#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Socket creation failed");
        exit(-1);
    }

    int yes = 1;

    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);

    struct addrinfo hint, *res;
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, "8080", &hint, &res);

    int bind_result = bind(sockfd, res->ai_addr, res->ai_addrlen);
    if (bind_result < 0)
    {
        perror("Bind failed");
        exit(-1);
    }

    // Listen for incoming connections
    int listen_result = listen(sockfd, 20);
    if (listen_result < 0)
    {
        perror("Listen failed");
        exit(-1);
    }

    struct sockaddr_storage their_addr;
    socklen_t addr_size = sizeof(their_addr);

    int new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);

    int max_len = 1000;
    char received_request[max_len];
    memset(received_request, 0, max_len);
    int num_bytes = recv(new_fd, received_request, max_len, 0);

    if (strncmp(received_request, "GET", 3) == 0)
    {
        printf("Received HTTP GET request!\n");

        // We respond to the HTTP GET request

        char *status_line = "HTTP/1.1 200 OK\r\n";
        int sent_bytes = send(new_fd, status_line, strlen(status_line), 0);
        printf("sent_bytes = %d\n", sent_bytes);

        char *headers = "Content-Type: text/html\r\n\r\n";

        sent_bytes = send(new_fd, headers, strlen(headers), 0);
        printf("sent_bytes = %d\n", sent_bytes);

        FILE *index_file = fopen("index.html", "r");
        char c;
        while ((c = getc(index_file)) != EOF)
        {
            sent_bytes = send(new_fd, &c, 1, 0);
        }
    }
    else
    {
        printf("Received Non-GET request. Ignoring...\n");
        close(new_fd);
        close(sockfd);
        exit(-1);
    }

    close(new_fd);
    close(sockfd);
}
