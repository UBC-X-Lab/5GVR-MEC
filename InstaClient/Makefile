CFLAGS = -I/opt/local/include -Ic_proto -gfull -Wall
LDFLAGS = -L/opt/local/lib -lprotobuf-c -Wl,-dead_strip

client: client.o $(patsubst %.c,%.o,$(wildcard c_proto/*.c))
client_ff: client_ff.o $(patsubst %.c,%.o,$(wildcard c_proto/*.c))
client_mec: client_mec.o $(patsubst %.c,%.o,$(wildcard c_proto/*.c))
