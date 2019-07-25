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
	int pc_sock;
	char message[BUF_SIZE];
	int str_len;
	socklen_t clnt_adr_sz;	
	struct sockaddr_in pc_adr, rob1_adr, rob2_adr;

	FILE *fp1, *fp2;
	char buf1[BUF_SIZE], buf2[BUF_SIZE];

	if(argc!=6){
		printf("Usage : %s <pc port> <robot1 port> <robot1 ip> <robot2 port> <robot2 ip>\n", argv[0]);
		exit(1);
	}
	
	// socket creation
	pc_sock=socket(PF_INET, SOCK_DGRAM, 0);
	if(pc_sock==-1)
		error_handling("UDP socket creation error");
	
	// assign server address
	memset(&pc_adr, 0, sizeof(pc_adr));
	pc_adr.sin_family=AF_INET;
	pc_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	// pc_adr.sin_addr.s_addr=inet_addr("192.168.1.69");
	pc_adr.sin_port=htons(atoi(argv[1]));
	
	if(bind(pc_sock, (struct sockaddr*)&pc_adr, sizeof(pc_adr))==-1)
		error_handling("bind() error");

	// connect to robot client
	rob1_adr.sin_family = AF_INET;
	rob1_adr.sin_port = htons(atoi(argv[2]));
	rob1_adr.sin_addr.s_addr = inet_addr(argv[3]);

	rob2_adr.sin_family = AF_INET;
	rob2_adr.sin_port = htons(atoi(argv[4]));
	rob2_adr.sin_addr.s_addr = inet_addr(argv[5]);

	if (connect(pc_sock, (struct sockaddr *)&rob1_adr, sizeof(rob1_adr))< 0 )
		error_handling("connect()1 error");
	if (connect(pc_sock, (struct sockaddr *)&rob2_adr, sizeof(rob2_adr))< 0 )
		error_handling("connect()2 error");

	if((fp1=fopen("text1.txt", "r"))==NULL)
		error_handling("fopen() error");
	if((fp2=fopen("text2.txt", "r"))==NULL)
		error_handling("fopen() error");

	while(1)
	{
		fgets(buf1, BUF_SIZE, fp1);
		sendto(pc_sock, buf1, strlen(buf1),	0, (struct sockaddr*)&rob1_adr, sizeof(rob1_adr));

		fgets(buf2, BUF_SIZE, fp2);
		sendto(pc_sock, buf2, strlen(buf2),	0, (struct sockaddr*)&rob2_adr, sizeof(rob2_adr));

		sleep(1);
	}
	// while(1) 
	// {
	// 	clnt_adr_sz=sizeof(clnt_adr);
	// 	str_len=recvfrom(pc_sock, message, BUF_SIZE, 0, 
	// 							(struct sockaddr*)&clnt_adr, &clnt_adr_sz);
	// 	sendto(pc_sock, message, str_len, 0, 
	// 							(struct sockaddr*)&clnt_adr, clnt_adr_sz);
	// }	
	close(pc_sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
