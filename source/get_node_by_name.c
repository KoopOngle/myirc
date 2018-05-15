/*
** EPITECH PROJECT, 2017
** get_node_by_name
** File description:
** get the node by the name of the env var
*/

#include <stdlib.h>
#include "list.h"
#include "env.h"
#include "string.h"

list_t *get_node_by_name(list_t **begin, char *name)
{
        list_t *ptrPre = *begin;
        list_t *tmp = ptrPre;
	env_var_t *env_var;

	while (tmp != NULL) {
		env_var = tmp->data;
		if (compare(env_var->name, name) == 0)
			return (tmp);
		tmp = tmp->next;
	}
        return (NULL);
}
