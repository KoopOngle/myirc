/*
** EPITECH PROJECT, 2018
** handler_chan.c
** File description:
** handler_chan.c
*/


#include "server.h"

void joinhandler(client_t *client, int efd, channel_t *chan)
{
	char *name = strtok(NULL, " ");
	char *tok;
	channel_t *tmp;
	channel_client_t *tmp2;

	if (name)
		name = strdup(cleanstr(name));
	else
		return;
	efd = efd;
	tok = strtok(name, ",");
	while (tok != NULL) {
		tmp = find_inchannel_list(chan, tok);
		if (tmp == NULL) {
			chan = add_tochannel_list(chan, tok);
			chan = find_inchannel_list(chan, tok);
			chan->clients = add_tocli_chan_list(chan->clients, client);
		} else {
			tmp2 = find_incli_chan_list(tmp->clients, client);
			if (tmp2 == NULL)
				chan->clients = add_tocli_chan_list(tmp->clients, client);
			else
				write(client->fd, "443 Already in the channel\r\n", 28);
		}
		tok = strtok(NULL, ",");
	}
}

void parthandler(client_t *client, int efd, channel_t *chan)
{
	char *name = strtok(NULL, " ");
	char *tok;
	channel_t *tmp = chan;

	if (name)
		name = strdup(cleanstr(name));
	else
		return;
	efd = efd;
	tok = strtok(name, ",");
	while (tok != NULL) {
		tmp = find_inchannel_list(chan, tok);
		if (tmp == NULL) {
			write(client->fd, tok, strlen(tok));
			write(client->fd, ": Channel isn't a good chan 403\r\n", 33);
			tok = strtok(NULL, ",");
			continue;
		}
		if (find_incli_chan_list(tmp->clients,client) == NULL)
		{
			write(client->fd, tok, strlen(tok));
			write(client->fd, ": You're not on that channel 442\r\n", 34);
			tok = strtok(NULL, ",");
			continue;
		}
		tmp->clients = suppress_fromcli_chan_list(find_incli_chan_list(chan->clients, client));
		tok = strtok(NULL, ",");
	}
}

void suppress_client_from_chans(client_t *client, channel_t *chan)
{
	channel_client_t *tmp;
	int start = 0;

	chan = chan->head;
	while(chan != chan->head || start == 0) {
		start = 1;
		tmp = find_incli_chan_list(chan->clients, client);
		if (tmp)
			chan->clients = suppress_fromcli_chan_list(tmp);
		chan = chan->next;
	}
}