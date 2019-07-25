#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
#define ROBOT1_IP 192.168.0.105
#define ROBOT1_PORT 9000
#define ROBOT2_IP 192.168.0.111
#define ROBOT2_PORT 9000

void error_handling(char *message);

int main(int argc, char *argv[])
{
	int sock;
	char message[BUF_SIZE];
	int str_len;
	socklen_t adr_sz;
	
	struct sockaddr_in rob_adr, pc_adr;
	if(argc!=2){
		printf("Usage : %s <robot port>\n", argv[0]);
		exit(1);
	}
	
	sock=socket(PF_INET, SOCK_DGRAM, 0);   
	if(sock==-1)
		error_handling("socket() error");
	
	memset(&rob_adr, 0, sizeof(rob_adr));
	rob_adr.sin_family=AF_INET;
	rob_adr.sin_port=htons(atoi(argv[1]));
	rob_adr.sin_addr.s_addr=htonl(INADDR_ANY);

	if(bind(sock, (struct sockaddr*)&rob_adr, sizeof(rob_adr))==-1)
		error_handling("bind() error");
	// connect(sock, (struct sockaddr*)&rob_adr, sizeof(rob_adr));

	while(1)
	{
		str_len = recvfrom(sock, messeage, BUF_SIZE, 0, (struct sockaddr *)&pc_adr, sizeof(pc_adr));
		message[str_len] = 0;
		printf("Message from server: %s", message);
	}
	// while(1)
	// {
	// 	fputs("Insert message(q to quit): ", stdout);
	// 	fgets(message, sizeof(message), stdin);     
	// 	if(!strcmp(message,"q\n") || !strcmp(message,"Q\n"))	
	// 		break;
	// 	/*
	// 	sendto(sock, message, strlen(message), 0, 
	// 				(struct sockaddr*)&rob_adr, sizeof(rob_adr));
	// 	*/
	// 	write(sock, message, strlen(message));

	// 	/*
	// 	adr_sz=sizeof(from_adr);
	// 	str_len=recvfrom(sock, message, BUF_SIZE, 0, 
	// 				(struct sockaddr*)&from_adr, &adr_sz);
	// 	*/
	// 	str_len=read(sock, message, sizeof(message)-1);

	// 	message[str_len]=0;
	// 	printf("Message from server: %s", message);
	// }	
	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
