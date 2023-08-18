#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <netinet/in.h>
#include <pthread.h>

#define PORT 8765
#define MAX_CLIENTS 5

struct client_info {
    int fd;
    struct sockaddr_in address;
};

void* handle_client(void* arg) {
    struct client_info* client = (struct client_info*)arg;
    int fd = client->fd;
    char buf[1024];
    int ret;

    while ((ret = read(fd, buf, sizeof(buf))) > 0) {
        /* bufの中の小文字を大文字に変換する */
        for (int i = 0; i < ret; i++) {
            if (isalpha(buf[i]))
                buf[i] = toupper(buf[i]);
        }

        /* 変換したデータをクライアントに送り返す */
        write(fd, buf, ret);
    }

    close(fd);
    free(client);
    pthread_exit(NULL);
}

int main() {
    int fd1;
    struct sockaddr_in saddr;
    int len;

    /*
     *  ストリーム型ソケット作る．
     */
    if ((fd1 = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }

    /* 
     * saddrの中身を0にしておかないと、bind()でエラーが起こることがある
     */
    bzero((char *)&saddr, sizeof(saddr));

    /*
     * ソケットの名前を入れておく
     */
    saddr.sin_family = PF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = htons(PORT);

    /*
     * ソケットにアドレスをバインドする。
     */
    if (bind(fd1, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) {
        perror("bind");
        exit(1);
    }

    /*
     * listenをソケットに対して発行する
     */
    if (listen(fd1, MAX_CLIENTS) < 0) {
        perror("listen");
        exit(1);
    }

    printf("Server started. Listening for clients...\n");

    while (1) {
        struct client_info* client = (struct client_info*)malloc(sizeof(struct client_info));
        len = sizeof(client->address);

        /* クライアントからの接続要求を受け付ける */
        client->fd = accept(fd1, (struct sockaddr *)&client->address, &len);
        if (client->fd < 0) {
            perror("accept");
            exit(1);
        }

        pthread_t tid;
        pthread_create(&tid, NULL, handle_client, (void*)client);
        pthread_detach(tid);
    }

    close(fd1);
    return 0;
}
