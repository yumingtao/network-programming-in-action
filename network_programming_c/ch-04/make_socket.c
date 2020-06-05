//
// Created by Yu, Mingtao on 2020/6/3.
//
#include<stdio.h>
#include <stdint.h>
#include <netinet/in.h>
#include <stdlib.h>


int make_socket(uint16_t port) {
    int sock;
    struct sockaddr_in name;

    /*
     * 创建字节流类型的套接字
     */
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    name.sin_family = AF_INET;/*设置地址簇*/
    name.sin_port = htons(port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);/*设置ip地址，通配地址*/

    if (bind(sock, (struct sockaddr *)&name, sizeof(name)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    return sock;
}

int main() {
    printf("Begin to make sock...\n");
    int sockfd = make_socket(12345);
    exit(0);
}