//
// Created by Yu, Mingtao on 2020/6/29.
//

#include <sys/errno.h>
#include <sys/un.h>
#include <sys/socket.h>
#include "../lib/common.h"
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        error(1, errno, "usage: local_data_server <local_path>");
    }

    int sockfd;
    struct sockaddr_un client_addr, server_addr;
    sockfd = socket(AF_LOCAL, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        error(1, errno, "create socket failed.");
    }

    bzero(&client_addr, sizeof(client_addr));
    client_addr.sun_family = AF_LOCAL;

    //需要指定一个本地路径，在服务端回包时，可以正确找到地址。
    //而在UDP客户端程序里，数据是可以通过UDP包的本地地址和端口来匹配的。
    strcpy(client_addr.sun_path, tmpnam(NULL));

    if (bind(sockfd, (struct sockaddr *) &client_addr, sizeof(client_addr)) < 0) {
        error(1, errno, "bind failed.");
    }

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sun_family = AF_LOCAL;
    strcpy(server_addr.sun_path, argv[1]);

    char send_line[MAXLINE];
    bzero(send_line, MAXLINE);
    char recv_line[MAXLINE];

    while (fgets(send_line, MAXLINE, stdin) != NULL) {
        int i = strlen(send_line);
        if (send_line[i - 1] == '\n') {
            send_line[i - 1] = 0;
        }

        size_t nbytes = strlen(send_line);
        printf("now sending %s \n", send_line);

        if (sendto(sockfd, send_line, nbytes, 0, (struct sockaddr *) &server_addr, sizeof(server_addr)) != nbytes) {
            error(1, errno, "sendto error.");
        }

        int n = recvfrom(sockfd, recv_line, MAXLINE, 0, NULL, NULL);
        recv_line[n] = 0;
        fputs(recv_line, stdout);
        fputs("\n", stdout);
    }

    exit(0);
}