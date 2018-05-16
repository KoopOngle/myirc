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

t_list *find_in_list(t_list *fd_list, int fd)
{
    fd_list = fd_list->head;
    if (fd_list->fd == fd)
        return (fd_list);
    fd_list = fd_list->next;
    while (fd_list != fd_list->head)
    {
        if (fd_list->fd == fd)
            return (fd_list);
        fd_list = fd_list->next;
    }
    return (NULL);
}

t_list *init_list()
{
    t_list *fd_list;
    fd_list = malloc(sizeof(t_list) * 1);
    fd_list->next = fd_list;
    fd_list->prev = fd_list;
    fd_list->head = fd_list;
    fd_list->fd = -1;
    return (fd_list);
}

t_list *suppress_from_list(t_list *fd_list)
{
    t_list *newfd;

    if (fd_list->head == fd_list)
    {
        if (fd_list->next == fd_list)
        {
            fd_list->next = fd_list;
            fd_list->prev = fd_list;
            fd_list->head = fd_list;
            fd_list->fd = -1;
            return (fd_list);
        }
        newfd = fd_list->next;
        while (newfd != fd_list)
        {
            newfd->head = fd_list->next;
            newfd = newfd->next;
        }
    }
    fd_list->prev->next = fd_list->next;
    fd_list->next->prev = fd_list->prev;
    newfd = fd_list->next;
    free(fd_list);
    return (newfd);
}

t_list *add_to_list(t_list *fd_list, int fd)
{
    t_list *newfd;
    if (fd_list->fd == -1)
    {
        fd_list->fd = fd;
        return (fd_list);
    } else
    {
        newfd = malloc(sizeof(t_list) * 1);
        fd_list = fd_list->head->prev;
        newfd->fd = fd;
        newfd->prev = fd_list;
        newfd->head = fd_list->head;
        newfd->next = newfd->head;
        if (fd_list->head->next == fd_list->head)
            fd_list->head->next = newfd;
        fd_list->head->prev = newfd;
        fd_list->next = newfd;
    }
    return (newfd);
}

int main()
{
    int i = 0;
    t_list *fd_list = init_list();
    fd_list = add_to_list(fd_list, 1);
    fd_list = add_to_list(fd_list, 22);
    fd_list = add_to_list(fd_list, 333);
    fd_list = add_to_list(fd_list, 4444);
    fd_list = add_to_list(fd_list, 55555);
    fd_list = fd_list->head;
    fd_list = suppress_from_list(find_in_list(fd_list, 333));
    fd_list = fd_list->head;
    while (i != 5)
    {
        i++;
        printf("%d : %d\n", i, fd_list->fd);
        fd_list = fd_list->next;
    }
    return (0);
}