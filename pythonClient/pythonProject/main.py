import socket
import threading

HOST = "127.0.0.1"
PORT = 12345

def receive_messages(sock):
    while True:
        try:
            data = sock.recv(1024)
            if not data:
                print("Server closed connection.")
                break
            print("\n[Chat] " + data.decode("utf-8").strip())
        except Exception as e:
            print("Receive error:", e)
            break

def main():
    try:
        name = input("Enter your name: ")

        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((HOST, PORT))
            print(f"Connected to server {HOST}:{PORT}")

            # Send name once
            s.sendall((name + "\n").encode("utf-8"))

            # Start receiver thread
            threading.Thread(target=receive_messages, args=(s,), daemon=True).start()

            while True:
                msg = input()
                if msg.lower() == "quit":
                    break
                s.sendall((msg + "\n").encode("utf-8"))

    except Exception as e:
        print("Error:", e)

if __name__ == "__main__":
    main()

