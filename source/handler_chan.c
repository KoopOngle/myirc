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
	channel_t *tmp = find_inchannel_list(chan, name);
	channel_client_t *tmp2;

	if (name)
		name = strdup(cleanstr(name));
	else
		return;
	efd = efd;
	if (tmp == NULL) {
		chan = add_tochannel_list(chan, name);
		chan = find_inchannel_list(chan, name);
		chan->clients = add_tocli_chan_list(chan->clients, client);
	} else {
		tmp2 = find_incli_chan_list(tmp->clients, client);
		if (tmp2 == NULL)
			chan->clients = add_tocli_chan_list(tmp->clients, client);
		else
			write(client->fd, "443 Already in the channel\r\n", 28);
	}
}

void parthandler(client_t *client, int efd, channel_t *chan)
{
	char *name = strtok(NULL, " ");

	if (name)
		name = strdup(cleanstr(name));
	else
		return;
	efd = efd;
	chan = find_inchannel_list(chan, name);
	if (chan == NULL) {
		write(client->fd, "403 Channel isn't a good chan\r\n", 31);
		return;
	}
	if (find_incli_chan_list(chan->clients,client) == NULL)
	{
		write(client->fd, "442 You're not on that channel\r\n", 32);
		return;
	}
	chan->clients = suppress_fromcli_chan_list(find_incli_chan_list(chan->clients, client));
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