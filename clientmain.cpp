#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>
/* You will to add includes here */
using namespace std;
// Enable if you want debugging to be printed, see examble below.
// Alternative, pass CFLAGS=-DDEBUG to make, make CFLAGS=-DDEBUG
#define DEBUG


// Included to get the support library
#include "calcLib.h"


void initCalcLib(std::string Desthost, int Destport) {

    // create socket 
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    ///定义sockaddr_in
    struct sockaddr_in servaddr;

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(Destport);  //服务器端口
    servaddr.sin_addr.s_addr = inet_addr(Desthost.c_str());  //服务器ip，inet_addr用于IPv4的IP转换（十进制转换为二进制）
    //连接服务器，成功返回0，错误返回-1
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect");
        exit(1);
    }

}

int main(int argc, char* argv[]) {

    /*
      Read first input, assumes <ip>:<port> syntax, convert into one string (Desthost) and one integer (port).
       Atm, works only on dotted notation, i.e. IPv4 and DNS. IPv6 does not work if its using ':'.
    */
    char delim[] = ":";
    char* Desthost = strtok(argv[1], delim);
    char* Destport = strtok(NULL, delim);
    // *Desthost now points to a sting holding whatever came before the delimiter, ':'.
    // *Dstport points to whatever string came after the delimiter. 

    /* Do magic */
    int port = atoi(Destport);
#ifdef DEBUG
    printf("Host %s, and port %d.\n", Desthost, port);
    int sockfd;

    close(sockfd);

#endif
    return 0;

}
