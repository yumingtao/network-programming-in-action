//
// Created by Yu, Mingtao on 2020/6/10.
//

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <zconf.h>
#include <sys/errno.h>
#include <string.h>


size_t readn(int fd, void *buffer, size_t size);

void read_data(int sockfd) {
    ssize_t n;
    char buf[1024];

    int time = 0;

    for (;;) {
        fprintf(stdout, "block in rean\n");
        n = readn(sockfd, buf, 1024);
        if (n == 0) {
            return;
        }

        time++;
        fprintf(stdout, "1k read for %d \n", time);
        usleep(10000);
    }
}


size_t readn(int fd, void *buffer, size_t size) {
    char *buffer_pointer = buffer;
    int length = size;

    while (length > 0) {
        int result = read(fd, buffer_pointer, length);
        if (result < 0) {
            if (errno == EINTR) {
                /*考虑非阻塞情况，这里需要再次调用read*/
                continue;
            } else {
                return (-1);
            }
        } else if (result == 0) {
            //EOF, 套接字关闭
            break;
        }

        length -= result;
        buffer_pointer += result;
    }

    //返回实际读取的自己数
    return (size - length);
}

int main(int argc, char **argv) {
    int listenfd, connfd;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    //初始化
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(12345);

    bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    listen(listenfd, 1024);

    for (;;) {
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
        read_data(connfd);
        close(connfd);
    }
}