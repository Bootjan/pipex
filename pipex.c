/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:19:06 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/19 17:13:29 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

void	perror_exit(const char *msg)
{
	ft_putendl_fd((char *)msg, 2);
	perror("Error");
	exit(1);
}

void	free_2d_array(char ***paths)
{
	int	i;
	
	if (!*paths)
		return ;
	i = 0;
	while ((*paths)[i])
	{
		if ((*paths)[i])
			free((*paths)[i]);
		(*paths)[i++] = NULL;
	}
	free(*paths);
	*paths = NULL;
}

void	init_pipe(t_pipex *pipex)
{
	int	fd[2];

	if (pipex->fd_in_curr)
	{
		pipex->fd_in_prev = pipex->fd_in_curr;
		pipex->fd_out_prev = pipex->fd_out_curr;
	}
	if (pipe(fd) == -1)
		perror_exit("Init pipe:");
	pipex->fd_in_curr = fd[1];
	pipex->fd_out_curr = fd[0];
}

int	fork_wait(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		perror_exit("Init fork:");
	wait(NULL);
	return (pid);
}

void	pipex(int argc, char **argv, char **envp)
{
	int		pid;
	int		i;
	t_pipex	pipex;	
	int		dup_check;

	ft_bzero(&pipex, sizeof(t_pipex));
	init_pipe(&pipex);
	pid = fork_wait();
	wait(NULL);
	if (pid == 0)
		do_first_cmd(argv, envp, pipex);
	i = 0;
	while (i++ < argc - 5 && pid > 0)
	{
		close(pipex.fd_in_curr);
		init_pipe(&pipex);
		pid = fork_wait();
		if (pid == 0)
			do_middle_cmd(argv[2 + i], envp, pipex);
	}
	dup_check = dup2(pipex.fd_out_curr, STDIN_FILENO);
	if (dup_check != STDIN_FILENO)
		perror_exit("Dup error:");
	if (pid > 0)
		do_last_cmd(argv, envp, pipex, i);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
		return (ft_putendl_fd("Error\nIncorrect amount of arguments.", 2), 1);
	pipex(argc, argv, envp);
}
