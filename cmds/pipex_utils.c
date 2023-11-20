/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:27:56 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/20 18:43:09 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	perror_exit(const char *msg)
{
	ft_putendl_fd((char *)msg, 2);
	perror("");
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
		perror_exit("Fork error:");
	wait(NULL);
	return (pid);
}

void	do_dup2(int fd, int new_fd)
{
	int	dup_check;

	dup_check = dup2(fd, new_fd);
	if (dup_check != new_fd)
		perror_exit("Dup2 error:");
}
