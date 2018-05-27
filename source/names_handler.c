/*
** EPITECH PROJECT, 2018
** handler_names.c
** File description:
** handler_names.c
*/

#include "server.h"

void name_print_channel_cli(client_t *client, channel_t *chan)
{
	channel_client_t *tmp = chan->clients->head;
	int start = 1;

	if (chan == NULL || chan->name == NULL)
		return;
	write(client->fd, "Name of people in chan : ", 25);
	write(client->fd, chan->name, strlen(chan->name));
	write(client->fd, "\n", 1);
	tmp = chan->clients->head;
	while(tmp && (tmp != chan->clients->head || start == 1)) {
		start = 2;
		if (tmp->client != NULL && tmp->client->nick != NULL) {
			write(client->fd, tmp->client->nick, strlen(tmp->client->nick));
			write(client->fd, "\n", 1);
		}
		tmp = tmp->next;
	}
}

void names_gen_handler(client_t *client, channel_t *chan)
{
	channel_t *tmpchan = chan->head;
	channel_t *general;
	int start = 0;

	while(tmpchan && (tmpchan != chan->head || start == 0)) {
		start = 1;
		if (strcmp(tmpchan->name, "*") == 0) {
			general = tmpchan;
			tmpchan = tmpchan->next;
			continue;
		}
		name_print_channel_cli(client, tmpchan);
		tmpchan = tmpchan->next;
	}
	name_print_channel_cli(client, general);
}

void nameshandler(client_t *client, int efd, channel_t *chan)
{
	char *name = strtok(NULL, " ");
	channel_t *tmp;

	efd = efd;
	if (name == NULL || name[0] == '\0') {
		names_gen_handler(client, chan);
		return;
	}
	name = strdup(cleanstr(name));
	if (strcmp(name, "*") == 0)
		return;
	chan = find_inchannel_list(chan , name);
	if (chan == NULL) {
		printf("bug\n");
		return;
	}
	tmp = chan;
	if (tmp->clients->client == NULL) {
		printf("rien dedant\n");
		return;
	}
	name_print_channel_cli(client, tmp);
}
