import socket

HOST = "127.0.0.1"  # Server IP or hostname
PORT = 12345        # Server port (must match your C++ server)

def main():
    try:
        # Create a TCP socket
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((HOST, PORT))
            print(f"Connected to server {HOST}:{PORT}")

            while True:
                msg = input("Enter message (or 'quit' to exit): ")
                if msg.lower() == "quit":
                    break

                # Send message with newline (server reads until '\n')
                s.sendall((msg + "\n").encode("utf-8"))

                # Receive response from server
                data = s.recv(1024)
                if not data:
                    print("Server closed connection.")
                    break

                print("Received:", data.decode("utf-8").strip())

    except ConnectionRefusedError:
        print("Could not connect to the server. Is it running?")
    except Exception as e:
        print("Error:", e)

if __name__ == "__main__":
    main()
