/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:19:46 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/20 18:16:09 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define FALSE 0
# define TRUE 1

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

typedef struct s_pipex {
	int		fd_out_prev;
	int		fd_in_prev;
	int		fd_out_curr;
	int		fd_in_curr;
}	t_pipex;

//### CMD ######################################################################
char	**compute_cmd(char *cmd, char *file);
char	**compute_cmd_no_file(char *av);

//### PATH #####################################################################
char	*compute_path(char **envp, char *cmd);
char	*compute_path_no_fd(char **envp, char ***cmd);

//### UTILS ####################################################################
void	do_dup2(int fd, int new_fd);
int		fork_wait(void);
void	init_pipe(t_pipex *pipex);
void	free_2d_array(char ***paths);
void	perror_exit(const char *msg);

//### CMDS #####################################################################
void	do_first_cmd(char **argv, char **envp, t_pipex pipex);
void	do_middle_cmd(char *av, char **envp, t_pipex pipex);
void	do_last_cmd(char **argv, char **envp, t_pipex pipex);

//### HERE_DOC #################################################################
void	here_doc(char **argv, char **envp);
void	do_last_cmd_append(char **argv, char **envp, t_pipex pipex);

#endif