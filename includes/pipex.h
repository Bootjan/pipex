/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:19:46 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/22 14:17:00 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
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

//### PROCESSES ################################################################
void	do_dup2(int fd, int new_fd);
int		do_fork(void);
void	init_pipe(t_pipex *pipex);
void	wait_for_childs(int num);
void	close_pipes(t_pipex pipex);

//### UTILS ####################################################################
void	free_2d_array(char ***paths);
void	perror_exit(const char *msg);
int		check_status(int status);

//### CMDS #####################################################################
void	do_first_cmd(char **argv, char **envp, t_pipex pipex);
void	do_middle_cmd(char *av, char **envp, t_pipex pipex);
void	do_middle_cmds(char *av, char **envp, t_pipex pipex, int *pid);
void	last_cmd_status(char **av, char **envp, t_pipex pipex, int *status);

//### HERE_DOC #################################################################
int		here_doc(char **argv, char **envp);
void	input_to_pipe(char *av, t_pipex *pipex, int *pid);
void	last_cmd_append_status(char **argv, char **envp, \
t_pipex pipex, int *status);

#endif