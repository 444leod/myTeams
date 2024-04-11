##
## EPITECH PROJECT, 2024
## myteams_server
## File description:
## Makefile
##

NAME = myteams_server

SRC = main.c \
	$(addprefix src/, $(SRC_SRC)) \
	$(addprefix src/lib/, $(LIB_SRC)) \
	$(addprefix src/network/, $(NETWORK_SRC)) \
	$(addprefix src/network/client_linked_list/, $(CLIENT_LLIST_SRC)) \
	$(addprefix src/network/user_linked_list/, $(USER_LLIST_SRC)) \
	$(addprefix src/commands/, $(COMMANDS_SRC)) \

SRC_SRC = server.c \
	check_args.c \
	handle_clients.c \
	handle_commands.c \

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
	escaped_string.c \
	get_uuid_as_string.c \
	magic_number.c \

COMMANDS_SRC = commands.c \
	create.c \
	help.c \
	info.c \
	list.c \
	login.c \
	logout.c \
	messages.c \
	send.c \
	subscribe.c \
	subscribed.c \
	unsubscribe.c \
	use.c \
	user.c \
	users.c \
	unknown_command.c \

NETWORK_SRC = get_socket.c \
	bind_socket.c \
	listen_socket.c \
	accept_socket.c \
	reply_code.c \
	special_print.c \
	get_port.c \

CLIENT_LLIST_SRC = add_client.c \
	create_client.c \
	remove_client.c \
	get_clients.c \
	clear_clients.c \

USER_LLIST_SRC = add_user.c \
	dump_users.c \
	get_users.c \
	init_users.c \

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -Wpedantic -I./include -luuid

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

tests_run: all

run: all

debug:
	$(CC) -o $(NAME) $(SRC) $(CFLAGS) -g

dev:
	$(CC) -o $(NAME) $(SRC) $(CFLAGS) -g -DDEV_MODE

.PHONY: all clean fclean re
.SILENT: run
