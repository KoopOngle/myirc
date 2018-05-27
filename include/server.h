/*
** EPITECH PROJECT, 2018
** server.h
** File description:
** server.h
*/

#ifndef SERVER_H_
 #define SERVER_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/epoll.h>
#include "linked_list.h"
#include <errno.h>


#define READ_SIZE 1
#define NB_COM 8
#define MAXEVENTS 1024

typedef struct handle_s {
	const char *string;
	void (*handler)(client_t*, int efd, channel_t *chan);
	const char *help;
} handle_t;

char *get_next_line(const int fd);
char *cleanstr(char *str);
void handle_command(char *str, client_t *client, int efd, channel_t *chan);
int read_client(client_t *client, int fd_event, int efd, channel_t *chan);
void accept_client(int efd, client_t *client, int fd, channel_t *chan);
void usershandler(client_t *client, int efd, channel_t *chan);
void userhandler(client_t *client, int efd, channel_t *chan);
void quithandler(client_t *client, int efd, channel_t *chan);
void passhandler(client_t *client, int efd, channel_t *chan);
void nickhandler(client_t *client, int efd, channel_t *chan);
void privmsghandler(client_t *client, int efd, channel_t *chan);
void suppress_client_from_chans(client_t *client, channel_t *chan);
void nameshandler(client_t *client, int efd, channel_t *chan);
void parthandler(client_t *client, int efd, channel_t *chan);
void joinhandler(client_t *client, int efd, channel_t *chan);


static const handle_t handlers[NB_COM] = {
	{"USER", &userhandler, "\t<SP> <username> <CRLF>\t\t: Specify user for authentication"},
	{"NICK", &nickhandler, "\t<SP> <password> <CRLF>\t\t: Specify password for authentication"},
	{"JOIN", &joinhandler, "\tCWD  <SP> <pathname> <CRLF>\t: Change working directory"},
	{"PART", &parthandler, "\t<CRLF>\t\t\t\t: Change working directory to parent directory"},
	{"USERS", &usershandler, "\t<CRLF>\t\t\t\t: Disconnection"},
	{"NAMES", &nameshandler, "\t<SP> <pathname> <CRLF>\t\t: Delete file on the server"},
	{"PRIVMSG", &privmsghandler, "\t<CRLF>\t\t\t\t: Print working directory"},
	{"QUIT", &quithandler, "bru"}
	};


#endif /* !SERVER_H_ */
