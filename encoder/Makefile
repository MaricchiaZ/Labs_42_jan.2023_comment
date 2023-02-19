NAME	= encoder

CC	= cc
INCLUDE	= -I ./include/
CFLAGS	= -g -Wall -Wextra -Werror $(INCLUDE)

RM	= rm -rf

PATH_SRCS	= ./srcs/
PATH_OBJS	= ./objs/

SRCS	= $(PATH_SRCS)main.c \
		$(PATH_SRCS)args_to_text.c \
		$(PATH_SRCS)frequency_table.c \
		$(PATH_SRCS)list.c \
		$(PATH_SRCS)huffman_tree.c \
		$(PATH_SRCS)dictionary.c \
		$(PATH_SRCS)encode_text.c \
		$(PATH_SRCS)compress.c \
		$(PATH_SRCS)shared_mem.c \
		$(PATH_SRCS)print_text_infos.c \
		$(PATH_SRCS)utils.c \

OBJS	= $(patsubst $(PATH_SRCS)%.c, $(PATH_OBJS)%.o, $(SRCS))

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS)  $(OBJS) -o $(NAME) $(MLXFLAGS)

$(PATH_OBJS)%.o:	$(PATH_SRCS)%.c
		@mkdir -p $(PATH_OBJS)
		$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) ./objs

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all $(PATH_OBJS) clean fclean re