CC = gcc
LDFLAGS := -ldl -L$(HOME)/ffmpeg_build/lib -lavdevice -lavfilter -lavformat -lavcodec -lpostproc -lswresample -lswscale -lavutil  -lm -lxcb -lXau -lXdmcp -lxcb-shm -lxcb -lXau -lXdmcp -lxcb-shape -lxcb -lXau -lXdmcp -lxcb-xfixes -lxcb-render -lxcb-shape -lxcb -lXau -lXdmcp -lasound -lm -ldl -lpthread -lrt -lSDL2 -Wl,--no-undefined -lm -ldl -lasound -lm -ldl -lpthread -lpulse-simple -lpulse -lX11 -lXext -lXcursor -lXinerama -lXi -lXrandr -lXss -lXxf86vm -lwayland-egl -lwayland-client -lwayland-cursor -lxkbcommon -lpthread -lrt -lsndio -lXv -lX11 -lXext -pthread -lm -lass -lm -lharfbuzz -lm -lglib-2.0 -pthread -lpcre -pthread -lgraphite2 -lfontconfig -luuid -lexpat -lfribidi -lfreetype -lpng16 -lm -lz -lm -lz -lva -lfreetype -lpng16 -lm -lz -lm -lz -lm -lz -pthread -lm -lz -lvorbis -lm -logg -lvorbisenc -lvorbis -lm -logg -L$(HOME)/ffmpeg_build/lib -lx264 -lpthread -lm -ldl -lva -lm -lm -lm -pthread -lva-drm -lva -lva-x11 -lva -lvdpau -lX11 -lm -lva -lXv -lX11 -lXext -lpthread -llzma -lbz2 -lm -lrist -L$(HOME)/librist_build/librist.a -lm
CFLAGS := -I$(HOME)/ffmpeg_build/include -I$(HOME)/librist_build/include

DummySenderFew: server_controller_static.c stream_receive_few_frame.o ../stream_decode.o ../focal_encode.c dummy_sender.c ../lockedQueue/locked_queue.o ../buildtimestamp.o
	$(CC) server_controller_static.c stream_receive_few_frame.o ../stream_decode.o ../focal_encode.c dummy_sender.c ../lockedQueue/locked_queue.o ../buildtimestamp.o $(CFLAGS) $(LDFLAGS) -o DummySender

DummySender: server_controller_static.c ../stream_receive.o ../stream_decode.o ../focal_encode.c dummy_sender.c ../lockedQueue/locked_queue.o ../buildtimestamp.o
	$(CC) server_controller_static.c ../stream_receive.o ../stream_decode.o ../focal_encode.c dummy_sender.c ../lockedQueue/locked_queue.o ../buildtimestamp.o $(CFLAGS) $(LDFLAGS) -o DummySender

DummySenderAllQ: server_controller_static_allq.c ../stream_receive.o ../stream_decode.o ../focal_encode_allq.c dummy_sender_allq.c ../lockedQueue/locked_queue.o ../buildtimestamp.o
	$(CC) server_controller_static_allq.c ../stream_receive.o ../stream_decode.o ../focal_encode_allq.c dummy_sender_allq.c ../lockedQueue/locked_queue.o ../buildtimestamp.o $(CFLAGS) $(LDFLAGS) -o DummySender

clean:
	rm DummySender DummySenderFew DummySenderAllQ