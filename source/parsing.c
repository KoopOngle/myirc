/*
** EPITECH PROJECT, 2018
** parsing.c
** File description:
** parsing.c
*/

#include "server.h"


char *cleanstr(char *str)
{
	int i = 0;

	if (!str)
		return(NULL);
	while(str[i] != '\0')
		i++;
	i--;
	while((str[i] >= 127 || str[i] <= 32) && i > 0) {
		str[i] = '\0';
		i--;
	}
	return(str);
}

void handle_command(char *str, client_t *client, int efd, channel_t *channel)
{
	char *firststr = cleanstr(strtok(str, " "));
	int i = 0;

	if (!firststr || str[0] == '\0' || str[0] == '\n')
		return;
	while (i < NB_COM && strcasecmp(firststr, handlers[i].string) != 0)
		i++;
	if (i < NB_COM) {
		if (handlers[i].handler)
			handlers[i].handler(client, efd, channel);
		else
			write(client->fd, "502 Can't handle this command.\r\n", 32);
	} else {
		//Ecrire aux potes
		write(client->fd, "500 Unknown command.\r\n", 22);
	}
}

int read_client(client_t *client, int fd_event, int efd, channel_t *channel)
{
	char *cmd = get_next_line(fd_event);
	int i = 0;

	if (cmd != NULL) {
		handle_command(cmd, find_in_list(client, fd_event), efd, channel);
	}
	else {
		quithandler(find_in_list(client, fd_event), efd, channel);
		return (1);
	}
	printf("Return :%d\n", i);

	return(0);
}

void accept_client(int efd, client_t *client, int fd, channel_t *chan)
{
	struct sockaddr in_addr;
	socklen_t in_len = sizeof(in_addr);
	int infd;
	int test;
	struct epoll_event ev;

	infd = accept(fd, &in_addr, &in_len);
	if (infd == -1) {
		perror ("accept");
		return;
	} else {
		printf("Accepted connection on descriptor %d\n", infd);
		client = add_to_list(client, infd);
		printallchan(chan);
		printf("----------\n");
		chan = find_inchannel_list(chan, "*");
		printallchan(chan);
		printf("----------\n");
		chan->clients = add_tocli_chan_list(chan->clients, client);
		printallchan(chan);
		printf("----------\n");
	}
	ev.data.fd = infd;
	ev.events = EPOLLIN;
	test = epoll_ctl(efd, EPOLL_CTL_ADD, infd, &ev);
	if (test == -1)
	{
		perror ("epoll_ctl");
		exit (84);
	}
}