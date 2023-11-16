SRCS = ft_helper.c ft_printf.c ft_print_u_d_i.c ft_print_p_x_ux.c ft_print_per_s_c.c\
ft_base_converter.c get_next_line.c get_next_line_utils.c

OBJS = ${SRCS:%.c=${OBJS_DIR}/%.o}
OBJS_DIR = ./objs

INCLUDES = ./includes

ARRCS = ar rcs
NAME = libftprintf.a

REMOVE = rm -f

CC = cc
CFLAGS = -Wall -Wextra -Werror


LIBFT_DIR = ./libft
LIBFT = ${LIBFT_DIR}/libft.a

MAIN = main.c

all: ${NAME}

${OBJS_DIR}/%.o:	%.c
	${CC} ${CFLAGS} -c $< -o $@

${NAME}:		${LIBFT} ${OBJS_DIR} ${OBJS}
	cp	${LIBFT} ${NAME}
	${ARRCS} ${NAME} ${OBJS}

${LIBFT}:
	make -C ${LIBFT_DIR} all

${OBJS_DIR}:
	mkdir -p ${OBJS_DIR}

clean:
	make -C ${LIBFT_DIR} clean
	${RM} ${OBJS}

fclean:	clean
	make -C ${LIBFT_DIR} fclean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
