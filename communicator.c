#include <stdio.h>
#include <string.h>
#include <stdint.h>

#ifdef unix

/*
 * ### UNIX FUNCTIONS ###
 * ######################
 */

#include <sys/socket.h>
#include <arpa/inet.h>

int g_sock;

int initClient(char *addr, int port) {
	struct sockaddr_in servaddr;
	g_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(g_sock < 0) return -1;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(addr);
	servaddr.sin_port=htons(port);
	if(connect(g_sock, (struct sockaddr *)&servaddr, sizeof(servaddr))<0) return -1;
	return g_sock;
}

int sendState(uint8_t *data) {
	return send(g_sock, data, 16, 0);
}

#else

/*
 * ### WINDOWS FUNCTIONS ###
 * #########################
 */

#include <winsock2.h>
#include <ws2tcpip.h>

SOCKET ConnectSocket = INVALID_SOCKET;

int initClient(char *addr, int port) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData)) {
        return -1;
    }
    struct addrinfo *ptr = NULL;
    struct addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    char buffer[6];
    sprintf(buffer, "%i", port);
    if(getaddrinfo(addr, buffer, &hints, &ptr)) {
        WSACleanup();
        return -1;
    }
    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if (ConnectSocket == INVALID_SOCKET) {
        freeaddrinfo(ptr);
        WSACleanup();
        return -1;
    }
    if(SOCKET_ERROR == connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen)) {
        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
        return -1;
    }
    if (ConnectSocket == INVALID_SOCKET) {
        freeaddrinfo(ptr);
        WSACleanup();
        return -1;
    }
    return 0;
}

int sendState(uint8_t *data) {
    if(SOCKET_ERROR != send(ConnectSocket, data, 16, 0))
        return 16;
    return -1;
}

#endif
