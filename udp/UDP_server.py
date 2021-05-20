import socket


server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)

#server

servPort = int(input("Server port : "));
servAddr = input("Server address : ");


server.bind((servAddr,servPort));
message = b"Server answer";
while True:
	data,client = server.recvfrom(40);
	print("Client request IP = ",client[0]);
	server.sendto(message, (client[0], client[1]))
