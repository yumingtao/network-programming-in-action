//
// Created by Yu, Mingtao on 2020/6/10.
//

#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/errno.h>
#include <stdarg.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MESSAGE_SIZE 1024000

void error(int status, int err, char *fmt, ...);

void send_data(int sockfd) {
    char *query;
    query = malloc(MESSAGE_SIZE + 1);
    for (int i = 0; i < MESSAGE_SIZE; i++) {
        query[i] = 'a';
    }

    query[MESSAGE_SIZE] = '\0';

    const char *cp;
    cp = query;
    size_t remaining = strlen(query);

    while (remaining) {
        int n_written = send(sockfd, cp, remaining, 0);
        fprintf(stdout, "send into buffer %d \n", n_written);
        if (n_written <= 0) {
            error(1, errno, "send failed");
            return;
        }

        remaining -= n_written;
        cp += n_written;
    }

    return;
}

void error(int status, int err, char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    if (err) {
        fprintf(stderr, ": %s (%d)\n", strerror(err), err);
    }
    if (status) {
        exit(status);
    }
}

int main(int argc, char **argv) {
    int sockfd;
    struct sockaddr_in servaddr;
    if (argc != 2) {
        error(1, 0, "usage: tcp_client <IPaddress>");
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(12345);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    int connect_rt = connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    if(connect_rt < 0){
        error(1, errno, "connect failed");
    }
    send_data(sockfd);
    exit(0);
}
