CFLAGS = -Ic_proto -Wall
LDLIBS = -lpthread -lprotobuf-c

client_mec: client_mec.o $(patsubst %.c,%.o,$(wildcard c_proto/*.c))
