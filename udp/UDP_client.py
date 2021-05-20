import sys
import string
import socket
import fcntl,os
import errno
import select
from time import sleep

client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
msg = "Client lookup";
cliPort = int(input("Client port : "));
servPort = int(input("Server port : "));
servAddr = input("Server address : ");
hostname = socket.gethostname();
fcntl.fcntl(client,fcntl.F_SETFL,os.O_NONBLOCK);


client.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

client.bind((socket.gethostbyname(hostname), cliPort));

pollObj = select.poll();
pollObj.register(client,select.POLLIN);
answer = False
while (not answer):
	print("Check!");
	client.sendto(msg.encode(),(servAddr,servPort));
	print("Send!");
	fds = pollObj.poll(10000);
	for descriptor,event in fds:
		if(event == select.POLLIN):
			data,addr = client.recvfrom(40);
			print("Server found IP",addr[0]);
			answer = True

client.close();
