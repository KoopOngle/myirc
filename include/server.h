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

#define NB_COM 10
#define MAXEVENTS 1024

typedef struct handle_s {
	const char *string;
	void (*handler)(client_t*);
	const char *help;
} handle_t;

char *cleanstr(char *str);
void handle_command(char *str, client_t *client);
int read_client(client_t *client, int fd_event);
void accept_client(int efd, client_t *client, int fd);
void usershandler(client_t *client);
void userhandler(client_t *client);
void quithandler(client_t *client);
void passhandler(client_t *client);
void nickhandler(client_t *client);


static const handle_t handlers[NB_COM] = {
	{"USER", &userhandler, "\t<SP> <username> <CRLF>\t\t: Specify user for authentication"},
	{"NICK", &nickhandler, "\t<SP> <password> <CRLF>\t\t: Specify password for authentication"},
	{"JOIN", NULL, "\tCWD  <SP> <pathname> <CRLF>\t: Change working directory"},
	{"PART", NULL, "\t<CRLF>\t\t\t\t: Change working directory to parent directory"},
	{"USERS", &usershandler, "\t<CRLF>\t\t\t\t: Disconnection"},
	{"NAMES", NULL, "\t<SP> <pathname> <CRLF>\t\t: Delete file on the server"},
	{"PRV", NULL, "\t<CRLF>\t\t\t\t: Print working directory"},
	{"SEND", NULL, "\t<CRLF>\t\t\t\t: Enable \"passive\" mode for data transfer"},
	{"ACCEPT", NULL, "\t<SP> <host-port> <CRLF>\t\t: Enable \"active\" mode for data transfer"},
	{"QUIT", &quithandler, "bru"}
	};


#endif /* !SERVER_H_ */
