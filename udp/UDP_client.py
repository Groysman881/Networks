import sys
import string
import socket
import fcntl,os
import errno
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
while True:
	client.sendto(msg.encode(),(servAddr,servPort));
	print("Send!");
	sleep(10);
	try:
		data, addr = client.recvfrom(40);
	except socket.error as e:
		err = e.args[0];
		if(err == errno.EAGAIN or err == errno.EWOULDBLOCK):
			continue;
		else:
			sys.exit(1);
	if(len(data) > 0):
		print("Server found IP",addr[0]);
		break;

client.close();
