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

LIB_SRC = exit.c \
	my_error.c \
	garbage_collector.c \
	garbage_llist.c \
	my_strdup.c \
	str_to_word_array.c \
	tablen.c \
	supercat.c \
	get_current_dir.c \
	my_snprintf.c \
	replace_char.c \
	debug_print.c \
	get_uuid_as_string.c \

NETWORK_SRC = get_socket.c \
	connect_to_server.c \
	listen_socket.c \
	accept_socket.c \
	print_fd_set.c \
	get_port.c \

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
