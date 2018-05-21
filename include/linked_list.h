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

typedef struct  s_channel_client
{
    struct s_channel_client       *prev;
    struct s_channel_client       *next;
    struct s_channel_client       *head;
    client_t    *client;
}               channel_client_t;

typedef struct  s_channel
{
    struct s_channel       *prev;
    struct s_channel       *next;
    struct s_channel       *head;
    channel_client_t       *clients;
    char   *name;
}               channel_t;

channel_client_t *find_incli_chan_list(channel_client_t *cli_chan_list, client_t *client);
channel_client_t *suppress_fromcli_chan_list(channel_client_t *cli_chan_list);
channel_client_t *add_tocli_chan_list(channel_client_t *cli_chan_list, client_t *client);
channel_client_t *initcli_chan();
channel_t *find_inchannel_list(channel_t *channel_list, char *name);
channel_t *initchannel();
channel_t *suppress_fromchannel_list(channel_t *channel_list);
channel_t *add_tochannel_list(channel_t *channel_list, char *name);
client_t *find_in_list(client_t *fd_list, int fd);
client_t *initclient();
client_t *suppress_from_list(client_t *fd_list);
client_t *add_to_list(client_t *fd_list, int fd);

#endif /* !LINKED_LIST_H */
