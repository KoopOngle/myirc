/*
** EPITECH PROJECT, 2018
** handler_names.c
** File description:
** handler_names.c
*/

#include "server.h"

void write_client(client_t *client, client_t *recever, char *to_send)
{
	write(recever->fd, ":", 1);
	write(recever->fd, client->nick, strlen(client->nick));
	write(recever->fd, " PRIVMSG client ", 16);
	write(recever->fd, recever->nick, strlen(recever->nick));
	write(recever->fd, ":", 1);
	write(recever->fd, to_send, strlen(to_send));
	write(recever->fd, "\r\n", 2);
}

int search_and_write_in_client(client_t *client, char *name, char *to_send)
{
	client_t *tmp = client->head;
	int start = 0;

	while ((tmp && tmp != client->head) || start == 0) {
		start = 1;
		if (strcmp(tmp->nick, name) == 0) {
			write_client(client, tmp, to_send);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void write_chan(client_t *client, channel_t *chan, char *to_send)
{
	channel_client_t *tmp = chan->clients->head;
	int start = 0;

	while ((tmp && tmp != chan->clients->head) || start == 0) {
		start = 1;
		if (tmp->client != client) {
			write(tmp->client->fd, ":", 1);
			write(tmp->client->fd, client->nick, strlen(client->nick));
			write(tmp->client->fd, " PRIVMSG chan ", 14);
			write(tmp->client->fd, chan->name, strlen(chan->name));
			write(tmp->client->fd, ":", 1);
			write(tmp->client->fd, to_send, strlen(to_send));
			write(tmp->client->fd, "\r\n", 2);
		}
		tmp = tmp->next;
	}
}

int search_and_write_in_chan(client_t *client, channel_t *chan, char *name, char *to_send)
{
	channel_t *tmp = chan->head;
	int start = 0;

	while ((tmp && tmp != chan->head) || start == 0) {
		start = 1;
		if (strcmp(tmp->name, name) == 0) {
			write_chan(client, tmp, to_send);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void privmsghandler(client_t *client, int efd, channel_t *chan)
{
	client = client;
	efd = efd;
	chan = chan;

	char *chans_name = strtok(NULL, " ");
	char *to_send = strtok(NULL, "");
	char *name;

	if (chans_name && to_send) {
		chans_name = strdup(cleanstr(chans_name));
		to_send = strdup(cleanstr(to_send));
	}
	else
		return;
	name = strtok(chans_name, ",");
	while (name != NULL) {
		printf("%s\n", name);
		if (search_and_write_in_chan(client, chan, name , to_send) == 0)
			search_and_write_in_client(client, name, to_send);
		name = strtok(NULL, ",");
	}
}

