// Example low level rendering Unity plugin

#include "PlatformBase.h"
#include "RenderAPI.h"

#include <assert.h>
#include <math.h>
#include <vector>

extern "C" {
#include <libavutil/imgutils.h>
#include <libavutil/samplefmt.h>
#include <libavutil/timestamp.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#pragma comment (lib, "Ws2_32.lib")
#define DEFAULT_BUFLEN 512
bool serverUp = false;
bool shutdownServer = false;
char* destinationIP;
PCSTR destinationPort;
DWORD serverThreadID;
HANDLE serverThread;
DWORD decoderThreadID;
HANDLE decoderThread;
HANDLE packet_mutex;
HANDLE frame_mutex;
FILE* file = fopen("C:\\Users\\Public\\RenderingPluginLog.txt", "a+");
#define LOG(fmt, ...) {\
fprintf(file, "%s:%d " fmt, __FILE__, __LINE__, ##__VA_ARGS__);\
fflush(file);\
}

// --------------------------------------------------------------------------
// SetTimeFromUnity, an example function we export which is called by one of the scripts.

static float g_Time;

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetTimeFromUnity(float t) { g_Time = t; }



// --------------------------------------------------------------------------
// SetTextureFromUnity, an example function we export which is called by one of the scripts.

static void* g_TextureHandle = NULL;
static int   g_TextureWidth = 0;
static int   g_TextureHeight = 0;

/* ffmpeg state */
static struct SwsContext* g_swsContext = NULL;
static AVFrame* g_avFrame = NULL;
static bool g_avFrameAvailable = false;
static AVFormatContext* g_avFormatContext = NULL;
static AVStream* g_avVideoStream = NULL;
static AVCodecContext* g_avVideoCodecContext = NULL;
static AVPacket* g_avPacket;
static bool g_avPacketAvailable = false;

static int g_avVideoStreamIndex;


extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetTextureFromUnity(void* textureHandle, int w, int h)
{
	// A script calls this at initialization time; just remember the texture pointer here.
	// Will update texture pixels each frame from the plugin rendering event (texture update
	// needs to happen on the rendering thread).
	g_TextureHandle = textureHandle;
	g_TextureWidth = w;
	g_TextureHeight = h;
}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetupConnectionFromUnity(char* IP, char* port)
{
	// A script calls this at initialization time;
	// This IP and port will be connected to to receive video data.
	destinationIP = IP;
	destinationPort = port;
}


// --------------------------------------------------------------------------
// UnitySetInterfaces

static void UNITY_INTERFACE_API OnGraphicsDeviceEvent(UnityGfxDeviceEventType eventType);
static IUnityInterfaces* s_UnityInterfaces = NULL;
static IUnityGraphics* s_Graphics = NULL;

extern "C" void	UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginLoad(IUnityInterfaces * unityInterfaces)
{
	s_UnityInterfaces = unityInterfaces;
	s_Graphics = s_UnityInterfaces->Get<IUnityGraphics>();
	s_Graphics->RegisterDeviceEventCallback(OnGraphicsDeviceEvent);

#if SUPPORT_VULKAN
	if (s_Graphics->GetRenderer() == kUnityGfxRendererNull)
	{
		extern void RenderAPI_Vulkan_OnPluginLoad(IUnityInterfaces*);
		RenderAPI_Vulkan_OnPluginLoad(unityInterfaces);
	}
#endif // SUPPORT_VULKAN

	// Run OnGraphicsDeviceEvent(initialize) manually on plugin load
	OnGraphicsDeviceEvent(kUnityGfxDeviceEventInitialize);
}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginUnload()
{
	s_Graphics->UnregisterDeviceEventCallback(OnGraphicsDeviceEvent);
}

#if UNITY_WEBGL
typedef void	(UNITY_INTERFACE_API* PluginLoadFunc)(IUnityInterfaces* unityInterfaces);
typedef void	(UNITY_INTERFACE_API* PluginUnloadFunc)();

extern "C" void	UnityRegisterRenderingPlugin(PluginLoadFunc loadPlugin, PluginUnloadFunc unloadPlugin);

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API RegisterPlugin()
{
	UnityRegisterRenderingPlugin(UnityPluginLoad, UnityPluginUnload);
}
#endif

// --------------------------------------------------------------------------
// GraphicsDeviceEvent


static RenderAPI* s_CurrentAPI = NULL;
static UnityGfxRenderer s_DeviceType = kUnityGfxRendererNull;


static void UNITY_INTERFACE_API OnGraphicsDeviceEvent(UnityGfxDeviceEventType eventType)
{
	// Create graphics API implementation upon initialization
	if (eventType == kUnityGfxDeviceEventInitialize)
	{
		assert(s_CurrentAPI == NULL);
		s_DeviceType = s_Graphics->GetRenderer();
		s_CurrentAPI = CreateRenderAPI(s_DeviceType);
	}

	// Let the implementation process the device related events
	if (s_CurrentAPI)
	{
		s_CurrentAPI->ProcessDeviceEvent(eventType, s_UnityInterfaces);
	}

	// Cleanup graphics API implementation upon shutdown
	if (eventType == kUnityGfxDeviceEventShutdown)
	{
		delete s_CurrentAPI;
		s_CurrentAPI = NULL;
		s_DeviceType = kUnityGfxRendererNull;
	}
}


static void receivePacket() {

}

DWORD WINAPI runServer(LPVOID param) {
	serverUp = true;
	LOG("Server Starting...\n");
	WSADATA wsaData;
	int iResult;

	SOCKET ConnectSocket = INVALID_SOCKET;

	struct addrinfo* result = NULL;
	struct addrinfo* ptr = NULL;
	struct addrinfo hints;

	int iSendResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		LOG("WSAStartup failed with error: %d\n", iResult);
		serverUp = false;
		return -1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(destinationIP, destinationPort, &hints, &result);
	if (iResult != 0) {
		LOG("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		serverUp = false;
		return -1;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			return 1;
		}

		// Connect to server.
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		LOG("Unable to connect to server!\n");
		WSACleanup();
		return 1;
	}

	// Receive until the peer shuts down the connection
	LOG("Server Connected...\n");
	do {
		if (!g_avPacketAvailable) {
			unsigned char recvlen[4];
			iResult = recv(ConnectSocket, (char*)recvlen, 4, MSG_WAITALL);
			LOG("Recieved length: iResult = %d\n", iResult);
			unsigned int len = -1;
			if (iResult > 0) {
				len = (recvlen[3] << 24) | (recvlen[2] << 16) | (recvlen[1] << 8) | (recvlen[0]);
			}
			else if (iResult == 0) {
				LOG("Connection closing...\n");
			}
			else {
				LOG("recv failed with error: %d\n", WSAGetLastError());
				closesocket(ConnectSocket);
				WSACleanup();
				serverUp = false;
				return -1;
			}
			if (len != -1) {
				char* receivedata = (char*)malloc(len);
				iResult = recv(ConnectSocket, receivedata, len, MSG_WAITALL);
				LOG("Recieved data: iResult = %d\n", iResult);
				LOG("received packet of len %d, read %d bytes\n", len, iResult);
				if (iResult > 0) {
					WaitForSingleObject(packet_mutex, INFINITE);
					LOG("Server received packet of len %d\n", len);
					int ret = av_new_packet(g_avPacket, len);
					if (ret) {
						LOG("Error allocating packet\n");
						return -1;
					}
					memcpy(g_avPacket->data, receivedata, len);
					free(receivedata);
					g_avPacketAvailable = true;
					LOG("Server created packet\n");
					ReleaseMutex(packet_mutex);
					SwitchToThread();//Yield this thread
				}
				else if (iResult == 0) {
					LOG("Connection closing...\n");
				}
				else {
					LOG("recv failed with error: %d\n", WSAGetLastError());
					closesocket(ConnectSocket);
					WSACleanup();
					serverUp = false;
					return -1;
				}
			}
		}
	} while (iResult > 0);

	// shutdown the connection since we're done
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		LOG("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		serverUp = false;
		return -1;
	}

	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();

	serverUp = false;
	return 0;
}

static void decode(AVCodecContext* ctx, AVPacket* pkt, AVFrame* frame) {
	int ret;
	static int frameno = 0;
	ret = avcodec_send_packet(ctx, pkt);
	if (ret < 0) {
		LOG("Error sending a packet for decoding\n");
		return;
	}
	ret = avcodec_receive_frame(ctx, frame);
	if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
		ReleaseMutex(frame_mutex);
		return;
	}
	else if (ret < 0) {
		LOG("Error during decoding\n");
		return;
	}
	g_avFrameAvailable = true;
	g_avPacketAvailable = false;
	av_packet_unref(pkt);
	LOG("received frame\n");

}

DWORD WINAPI runDecoder(LPVOID param) {
	LOG("Decoder starting...\n");
	const AVCodec* codec;
	AVCodecContext* ctx = NULL;
	int ret;
	codec = avcodec_find_decoder(AV_CODEC_ID_H264);
	if (!codec) {
		LOG("Codec not found\n");
		return -1;
	}
	ctx = avcodec_alloc_context3(codec);
	if (!ctx) {
		LOG("Could not allocate decoder codec context\n");
		return -1;
	}
	if (avcodec_open2(ctx, codec, NULL) < 0) {
		LOG("Could not open codec\n");
		return -1;
	}
	g_avFrame = av_frame_alloc();
	if (!g_avFrame) {
		LOG("Could not allocate output frame\n");
		return -1;
	}
	LOG("Decoder initialized...\n");
	while (!shutdownServer) {
		if (g_avPacketAvailable && !g_avFrameAvailable) {
			WaitForSingleObject(packet_mutex, INFINITE);
			LOG("Decoding Packet at %x with len %d\n", g_avPacket, g_avPacket->size);
			WaitForSingleObject(frame_mutex, INFINITE);
			decode(ctx, g_avPacket, g_avFrame);
			ReleaseMutex(frame_mutex);
			ReleaseMutex(packet_mutex);
		}
		SwitchToThread();//Yield this thread
	}
	LOG("Shutdown signal received, shutting down decoder\n");
	avcodec_free_context(&ctx);
	return 0;
}
// --------------------------------------------------------------------------
// OnRenderEvent
// This will be called for GL.IssuePluginEvent script calls; eventID will
// be the integer passed to IssuePluginEvent. In this example, we just ignore
// that value.


static void ModifyTexturePixels()
{
	if (!serverUp) {
		frame_mutex = CreateMutex(NULL, FALSE, NULL);
		if (frame_mutex == NULL) {
			LOG("ERROR creating frame mutex.\n");
			return;
		}
		packet_mutex = CreateMutex(NULL, FALSE, NULL);
		if (packet_mutex == NULL) {
			LOG("ERROR creating packet mutex.\n");
			return;
		}
		g_avPacket = av_packet_alloc();
		if (!g_avPacket) {
			LOG("Failed allocating packet\n");
			return;
		}
		decoderThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)runDecoder, 0, 0, &decoderThreadID);
		serverThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)runServer, 0, 0, &serverThreadID);
	}

	void* textureHandle = g_TextureHandle;
	int width = g_TextureWidth;
	int height = g_TextureHeight;
	if (!textureHandle)
		return;


	if (g_avFrameAvailable && WaitForSingleObject(frame_mutex, 10) == WAIT_OBJECT_0) {
		LOG("Updating Unity with frame\n")
			g_avFrameAvailable = false;
		int textureRowPitch;
		void* textureDataPtr = s_CurrentAPI->BeginModifyTexture(textureHandle, width, height, &textureRowPitch);
		if (!textureDataPtr) {
			LOG("BeginModifyTexture Failed\n");
			ReleaseMutex(frame_mutex);
			return;
		}
		uint8_t* dstData[] = { (uint8_t*)textureDataPtr };
		int dstStride[] = { textureRowPitch };
		if (!g_swsContext) {
			g_swsContext = sws_getCachedContext(g_swsContext,
				g_avFrame->width, g_avFrame->height, (AVPixelFormat)g_avFrame->format,
				g_TextureWidth, g_TextureHeight, AV_PIX_FMT_RGBA,
				SWS_BICUBIC, NULL, NULL, NULL);

			if (!g_swsContext) {
				LOG("Failed to create swscale context\n");
				ReleaseMutex(frame_mutex);

				return;
			}
		}
		if (sws_scale(g_swsContext, g_avFrame->data, g_avFrame->linesize, 0, g_avFrame->height, dstData, dstStride) < 0) {
			LOG("scaling failed!\n");
		}

		s_CurrentAPI->EndModifyTexture(textureHandle, width, height, textureRowPitch, textureDataPtr);
		LOG("Done updating unity\n");
		ReleaseMutex(frame_mutex);
	}
	return;
}


static void UNITY_INTERFACE_API OnRenderEvent(int eventID)
{
	// Unknown / unsupported graphics device type? Do nothing
	if (s_CurrentAPI == NULL)
		return;

	ModifyTexturePixels();
}


// --------------------------------------------------------------------------
// GetRenderEventFunc, an example function we export which is used to get a rendering event callback function.

extern "C" UnityRenderingEvent UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetRenderEventFunc()
{
	return OnRenderEvent;
}