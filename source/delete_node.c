/*
** EPITECH PROJECT, 2017
** delete_node.c
** File description:
** deleting node by referencing the pointer to be delete
*/

#include <stdlib.h>
#include "list.h"
#include "env.h"
#include "string.h"

int delete_node(list_t **begin, list_t *node)
{
        list_t *ptrPre = *begin;
        list_t *tmp = ptrPre;

	if (tmp && node && tmp == node) {
		*begin = ptrPre->next;
		ptrPre = *begin;
		free(tmp);
		return (0);
	}
        tmp = ptrPre;
        while (tmp != NULL) {
                if (tmp == node) {
                        ptrPre->next = tmp->next;
			free(tmp);
			return (0);
                } else
                        ptrPre = tmp;
                tmp = tmp->next;
        }
        return (0);
}
