#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <sstream>
#include <netdb.h>

using namespace std;

int main(int argc, const char * argv[])
{
    if(strcmp(argv[0], "-c")){
        string s = argv[2];
        s = s.substr(1, s.length());
        char *cstr = new char[s.length() + 1];
        strcpy(cstr, s.c_str());
        int client;
        int client_port = 1500;
        int bufsize = 1024;
        char buffer[bufsize];
        char *servername = cstr;
        struct sockaddr_in sin;
        struct hostent *host = gethostbyname(servername);
        
        if((client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
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
        
        recv(client, buffer, bufsize, 0);
        cout<<"client recv"<<buffer<<endl;
        cout<<"connection confirmed"<<endl;
        
        cout<<"communicating to server"<<endl;
        
        do {
            cin>>buffer;
            send(client, buffer, bufsize, 0);
            if (*buffer == 'FIN') {
                send(client, buffer, bufsize, 0);
                *buffer = '*';
            }
        } while (*buffer != '*');
        recv(client, buffer, bufsize, 0);
        do {
            recv(client, buffer, bufsize, 0);
            cout<<"server connection terminated"<<endl;
            close(client);
        } while (*buffer != '$');
        cout<<"server connection terminated"<<endl;
       	close(client);
    }
}
