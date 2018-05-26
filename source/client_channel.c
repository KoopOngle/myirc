/*
** EPITECH PROJECT, 2017
** client_channel.c
** File description:
** client_channel
*/

#include "linked_list.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"

channel_client_t *find_incli_chan_list(channel_client_t *cli_chan_list, client_t *client)
{
	cli_chan_list = cli_chan_list->head;
	if (cli_chan_list->client == client)
		return (cli_chan_list);
	cli_chan_list = cli_chan_list->next;
	while (cli_chan_list != cli_chan_list->head)
	{
		if (cli_chan_list->client == client)
			return (cli_chan_list);
		cli_chan_list = cli_chan_list->next;
	}
	return (NULL);
}

channel_client_t *initcli_chan()
{
	channel_client_t *cli_chan_list;
	cli_chan_list = malloc(sizeof(channel_client_t) * 1);
	cli_chan_list->next = cli_chan_list;
	cli_chan_list->prev = cli_chan_list;
	cli_chan_list->head = cli_chan_list;
	cli_chan_list->client = NULL;
	return (cli_chan_list);
}

channel_client_t *suppress_fromcli_chan_list(channel_client_t *cli_chan_list)
{
	channel_client_t *newclient;

	if (cli_chan_list == NULL)
		return (NULL);
	if (cli_chan_list->head == cli_chan_list)
	{
		if (cli_chan_list->next == cli_chan_list)
		{
			cli_chan_list->next = cli_chan_list;
			cli_chan_list->prev = cli_chan_list;
			cli_chan_list->head = cli_chan_list;
			cli_chan_list->client = NULL;
			return (cli_chan_list);
		}
		newclient = cli_chan_list->next;
		while (newclient != cli_chan_list)
		{
			newclient->head = cli_chan_list->next;
			newclient = newclient->next;
		}
	}
	cli_chan_list->prev->next = cli_chan_list->next;
	cli_chan_list->next->prev = cli_chan_list->prev;
	newclient = cli_chan_list->next;
	free(cli_chan_list);
	return (newclient);
}

channel_client_t *add_tocli_chan_list(channel_client_t *cli_chan_list, client_t *client)
{
	channel_client_t *newcli;

	if (cli_chan_list == NULL) {
		printf("cli_chan_list null\n");
		return (NULL);
	}
	if (cli_chan_list->client == NULL)
	{
		printf("cli_chan_list->client null\n");
		cli_chan_list->client = client;
		return (cli_chan_list);
	} else
	{
		printf("cli_chan_list else\n");
		newcli = malloc(sizeof(channel_client_t) * 1);
		cli_chan_list = cli_chan_list->head->prev;
		newcli->client = client;
		newcli->prev = cli_chan_list;
		newcli->head = cli_chan_list->head;
		newcli->next = newcli->head;
		if (cli_chan_list->head->next == cli_chan_list->head)
			cli_chan_list->head->next = newcli;
		cli_chan_list->head->prev = newcli;
		cli_chan_list->next = newcli;
	}
	return (newcli);
}