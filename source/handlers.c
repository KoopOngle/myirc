/*
** EPITECH PROJECT, 2018
** handlers.c
** File description:
** handlers.c
*/

#include "server.h"

void nickhandler(client_t *client, int efd, channel_t *chan)
{
	client_t *tmp = client->head;
	char *name = strtok(NULL, " ");
	int start = 1;
	int test = 0;

	chan = chan;
	efd = efd;
	if (name)
		name = strdup(cleanstr(name));
	else
		return;
	if (!name || name[0] == '\0')
		write(client->fd, "431 No nickname given\r\n", 23);
	while (tmp != client->head || start == 1) {
		start = 0;
		if (tmp == client) {
			tmp = tmp->next;
			continue;
		}
		if (tmp->nick != NULL && strcasecmp(tmp->nick, name) == 0)
		{
			test = 1;
			break;
		}
		tmp = tmp->next;
	}
	if (test == 1)
		write(client->fd, "433 Nickname already used\r\n", 27);
	else {
		client->nick = strdup(name);

		if (client->user != 0)
			write(client->fd, "001 Welcome\r\n", 13);
	}
	printf("NICK handled %d\n", client->fd);
}

void userhandler(client_t *client, int efd, channel_t *chan)
{
	chan = chan;
	efd = efd;
	client->user = 1;
	if (client->nick != NULL)
		write(client->fd, "001 Welcome\r\n", 13);
}

void passhandler(client_t *client, int efd, channel_t *chan)
{
	chan = chan;
	efd = efd;
	client->fd = client->fd;
}

void usershandler(client_t *client, int efd, channel_t *chan)
{
	client_t *tmp = client->head;
	int start = 1;

	chan = chan;
	efd = efd;
	write(client->fd, "Users list : \n", 14);
	while (tmp && (tmp != client->head || start == 1)){
		start = 0;
		if (tmp->nick) {
			write(client->fd, tmp->nick, strlen(tmp->nick));
			write(client->fd, "\n", 1);
		}
		tmp = tmp->next;
	}
}

void quithandler(client_t *client, int efd, channel_t *chan)
{
	printf("Closed connection on descriptor %d\n", client->fd);
	epoll_ctl(efd, EPOLL_CTL_DEL, client->fd, NULL);
	shutdown(client->fd, SHUT_RDWR);
	close(client->fd);
	suppress_client_from_chans(client, chan);
	client = suppress_from_list(client);
	//ecrire a tout le monde qu'il a quit
}