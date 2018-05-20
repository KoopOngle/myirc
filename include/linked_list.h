/*
** EPITECH PROJECT, 2018
** linked list header
** File description:
** linked list struct
*/

#ifndef LINKED_LIST_H
# define LINKED_LIST_H

typedef struct  s_list
{
    struct s_list       *prev;
    struct s_list       *next;
    struct s_list       *head;
    int     fd;
    char   *nick;
}               client_t;

client_t *find_in_list(client_t *fd_list, int fd);
client_t *initclient();
client_t *suppress_from_list(client_t *fd_list);
client_t *add_to_list(client_t *fd_list, int fd);

#endif /* !LINKED_LIST_H */
