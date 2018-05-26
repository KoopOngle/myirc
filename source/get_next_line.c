/*
** EPITECH PROJECT, 2017
** get_next_line.c
** File description:
** get the next line
*/

#include "server.h"
#include <stdlib.h>
#include <unistd.h>

static int my_strcat(char *dest, char const *src, int j)
{
	int i = 0;

	while (dest && dest[i] != '\0')
		i++;
	while (src && dest && src[j] != '\0' && src[j] != '\n') {
		dest[i++] = src[j++];
	}
	if (dest)
		dest[i] = '\0';
	if (src && src[j] == '\n') {
		return (j + 1);
	}
	else
		return (0);
}

char *my_realloc(char *dest, int val_realloc)
{
	char *reallocdest = malloc(sizeof(char) * val_realloc + 1);

	if (reallocdest)
		reallocdest[0] = '\0';
	if (reallocdest && dest) {
		my_strcat(reallocdest, dest, 0);
		free(dest);
	}
	return (reallocdest);
}

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

static char* res(char *result, int i, int size)
{
	if (result == NULL || (result[0] == '\0' && i == 0 && size < 1)) {
		if (result)
			free(result);
		return (NULL);
	}
	return (result);
}

char *get_next_line(const int fd)
{
	static int size = 1;
	static char buffer[READ_SIZE + 1];
	static int i = 0;
	int mallocsize = READ_SIZE;
	char *result = malloc(sizeof(char) * mallocsize + 1);

	if (result)
		result[0] = 0;
	raz(result);
	i = my_strcat(result, buffer, i);
	while (result && size > 0 && i == 0) {
		raz(buffer);
		size = read(fd, buffer, READ_SIZE);
		if (size > 0) {
			mallocsize += READ_SIZE;
			result = my_realloc(result, mallocsize);
			i = my_strcat(result, buffer, i);
		}
	}
	return (res(result, i, size));
}
