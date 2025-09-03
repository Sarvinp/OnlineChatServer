import zmq
import threading
import sys

def receive_messages(socket):
    while True:
        try:
            socket.recv()  # Empty frame
            msg = socket.recv_string()
            print(f"[Client] Received: {msg}")
        except zmq.error.ZMQError:
            break  # Socket closed

def main():
    context = zmq.Context()
    socket = context.socket(zmq.DEALER)

    client_id = input("Enter your name: ")
    socket.setsockopt_string(zmq.IDENTITY, client_id)
    socket.connect("tcp://localhost:5555")

    receiver = threading.Thread(target=receive_messages, args=(socket,), daemon=True)
    receiver.start()

    print("Type messages to send. Enter '0' to exit.")
    while True:
        msg = input()
        if msg.strip() == "0":
            print("[Client] Exiting...")
            socket.close()
            context.term()
            break
        socket.send(b"")  # Empty frame
        socket.send_string(msg)

if __name__ == "__main__":
    main()
