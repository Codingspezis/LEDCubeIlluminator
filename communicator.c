#include <stdio.h>
#include <string.h>
#include <stdint.h>

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
