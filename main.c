#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct hostent *he = gethostbyname("www.google.com");
    struct in_addr **addList = (struct in_addr **) he->h_addr_list;
    char *ip = inet_ntoa(*addList[0]);
    struct sockaddr_in client;
    client.sin_family = AF_INET;
    client.sin_port = htons(80);
    client.sin_addr.s_addr = inet_addr(ip);

    int descriptor = socket(AF_INET, SOCK_STREAM, 0);
    int connection = connect(descriptor, (struct sockaddr *) &client, sizeof(client));

    char *data = "GET / HTTP/1.1\r\n\r\n";
    send(descriptor, data, strlen(data), 0);

    char reply[1024];
    recv(descriptor, reply, 1024, 0);
    puts(reply);
}