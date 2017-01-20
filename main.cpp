#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

using namespace std;

int main()
{
	int client, server;
	int server_port = 1500;
	int buf_size = 1024;
	char buffer[buf_size];
	struct sockaddr_in sin;

	if ((client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
		perror("opening TCP socket");
		abort();
	}
    cout<<"socet server has been created"<<endl;

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(server_port);

	if(bind(client, (struct sockaddr*)&sin, sizeof(sin)) < 0 ){
		perror("bind");
		printf("can not bind socket to address/n");
		abort();
	}
	cout<<"waiting for client"<<endl;
	if(listen(client, 1) < 0){
		perror("error listening");
		abort();
	}

	int addrlen = sizeof(sin);
	server = accept(client, (struct sockaddr*)&sin, &addrlen);

	if(server < 0){
		perror("error accepting connection");
		abort();
	}

	cout<<"accepting connection"<<endl;
	strcpy(buffer, "Server connected...");
	send(server, buffer, buf_size, 0);

}
