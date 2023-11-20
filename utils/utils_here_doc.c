/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 22:47:31 by bootjan           #+#    #+#             */
/*   Updated: 2023/11/19 22:48:39 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.c"

void	init_pipe_here_doc(t_pipex *pipex, char *input)
{
	int	fd[2];

	if (pipex->fd_in_curr)
	{
		pipex->fd_in_prev = pipex->fd_in_curr;
		pipex->fd_out_prev = pipex->fd_out_curr;
	}
	if (pipe(fd) == -1)
	{
		free(input);
		perror_exit("Init pipe:");
	}
	pipex->fd_in_curr = fd[1];
	pipex->fd_out_curr = fd[0];
}