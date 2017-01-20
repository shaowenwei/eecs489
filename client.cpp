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

int main(int argc, const char * argv[])
{
	int client;
	int client_port = 1500;
	int buf_size = 1024;
	char buffer[buf_size];
	char *servername;
	struct sockaddr_in sin;
	struct hostent *host = gethostbyname(servername);

	if(client = socket(AF_INET, SOCK_STREAM, IPPORTO_TCP) < 0){
		perror("error socket");
		abort();
	}

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = *(unsigned long *) host->h_addr_list[0];
	sin.sin_port = htons(client_port);

	if(connect(client, (struct sockaddr*)&sin, sizeof(sin)) < 0){
		perror("error connecting");
		abort();
	}
	cout<<"client connected"<<endl;

	recv(client, buffer, buf_size, 0);
	cout<<buffer<<endl;
	cout<<"connection confirmed"<<endl;

}