#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int
main(int argc, char *argv[])
{
	int fd, sockfd;
	struct sockaddr_in sin;
	struct sockaddr sclient;
	socklen_t addrlen;
	char buf[1024];
	int nr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) {
		err(EXIT_FAILURE, "socket failed");
	}
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = 0;
	sin.sin_port = htons(9999);
	if(bind(sockfd, (struct sockaddr *)&sin, sizeof(sin)) < 0){
		err(EXIT_FAILURE, "bind failed");
	}
	if(listen(sockfd, 100) < 0){ //como mucho 100 clientes en la cola
		err(EXIT_FAILURE, "listen failed");
	}

	addrlen = sizeof(sclient);
	fd = accept(sockfd, &sclient, &addrlen);
	if(sockfd < 0){
		err(EXIT_FAILURE, "accept failed");
	}
	while((nr = read(fd, buf, 1024)) > 0){
		if(write(1, buf, nr) != nr){
			err(EXIT_FAILURE, "write failed");
		}
	}
	if(nr < 0){
		err(EXIT_FAILURE, "read failed");
	}
	close(fd);
	close(sockfd);
	exit(EXIT_SUCCESS);
}
