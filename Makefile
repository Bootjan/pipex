MAIN = pipex.c
PATH_CMD = get_cmd.c get_path.c
CMDS = first_cmd.c middle_cmd.c last_cmd.c pipex_utils.c
HERE_DOC = here_doc.c here_doc_last_cmd.c


SRCS = $(PATH_CMD)\
$(CMDS)\
$(HERE_DOC)\
$(MAIN)

OBJS = ${SRCS:%.c=${OBJS_DIR}/%.o}
NAME = pipex
VPATH = . ./cmds ./utils ./path_cmd ./here_doc

I_DIRS := $(shell find . -type f -name "*.h" -exec dirname {} + | uniq)
INCLUDE = ${I_DIRS:%=-I%}
CC = cc
CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g
OBJS_DIR = ./objs

LIB = -L./libft -lftprintf
RM = rm -f

MAKE_LIB = ${MAKE_DIR}/libftprintf.a
MAKE_DIR = ./libft

all:	${NAME}

bonus: all

${NAME}: ${MAKE_LIB} ${OBJS_DIR} ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${LIB} -o ${NAME}

${MAKE_LIB}:
	make -C ${MAKE_DIR} all

${OBJS_DIR}:
	mkdir -p ${OBJS_DIR}

${OBJS_DIR}/%.o:	%.c
	${CC} ${CFLAGS} -c $< -o $@ ${INCLUDE}

clean:	
	make -C ${MAKE_DIR} clean
	${RM} -r ${OBJS_DIR}

fclean: clean
	${RM} ${NAME}
	make -C ${MAKE_DIR} fclean
	rm -rf ${OBJS_DIR}

re: fclean all

.PHONY: all clean re clean fclean bonus
