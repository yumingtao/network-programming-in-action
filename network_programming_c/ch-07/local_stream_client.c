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
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc != 2){
        error(1, errno, "usage: local_stream_client <local path>");
    }

    int sockfd;
    struct sockaddr_un servaddr;

    sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if(sockfd < 0){
        error(1, errno, "create socket failed.");
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sun_family = AF_LOCAL;
    strcpy(servaddr.sun_path, argv[1]);

    if(connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0){
        error(1, errno, "connect failed.");
    }

    char send_line[MAXLINE];
    bzero(send_line, sizeof(send_line));
    char recv_line[MAXLINE];

    while (fgets(send_line, MAXLINE, stdin) != NULL){
        int nbytes = sizeof(send_line);
        if(write(sockfd, send_line, nbytes) != nbytes){
            error(1, errno, "write failed.");
        }

        if (read(sockfd, recv_line, MAXLINE) == 0){
            error(1, errno, "server teminated prematurely");
        }

        fputs(recv_line, stdout);
    }

    exit(0);
}