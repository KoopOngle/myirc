/*
** EPITECH PROJECT, 2018
** mainserver.c
** File description:
** mainserver.c
*/

#include "server.h"


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
	int efd, test, i, n;
	struct epoll_event event;
 	struct epoll_event *events;
	efd = epoll_create1(0);
	if (efd == -1)
	{
		perror("create");
		close(fd);
		exit(84);
	}
	event.data.fd = fd;
	event.events = EPOLLIN | EPOLLET;
	test = epoll_ctl(efd, EPOLL_CTL_ADD, fd, &event);
	if (test == -1){
		perror("epoll_ctl");
		close(fd);
		exit(84);
	}
	events = calloc(MAXEVENTS, sizeof(event));

	while (2727) {
		n = epoll_wait (efd, events, MAXEVENTS, -1);
		for (i = 0; i < n; i++) {
			if (testError(events, i))
				continue;
			else if (events[i].data.fd == fd) {
				// là ça veut dire qu'il y a une nouvelle connection
				while (1) {
					struct sockaddr in_addr;
					socklen_t in_len = sizeof(in_addr);
					int infd;
					char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];

					infd = accept(fd, &in_addr, &in_len);
					if (infd == -1)
					{
						if ((errno == EAGAIN) ||
						(errno == EWOULDBLOCK))
						{
							/* We have processed all incoming
							connections. */
							break;
						}
					}
					else
					{
						perror ("accept");
						break;
					}
					test = getnameinfo (&in_addr, in_len,
							hbuf, sizeof(hbuf),
							sbuf, sizeof (sbuf),
							NI_NUMERICHOST | NI_NUMERICSERV);
					if (test == 0)
					{
						printf("Accepted connection on descriptor %d "
						"(host=%s, port=%s)\n", infd, hbuf, sbuf);
					}
					event.data.fd = infd;
					event.events = EPOLLIN | EPOLLET;
					test = epoll_ctl (efd, EPOLL_CTL_ADD, infd, &event);
					if (test == -1)
					{
						perror ("epoll_ctl");
						exit (84);
					}
				}
				continue;
			}
			else {
				//Là c'est quand on a des data a récup dans le fd
				int done = 0;

				while (9393) {
					//Ici ça va être la fonction read mamene
					ssize_t count;
					char buf[512];

					count = read(events[i].data.fd, buf, sizeof(buf));
					if (count == -1) {
						if (errno != EAGAIN) // en gros si c'est égale a ça c'ets que ça a fini de read
							{
								perror ("read");
								done = 1;
							}
						break;
					}
					else if (count == 0) {
						//fin du file donc close connection
						done = 1;
						break;
					}
					test = write(1, buf, count);
					if (test == -1) {
						perror("write");
						exit(84);
					}
				}
				if (done) {
					printf ("Closed connection on descriptor %d\n",
					events[i].data.fd);
					/* Closing the descriptor will make epoll remove it
					from the set of descriptors which are monitored. */
					close (events[i].data.fd);
				}
			}
		}
	}
	free (events);
	close(fd);
	return (0);
}


/*void client_read(t_env *e, int fd)
{
	int r;
	char buf[4096];

	r = read(fd, buf, 4096);
	if (r > 0)
	{
		buf[r] = ’\0’;
		printf("%d: %s\n", fd, buf);
	}
	else
	{
		printf("%d: Connection closed\n");
		close(fd);
		e->fd_type[fd] = FD_FREE;
	}
}*/

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

	if (argc != 3)
		return(1);
	port = atoi(argv[1]);
	if (chdir(argv[2]) == -1)
		return(1);
	fd = init_all(port);
	if (close(fd) == -1)
		return (1);
	return(0);
}