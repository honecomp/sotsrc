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
	struct sockaddr_in sin;
	int fd;
	char buf[512];
 	int nr;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if(fd < 0) {
		err(EXIT_FAILURE, "socket failed");
	}
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");
	sin.sin_port = htons(9999);
 	if(connect(fd, (struct sockaddr *)&sin, sizeof(struct sockaddr)) == -1){
		err(EXIT_FAILURE, "connect failed");
 	}
	while((nr = read(0, buf, 512)) > 0){
		if(write(fd, buf, nr) != nr) {
			err(EXIT_FAILURE, "write failed");
		}
	}
	if(nr < 0){
		err(EXIT_FAILURE, "read failed");
	}
	close(fd);
	exit(EXIT_SUCCESS);
}
