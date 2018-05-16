/*
** EPITECH PROJECT, 2017
** my_list_size
** File description:
** my list size
*/

#include <stdlib.h>
#include "list.h"

int put_in_list(list_t **list, void *data)
{
	list_t *element;
	list_t *tmp = *list;

	element = malloc(sizeof(*element));
	element->data = data;
	element->next = NULL;
	if (list && *list) {
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = element;
	} else
		*list = element;
	return (0);
}
