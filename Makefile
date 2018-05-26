##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile for myirc project
##

CC		=		gcc

CFLAGS		+=		-W -Wall -Wextra -g3

CFLAGS		+=		-I./include

CFLAGS		+=		$(DEBUG)

LDFLAGS		+=

NAME		=		server
NAME2		=		client

SRCDIR		=		source

SRCS1		=		$(addprefix $(SRCDIR)/,	\
				mainserver.c		\
				linked_list.c		\
				parsing.c		\
				handlers.c		\
				channel.c		\
				client_channel.c	\
				get_next_line.c)

SRCS2		=		$(addprefix $(SRCDIR)/,	\
				mainclient.c)

OBJDIR		=		build

OBJS		=		$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o,  $(SRCS1))
OBJS2		=		$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o,  $(SRCS2))

all:		$(NAME)
		$(NAME2)
		@echo "Done compiling $(NAME) , $(NAME2)"

$(NAME):	buildrepo $(OBJS)
		@echo "Linking $(NAME)"
		@$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

$(NAME2):
		buildrepo $(OBJS2)
		@echo "Linking $(NAME2)"
		@$(CC) -o $(NAME2) $(OBJS2) $(LDFLAGS)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c
		@echo "->" $<
		@$(CC) -c $< -o $@ $(CFLAGS)

buildrepo:
		@$(call build-repo)

clean:
		@echo "Cleaning object files"
		@rm -rf $(OBJDIR)


fclean:		clean
		@echo "Cleaning binary"
		@rm -f $(NAME)

re:		fclean all

define build-repo
	for dir in $(dir $(OBJS));	\
	do				\
		mkdir -p $$dir;		\
	done
endef

.PHONY: all tests_run buildrepo clean fclean re
