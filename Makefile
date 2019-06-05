all : server client

server : server.o
	gcc -o server server.o -lrt
	
client : client.o
	gcc -o client client.o -lrt


server.o : server.c 
	gcc -c server.c  -lrt

client.o : client.c	
	gcc -c client.c  -lrt


clean:
	rm server client *.o
