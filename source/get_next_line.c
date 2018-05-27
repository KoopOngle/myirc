/*
** EPITECH PROJECT, 2017
** get_next_line.c
** File description:
** get the next line
*/

#include "server.h"
#include <stdlib.h>
#include <unistd.h>

static void raz(char *str)
{
	int i = 0;

	if (str == NULL)
		return;
	while (str[i] != '\0') {
		str[i] = 0;
		i++;
	}
}

char *get_next_line(const int fd)
{
	int size = 1;
	char buffer[512];
	int mallocsize = 1;
	char *result = malloc(sizeof(char) * mallocsize + 1);

	if (result == NULL)
		return (NULL);
	result[0] = 0;
	while (result && size > 0) {
		raz(buffer);
		size = read(fd, buffer, 1);
		if (size > 0) {
			mallocsize += 1;
			buffer[size] = '\0';
			result = realloc(result, mallocsize);
			strcat(result, buffer);
		}
		else
			return (NULL);
		if (size > 0 && buffer[0] == '\n')
			break;
	}
	result[strlen(result) - 1] = 0;
	return (result);
}
