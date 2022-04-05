import socket
import sys
import time
import struct

MAX_SIZE = 8

def connect_to_server(addr, port):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    sock.connect((addr, port))

    return sock

def xrecv(sock, n):
    buf = b''

    i = 0
    while i < n:
        data = sock.recv(n-i)
        if len(data) == 0:
            break

        buf += data
        i += len(data)

    return buf

def main():
    if len(sys.argv) != 3:
        print('Usage: python-client.py ip port', file=sys.stderr)
        return

    try:
        sock = connect_to_server(sys.argv[1], int(sys.argv[2]))

        buf = xrecv(sock, 4)
        if len(buf) != 4:
            raise Exception('EOF')

        size = struct.unpack('<I', buf)[0]

        if size > MAX_SIZE:
            raise Exception(f'Invalid size {size}')

        buf = xrecv(sock, size)

        if size == 8:
            current_time = struct.unpack('<Q', buf)[0]
        elif size == 4:
            current_time = struct.unpack('<I', buf)[0]
        else:
            raise Exception(f'Invalid size {size}')

        print('The time is {}'.format(time.ctime(current_time)))
    except Exception as ex:
        print(f'Got exception: {ex}', file=sys.stderr)

if __name__ == '__main__':
    main()
