#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

const char *html_content = 
"HTTP/1.1 200 OK\r\n"
"Content-Type: text/html; charset=utf-8\r\n\r\n"
"<!DOCTYPE html>"
"<html>"
"<head><title>Eu tenho um site fds</title></head>"
"<body><h1>Bom dia</h1>"
"<p>Eu tenho um site fds</p>"
"<p>texto gigante<p>"
"<p>texto gigante<p>"
"<p>texto gigante<p>"
"<p>texto gigante<p>"
"<p>texto gigante<p>"
"<p>texto gigante<p>"
"<p>texto gigante<p>"
"<p>texto gigante<p>"
"<p>texto gigante<p>"
"<p>texto gigante<p>"
"<p>texto gigante<p>"
"<p>texto gigante<p>"
"<p>texto gigante<p>"
"</body>"
"</html>";

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Setting up the address structure
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Binding the socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listening for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    // Accepting incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Reading the request
    read(new_socket, buffer, BUFFER_SIZE);
    printf("Received request:\n%s\n", buffer);

    // Sending the HTML response
    write(new_socket, html_content, strlen(html_content));
    printf("HTML content sent\n");

    // Closing the socket
    close(new_socket);
    close(server_fd);

    return 0;
}