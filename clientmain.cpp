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
// Included to get the support library
#include "calcLib.h"
/* You will to add includes here */
using namespace std;
// Enable if you want debugging to be printed, see examble below.
// Alternative, pass CFLAGS=-DDEBUG to make, make CFLAGS=-DDEBUG
#define DEBUG

int main(int argc, char* argv[]) {
    char delim[] = ":";
    char* Desthost = strtok(argv[1], delim);
    char* Destport = strtok(NULL, delim);
    int port = atoi(Destport);
#ifdef DEBUG
    printf("Host %s, and port %d.\n", Desthost, port);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int recv_num;
    if (sockfd == -1) {
        perror("failed to create socket");
        exit(1);
    }
    // 连接服务器
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(Desthost); // 服务器IP地址

    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("failed to connect server");
        close(sockfd);
        exit(1);
    }
    char recv_buf[1024];
    memset(recv_buf, 0, sizeof(recv_buf));
    // 接收数据
    if ((recv_num = read(sockfd, recv_buf, sizeof(recv_buf))) == -1) {
        perror("failed to receive data from server");
    }
    else if (recv_num > 0) {
        printf("%s", recv_buf);
    }
    // 发送确认消息
    const char* confirm_message = "OK\n";
    send(sockfd, confirm_message, strlen(confirm_message), 0);
    printf("%s", confirm_message);
    // 接收新数据
    memset(recv_buf, 0, sizeof(recv_buf));
    recv_num = read(sockfd, recv_buf, sizeof(recv_buf));
    if (recv_num == -1) {
        perror("failed to receive data from server");
    }
    else if (recv_num > 0) {
        printf("%s", recv_buf);
    }

    close(sockfd);
#endif
}
