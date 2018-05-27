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

client_t *find_in_list(client_t *fd_list, int fd)
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

client_t *initclient()
{
        client_t *fd_list;
        fd_list = malloc(sizeof(client_t) * 1);
        fd_list->next = fd_list;
        fd_list->prev = fd_list;
        fd_list->head = fd_list;
        fd_list->fd = -1;
        return (fd_list);
}

client_t *suppress_from_list(client_t *fd_list)
{
        client_t *newfd;

        if (fd_list == NULL)
                return (NULL);
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

char *create_nick(int fd) {
        char *nick = malloc(100);
        sprintf(nick, "Guest%d", fd);
        return nick;
}

client_t *add_to_list(client_t *fd_list, int fd)
{
        client_t *newfd;
        if (fd_list == NULL)
                return (NULL);
        if (fd_list->fd == -1)
        {
                fd_list->fd = fd;
                fd_list->nick = create_nick(fd);
                return (fd_list);
        } else
        {
                newfd = malloc(sizeof(client_t) * 1);
                fd_list = fd_list->head->prev;
                newfd->fd = fd;
                newfd->prev = fd_list;
                newfd->head = fd_list->head;
                newfd->next = newfd->head;
                newfd->user = 0;
                newfd->nick = create_nick(fd);
                if (fd_list->head->next == fd_list->head)
                        fd_list->head->next = newfd;
                fd_list->head->prev = newfd;
                fd_list->next = newfd;
        }
        return (newfd);
}