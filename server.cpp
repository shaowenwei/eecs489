#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <sstream>

using namespace std;

int main(int argc, const char * argv[])
{
    if(strcmp(argv[0], "-s")){
        
        string s = argv[2];
        s = s.substr(1, s.length());
        stringstream ss;
        int portnum;
        ss<<s;
        ss>>portnum;
        if((portnum >= 65535) || (portnum <= 1024)){
            perror("port number must be in the range 1024 to 65535");
            abort();
        }
        
        int client, server;
        int server_port = portnum;
        int bufsize = 1024;
        char buffer[bufsize];
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
        
        bind(client, (struct sockaddr*)&sin, sizeof(sin));
        cout<<"waiting for client"<<endl;
        if(listen(client, 1) < 0){
            perror("error listening");
            abort();
        }
        
        socklen_t addrlen = sizeof(sin);
        server = accept(client, (struct sockaddr*)&sin, &addrlen);
        
        if(server < 0){
            perror("error accepting connection");
            abort();
        }
        
        cout<<"accepting connection"<<endl;
        strcpy(buffer, "Server connected...");
        send(server, buffer, bufsize, 0);
        
        cout<<"communicating to client"<<endl;
        do {
            recv(server, buffer, bufsize, 0);
            cout << buffer << " ";
            if (*buffer == 'FIN') {
                *buffer = '*';
            }
        } while (*buffer != '*');
        strcpy(buffer, "$");
        send(server, buffer, bufsize, 0);
        cout<<"server connection terminated"<<endl;
        close(server);
    }
}
