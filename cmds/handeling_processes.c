/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handeling_processes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:30:02 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/22 14:21:10 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	close_pipes(t_pipex pipex)
{
	if (pipex.fd_in_curr)
	{
		close(pipex.fd_in_curr);
		close(pipex.fd_out_curr);
	}
	if (pipex.fd_in_prev)
	{
		close(pipex.fd_in_prev);
		close(pipex.fd_out_prev);
	}
}

int	do_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		perror_exit("Fork error:");
	return (pid);
}

void	do_dup2(int fd, int new_fd)
{
	int	dup_check;

	dup_check = dup2(fd, new_fd);
	if (dup_check != new_fd)
		perror_exit("Dup2 error:");
}

void	wait_for_childs(int num)
{
	int	i;

	i = 0;
	while (i++ < num)
		wait(NULL);
}
