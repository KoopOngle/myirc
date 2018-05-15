/*
** EPITECH PROJECT, 2017
** list_size.c
** File description:
** list_size
*/

#include <stdlib.h>
#include "list.h"

int list_size(list_t *begin)
{
	list_t *tmp = begin;
	int i = 0;

	while (tmp != NULL) {
		i++;
		tmp = tmp->next;
	}
	return (i);
}
