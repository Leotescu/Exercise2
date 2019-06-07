#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<mqueue.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#define MAX_MSG 50
#define MSG_SIZE 2048
#define BUF_SIZE 10000

int main(int argc, char **argv){
	
	char name_queue[100];
	char buffer1[BUF_SIZE];
	char buf[5];
	mqd_t server_queue, client_queue;
	struct mq_attr attr;	
	int token = 1;

	attr.mq_flags = 0;
	attr.mq_maxmsg = MAX_MSG;
	attr.mq_msgsize = MSG_SIZE;
	attr.mq_curmsgs = 0;

	sprintf(name_queue, "/client-%d", token);

	client_queue = mq_open(name_queue, O_RDONLY | O_CREAT, 0664, 0);
	if(client_queue == -1){
		perror("mq_open-client");
		return 1; 	
	}

	server_queue = mq_open("/my_mq", O_WRONLY);
	if(client_queue == 1){
		perror("mq_open-server");
		return 1;		
		}
	printf("Insert a token:\n");

	while(fgets(buf, 5, stdin)) {
		int send = mq_send(server_queue, name_queue, strlen(name_queue) + 1, 0);
		if(send == -1){
			perror("Client not connected");
			return 1;			
		} 
		int recv = mq_receive(client_queue, buffer1, BUF_SIZE, NULL);
		if(recv == -1){
			perror("mq_recieve");
			return 1;
		}
	
	printf("Token received: %s\n" , buffer1);
	printf("Insert a token:\n");
	}
	
	int close = mq_close(client_queue);
	if(close == -1){
		perror("mq_close");
		return 1;	
	}

	printf("Finish\n");
	return 0;
}
