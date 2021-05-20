import socket
import time

server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)

#server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEPORT, 1)

# Enable broadcasting mode
#server.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
servAddr = input("Server address : ");
servPort = int(input("Server port : "));


server.settimeout(0.2)
message = b"your very important message"
while True:
	data,client = server.recvfrom(40);
    server.sendto(message, (client[0], client[1]))
    print("message sent!")
    time.sleep(1)
