all : client server

client : UDP_client.o
	gcc UDP_client.o -o client
client.o : UDP_client.c
	gcc -c UDP_client.c  
server : UDP_server.o
	gcc UDP_server.o -o server
server.o : UDP_server.c
	gcc -c UDP_server.c
 	
clean :
	rm -rf *.o wr rd

