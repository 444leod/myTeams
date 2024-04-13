##
## EPITECH PROJECT, 2024
## myteams_client
## File description:
## Makefile
##

NAME = myteams_cli

SRC = main.c \
	$(addprefix src/, $(SRC_SRC)) \
	$(addprefix src/network/client_linked_list/, $(CLIENT_LLIST_SRC)) \
	$(addprefix src/commands/, $(COMMANDS_SRC)) \
	$(addprefix src/packet_handlers/, $(PACKET_HANDLER_SRC)) \

SRC_SRC = client.c \
	check_args.c \
	parse_reply.c \
	exit.c \
	is_logged.c \
	input_processing.c \

PACKET_HANDLER_SRC = buffer.c \
	userinfo.c \
	error.c

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -Wpedantic -I./include -I../include \
	-luuid -L ../libs/myteams/ -lmyteams -L ../ -lmy -lnetwork \
	-I ../libs/myteams

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

tests_run:
	exit 0

run: all

debug:
	$(CC) -o $(NAME) $(SRC) $(CFLAGS) -g

dev:
	$(CC) -o $(NAME) $(SRC) $(CFLAGS) -g -DDEV_MODE

.PHONY: all clean fclean re
.SILENT: run
