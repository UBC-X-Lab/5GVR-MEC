CC = gcc
LDFLAGS := -ldl -L$(HOME)/ffmpeg_build/lib -lavdevice -lavfilter -lavformat -lavcodec -lpostproc -lswresample -lswscale -lavutil  -lm -lxcb -lXau -lXdmcp -lxcb-shm -lxcb -lXau -lXdmcp -lxcb-shape -lxcb -lXau -lXdmcp -lxcb-xfixes -lxcb-render -lxcb-shape -lxcb -lXau -lXdmcp -lasound -lm -ldl -lpthread -lrt -lSDL2 -Wl,--no-undefined -lm -ldl -lasound -lm -ldl -lpthread -lpulse-simple -lpulse -lX11 -lXext -lXcursor -lXinerama -lXi -lXrandr -lXss -lXxf86vm -lwayland-egl -lwayland-client -lwayland-cursor -lxkbcommon -lpthread -lrt -lsndio -lXv -lX11 -lXext -pthread -lm -lass -lm -lharfbuzz -lm -lglib-2.0 -pthread -lpcre -pthread -lgraphite2 -lfontconfig -luuid -lexpat -lfribidi -lfreetype -lpng16 -lm -lz -lm -lz -lva -lfreetype -lpng16 -lm -lz -lm -lz -lm -lz -pthread -lm -lz -lvorbis -lm -logg -lvorbisenc -lvorbis -lm -logg -L$(HOME)/ffmpeg_build/lib -lx264 -lpthread -lm -ldl -lva -lm -lm -lm -pthread -lva-drm -lva -lva-x11 -lva -lvdpau -lX11 -lm -lva -lXv -lX11 -lXext -lpthread -llzma -lbz2 -lm -lrist -L$(HOME)/librist_build/librist.a -lm
CFLAGS := -I$(HOME)/ffmpeg_build/include -I$(HOME)/librist_build/include

$(info options for make are: FocalEncoder (parallel - up to date), FocalEncoderDynamic (uses rist input), FocalEncoderStatic (uses static input video), FocalEncoderDummyTCP (customtcp), clean)

FocalEncoderStatic: encoder.c focal_transmit_NONQUEUE.c
	$(CC) encoder.c focal_transmit.c $(CFLAGS) $(LDFLAGS) -o FocalEncoder

FocalEncoderDynamic: dynamic_encoder.c focal_transmit_NONQUEUE.c buildtimestamp.c
	$(CC) dynamic_encoder.c focal_transmit_NONQUEUE.c buildtimestamp.c $(CFLAGS) $(LDFLAGS) -o FE_RIST_DY

FocalEncoder: server_controller.c stream_receive.o stream_decode.o focal_encode.c focal_transmit.c lockedQueue/locked_queue.o buildtimestamp.o
	$(CC) server_controller.c stream_receive.o stream_decode.o focal_encode.c focal_transmit.c lockedQueue/locked_queue.o buildtimestamp.o $(CFLAGS) $(LDFLAGS) -o FocalEncoder

FocalEncoderDummyTCP: server_controller.c stream_receive_custom_protocol.o stream_decode.o focal_encode.o focal_transmit.o lockedQueue/locked_queue.o buildtimestamp.o
	$(CC) server_controller.c stream_receive_custom_protocol.o stream_decode.o focal_encode.c focal_transmit.c lockedQueue/locked_queue.o buildtimestamp.o $(CFLAGS) $(LDFLAGS) -o FocalEncoder

FocalEncoderDummyTcpALLQ: server_controller_allq.c stream_receive_custom_protocol.o stream_decode.o focal_encode_allq.o focal_transmit_allq.o lockedQueue/locked_queue.o buildtimestamp.o
	$(CC) server_controller_allq.c stream_receive_custom_protocol.c stream_decode.o focal_encode_allq.o focal_transmit_allq.o lockedQueue/locked_queue.o buildtimestamp.o $(CFLAGS) $(LDFLAGS) -o FocalEncoder

FocalEncoderDummyTcpDebug: server_controller.c stream_receive_custom_protocol_debug.o stream_decode_debug.o focal_encode_debug.o focal_transmit_debug.o lockedQueue/locked_queue.o buildtimestamp.o
	$(CC) server_controller.c stream_receive_custom_protocol_debug.c stream_decode_debug.o focal_encode_debug.o focal_transmit_debug.o lockedQueue/locked_queue.o buildtimestamp.o $(CFLAGS) $(LDFLAGS) -o FocalEncoder

clean:
	rm FocalEncoderStatic FocalEncoderDynamic FocalEncoder