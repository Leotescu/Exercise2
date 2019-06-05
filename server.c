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

	mqd_t server_queue, client_queue;
	int token = 1;
	struct mq_attr attr;
	char buffer1[BUF_SIZE], buffer2[BUF_SIZE];
	
	attr.mq_flags = 0;
	attr.mq_maxmsg = MAX_MSG;
	attr.mq_msgsize = MSG_SIZE;
	attr.mq_curmsgs = 0;

	printf("Server opened.\n");

	server_queue = mq_open("/my_mq", O_RDONLY | O_CREAT, 0664, &attr);
	
	if(server_queue == -1){
		perror("mq_open-server");
		return 1;
	}

	while(1){
		int recv = mq_receive(server_queue, buffer1, BUF_SIZE, NULL);
		if(recv == -1){
			perror("mq_recieve");
			return 1;
		}
		printf("Message recieved.\n");

	 	client_queue = mq_open(buffer1, O_WRONLY);
		if(client_queue == 1){
			perror("No open client queue");
			return 1;		
		}

		sprintf(buffer2, "%d", token);
		int send = mq_send(client_queue, buffer2, strlen(buffer2) +1, 0);
		if(send == -1){
			perror("mq_send");
			return 1;			
		}
		printf("Message sent to client.\n");
		token++;
	}
	return 0;
}
