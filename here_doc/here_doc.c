/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:41:35 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/21 23:43:25 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc(char **argv, char **envp)
{
	int		pid;
	t_pipex	pipex;

	pid = 0;
	ft_bzero(&pipex, sizeof(t_pipex));
	input_to_pipe(argv[2], &pipex, &pid);
	if (pid > 0)
	{
		close(pipex.fd_in_curr);
		init_pipe(&pipex);
		pid = fork_wait();
		if (pid == 0)
			do_middle_cmd((char *)argv[3], envp, pipex);
	}
	if (pid > 0)
	{
		pid = fork_wait();
		if (pid == 0)
			do_last_cmd_append(argv, envp, pipex);
	}
}
