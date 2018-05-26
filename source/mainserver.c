/*
** EPITECH PROJECT, 2018
** mainserver.c
** File description:
** mainserver.c
*/

#include "server.h"
#include "linked_list.h"


int testError( struct epoll_event *events, int i)
{
	if ((events[i].events & EPOLLERR)
	|| (events[i].events & EPOLLHUP)
	|| !(events[i].events & EPOLLIN)) {
		fprintf (stderr, "epoll error\n");
		close (events[i].data.fd);
		return 1;
	}
	return 0;
}

int accept_func(int fd)
{
	client_t *fd_list = initclient();
	int efd, test, i, n;
	struct epoll_event event;
 	struct epoll_event *events;
	channel_t *chan_list = initchannel();

	efd = epoll_create1(0);
	chan_list = add_tochannel_list(chan_list, "*");
	if (efd == -1) {
		perror("create");
		close(fd);
		exit(84);
	}
	event.data.fd = fd;
	event.events = EPOLLIN;
	test = epoll_ctl(efd, EPOLL_CTL_ADD, fd, &event);
	if (test == -1){
		perror("epoll_ctl");
		close(fd);
		exit(84);
	}
	events = calloc(MAXEVENTS, sizeof(event));

	while (2727) {
		n = epoll_wait (efd, events, MAXEVENTS, -1);
		printf("n:[%d]\n", n);
		for (i = 0; i < n; i++) {
			if (testError(events, i))
				continue;
			if (events[i].data.fd == fd) {
				accept_client(efd, fd_list, fd, chan_list);
			}
			else {
				read_client(fd_list, events[i].data.fd, efd, chan_list);
			}
		}
	}
	free (events);
	close(fd);
	return (0);
}

int init_all(int port)
{
	struct protoent *pe;
	int fd;
	struct sockaddr_in s_in;

	pe = getprotobyname("TCP");
	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(port);
	s_in.sin_addr.s_addr = INADDR_ANY;
	if (!pe)
		return(1);
	fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (fd == -1)
		return(1);
	if (bind(fd, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1) {
		close(fd);
		return(1);
	}
	if (listen(fd, SOMAXCONN) == -1) {
		close(fd);
		return(1);
	}
	accept_func(fd);
	return(fd);
}

int main(int argc, char **argv)
{
	int port;
	int fd;

	if (argc != 2)
		return(1);
	port = atoi(argv[1]);
	fd = init_all(port);
	if (close(fd) == -1)
		return (1);
	return(0);
}
