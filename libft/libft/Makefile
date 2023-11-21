SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
	ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
	ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
	ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c \
ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_strlcpy.c ft_abs.c ft_get_max.c ft_get_min.c ft_swap_list.c \
ft_ischar.c

OBJS = ${SRCS:%.c=${OBJS_DIR}/%.o}
OBJS_DIR = ./objs

CC = cc
CFLAGS= -Wall -Wextra -Werror

NAME = libft.a

REMOVE = rm -f
ARRCS = ar rcs

all: ${NAME} 

${OBJS_DIR}/%.o:	%.c
	@${CC} ${CFLAGS} -c $< -o $@

${NAME}: $(OBJS_DIR) ${OBJS}
	@${ARRCS} $(NAME) $(OBJS)
	@echo "Libft.a made!"

$(OBJS_DIR):
	@mkdir -p objs
	@echo "./objs made!"

clean:
	@${REMOVE} ${OBJS}
	@echo "Libft objects removed!"

fclean: clean
	@${REMOVE} ${NAME}
	@echo "Libft.a removed!"

re: fclean all

.PHONY: all clean fclean re
