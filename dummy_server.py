import socket
import struct
import sys

HOST = "74.198.53.47"  # Standard loopback interface address (localhost)
IN_PORT = 27873 # video input port
OUT_PORT = 27872  # video output port

def main():
    socket_in = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    socket_out = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    socket_in.bind((HOST, IN_PORT))
    socket_out.bind((HOST, OUT_PORT))

    socket_out.listen()
    out_conn, addr = socket_out.accept()
    if out_conn:
        print(f"Receiver connection from {addr}")

    socket_in.listen()
    in_conn, addr = socket_in.accept()
    if in_conn:
        print(f"Camera connection from {addr}")

    # pass through

if __name__ == "__main__":
    OUT_PORT = int(sys.argv[1])
    IN_PORT = int(sys.argv[2])
    main()
