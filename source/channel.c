/*
** EPITECH PROJECT, 2017
** main.c
** File description:
** main test for linked list
*/

#include "linked_list.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"

channel_t *find_inchannel_list(channel_t *channel_list, char *name)
{
	channel_list = channel_list->head;
	if (strcmp(channel_list->name, name) == 0)
		return (channel_list);
	channel_list = channel_list->next;
	while (channel_list != channel_list->head)
	{
		if (strcmp(channel_list->name, name) == 0)
			return (channel_list);
		channel_list = channel_list->next;
	}
	return (NULL);
}

channel_t *initchannel()
{
	channel_t *channel_list;
	channel_list = malloc(sizeof(channel_t) * 1);
	channel_list->next = channel_list;
	channel_list->prev = channel_list;
	channel_list->head = channel_list;
	channel_list->name = NULL;
	return (channel_list);
}

channel_t *suppress_fromchannel_list(channel_t *channel_list)
{
	channel_t *newchannel;

	if (channel_list == NULL)
		return (NULL);
	if (channel_list->head == channel_list)
	{
		if (channel_list->next == channel_list)
		{
			channel_list->next = channel_list;
			channel_list->prev = channel_list;
			channel_list->head = channel_list;
			channel_list->name = NULL;
			return (channel_list);
		}
		newchannel = channel_list->next;
		while (newchannel != channel_list)
		{
			newchannel->head = channel_list->next;
			newchannel = newchannel->next;
		}
	}
	channel_list->prev->next = channel_list->next;
	channel_list->next->prev = channel_list->prev;
	newchannel = channel_list->next;
	free(channel_list);
	return (newchannel);
}

channel_t *add_tochannel_list(channel_t *channel_list, char *name)
{
	channel_t *newchannel;
	if (channel_list == NULL)
		return (NULL);
	if (channel_list->name == NULL)
	{
		channel_list->name = strdup(name);
		return (channel_list);
	} else
	{
		newchannel = malloc(sizeof(channel_t) * 1);
		channel_list = channel_list->head->prev;
		newchannel->name = strdup(name);
		newchannel->prev = channel_list;
		newchannel->head = channel_list->head;
		newchannel->next = newchannel->head;
		if (channel_list->head->next == channel_list->head)
			channel_list->head->next = newchannel;
		channel_list->head->prev = newchannel;
		channel_list->next = newchannel;
	}
	return (newchannel);
}