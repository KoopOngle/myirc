/*
** EPITECH PROJECT, 2018
** handlers.c
** File description:
** handlers.c
*/


/*
431 ERR_NONICKNAMEGIVEN
":No nickname given"
Renvoyé quand un paramètre pseudonyme attendu pour une commande n'est pas fourni.

432 ERR_ERRONEUSNICKNAME
"<pseudo> :Erroneus nickname"
Renvoyé après la réception d'un message NICK qui contient des caractères qui ne font pas partie du jeu autorisé. Voir les sections 1 et 2.2 pour les détails des pseudonymes valides.

433 ERR_NICKNAMEINUSE
"<nick> :Nickname is already in use"
Renvoyé quand le traitement d'un message NICK résulte en une tentative de changer de pseudonyme en un déjà existant.

436 ERR_NICKCOLLISION
"<nick> :Nickname collision KILL"
*/

#include "server.h"

void nickhandler(client_t *client, int efd)
{
	client_t *tmp = client->head;
	char *name = strdup(cleanstr(strtok(NULL, " ")));
	int start = 1;
	int test = 0;

	efd = efd;
	if (!name || name[0] == '\0')
		write(client->fd, "431 No nickname given\r\n", 23);
	while (tmp != client->head || start == 1) {
		start = 0;
		if (tmp == client) {
			tmp = tmp->next;
			continue;
		}
		if (tmp->nick != NULL && strcasecmp(tmp->nick, name) == 0)
		{
			test = 1;
			break;
		}
		tmp = tmp->next;
	}
	if (test == 1)
		write(client->fd, "433 Nickname already used\r\n", 27);
	else {
		client->nick = strdup(name);

		if (client->user != 0)
			write(client->fd, "001 Welcome\r\n", 13);
		//write(client->fd, "Bonjour ", 8);
		//write(client->fd, name, strlen(name));
		//write(client->fd, " 001\r\n", 6);
	}
	printf("NICK handled %d\n", client->fd);
}

void userhandler(client_t *client, int efd)
{
	efd = efd;
	client->user = 1;
	printf("USERRRRRRRRRrr\n");
	if (client->nick != NULL)
		write(client->fd, "001 Welcome\r\n", 13);
}

void passhandler(client_t *client, int efd)
{
	efd = efd;
	client->fd = client->fd;
}

void usershandler(client_t *client, int efd)
{
	client_t *tmp = client->head;
	int start = 1;

	efd = efd;
	write(client->fd, "Users list : \n", 14);
	while (tmp && (tmp != client->head || start == 1)){
		start = 0;
		if (tmp->nick) {
			write(client->fd, tmp->nick, strlen(tmp->nick));
			write(client->fd, "\n", 1);
		}
		tmp = tmp->next;
	}
}

void quithandler(client_t *client, int efd)
{
	printf("Closed connection on descriptor %d\n", client->fd);
	epoll_ctl(efd, EPOLL_CTL_DEL, client->fd, NULL);
	shutdown(client->fd, SHUT_RDWR);
	close(client->fd);
	client = suppress_from_list(client);
	//ecrire a tout le monde qu'il a quit
}