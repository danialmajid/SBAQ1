#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg) {
    perror(msg);
    exit(1);}

int main() {
    int sockfd, new_sock;
    int random_number;
    int n;
    struct sockaddr_in server_address, client_address;
    char buffer[256];

    sockfd = socket(AF_INET, SOCK_STREAM, 0)
    if (sockfd < 0)
        error("Error to opening socket");

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(8080);

    if (bind(sockfd, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) 
        error("Error on binding");

    
    listen(sockfd, 5);
    socklen_t client_length = sizeof(client_address);
    new_sock = accept(sockfd, (struct sockaddr *) &client_address, &client_length);
    if (new_sock < 0) 
        error("Error on accept");

    srand(time(NULL));
    random_number = (rand() % 900) + 100;

    sprintf(buffer, "%d", random_number);

    n = write(new_sock, buffer, sizeof(buffer));
    if (n < 0) error("Error writing to socket");

    close(new_sock);
    close(sockfd);
    return 0;
}
