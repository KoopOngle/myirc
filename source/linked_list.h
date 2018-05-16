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
}               t_list;

#endif /* !LINKED_LIST_H */
