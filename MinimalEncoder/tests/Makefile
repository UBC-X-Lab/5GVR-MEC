CC = gcc
LDFLAGS := -ldl -L$(HOME)/ffmpeg_build/lib -lavdevice -lavfilter -lavformat -lavcodec -lpostproc -lswresample -lswscale -lavutil  -lm -lxcb -lXau -lXdmcp -lxcb-shm -lxcb -lXau -lXdmcp -lxcb-shape -lxcb -lXau -lXdmcp -lxcb-xfixes -lxcb-render -lxcb-shape -lxcb -lXau -lXdmcp -lasound -lm -ldl -lpthread -lrt -lSDL2 -Wl,--no-undefined -lm -ldl -lasound -lm -ldl -lpthread -lpulse-simple -lpulse -lX11 -lXext -lXcursor -lXinerama -lXi -lXrandr -lXss -lXxf86vm -lwayland-egl -lwayland-client -lwayland-cursor -lxkbcommon -lpthread -lrt -lsndio -lXv -lX11 -lXext -pthread -lm -lass -lm -lharfbuzz -lm -lglib-2.0 -pthread -lpcre -pthread -lgraphite2 -lfontconfig -luuid -lexpat -lfribidi -lfreetype -lpng16 -lm -lz -lm -lz -lva -lfreetype -lpng16 -lm -lz -lm -lz -lm -lz -pthread -lm -lz -lvorbis -lm -logg -lvorbisenc -lvorbis -lm -logg -L$(HOME)/ffmpeg_build/lib -lx264 -lpthread -lm -ldl -lva -lm -lm -lm -pthread -lva-drm -lva -lva-x11 -lva -lvdpau -lX11 -lm -lva -lXv -lX11 -lXext -lpthread -llzma -lbz2 -lm -lrist -L$(HOME)/librist_build/librist.a -lm
CFLAGS := -I$(HOME)/ffmpeg_build/include -I$(HOME)/librist_build/include -I$(HOME)/Augmented-x264/MinimalEncoder -I$(HOME)/Augmented-x264/MinimalEncoder/lockedQueue

$(info options for make are: all, TestReciever, TestEncoder, TestDecoder, clean)

all: TestReciever TestDecoder TestEncoder

TestReceiver: test_receiver.c ../stream_receive.o ../lockedQueue/locked_queue.o
	$(CC)  test_receiver.c ../lockedQueue/locked_queue.o ../stream_receive.o $(CFLAGS) $(LDFLAGS) -o TestReceiver

TestEncoder: test_encoder.c ../focal_transmit.o ../focal_encode.o ../lockedQueue/locked_queue.o
	$(CC)  test_encoder.c ../lockedQueue/locked_queue.o ../focal_encode.o ../focal_transmit.o $(CFLAGS) $(LDFLAGS) -o TestEncoder

TestDecoder: test_decoder.c ../stream_decode.o ../lockedQueue/locked_queue.o
	$(CC)  test_decoder.c ../lockedQueue/locked_queue.o ../stream_decode.o $(CFLAGS) $(LDFLAGS) -o TestDecoder

clean:
	rm TestReceiver TestEncoder TestDecoder

