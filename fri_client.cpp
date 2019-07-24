#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int serv_sock;
	char message[BUF_SIZE];
	int str_len;
	socklen_t clnt_adr_sz;
	
	struct sockaddr_in serv_adr, clnt_adr;
	if(argc!=2){
		printf("Usage : %s <robot port> <robot ip>\n", argv[0]);
		exit(1);
	}
	
	// socket creation
	serv_sock=socket(PF_INET, SOCK_DGRAM, 0);
	if(serv_sock==-1)
		error_handling("UDP socket creation error");
	
	// assign server address
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port=htons(atoi(argv[1]));
	
	if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
		error_handling("bind() error");

	// connect to robot client
	clnt_adr.sin_family = AF_INET;
	clnt_adr.sin_port = htons(atoi(argv[1]));
	clnt_adr.sin_addr.s_addr = htonl(atoi(argv[2]))

	if (connect(serv_sock, (struct sockaddr *)&clnt_adr, sizeof(clnt_adr))< 0 )
		error_handling("connect() error");

	while(1)
	{
		
	}
	// while(1) 
	// {
	// 	clnt_adr_sz=sizeof(clnt_adr);
	// 	str_len=recvfrom(serv_sock, message, BUF_SIZE, 0, 
	// 							(struct sockaddr*)&clnt_adr, &clnt_adr_sz);
	// 	sendto(serv_sock, message, str_len, 0, 
	// 							(struct sockaddr*)&clnt_adr, clnt_adr_sz);
	// }	
	close(serv_sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
