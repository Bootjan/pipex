/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:41:35 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/22 14:19:06 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	here_doc(char **argv, char **envp)
{
	int		pid;
	t_pipex	pipex;
	int		status;

	pid = 0;
	status = 0;
	ft_bzero(&pipex, sizeof(t_pipex));
	input_to_pipe(argv[2], &pipex, &pid);
	if (pid > 0)
	{
		close(pipex.fd_in_curr);
		init_pipe(&pipex);
		pid = do_fork();
		if (pid == 0)
			do_middle_cmd((char *)argv[3], envp, pipex);
	}
	if (pid > 0)
		last_cmd_append_status(argv, envp, pipex, &status);
	wait_for_childs(2);
	if (pid > 0)
		close_pipes(pipex);
	return (check_status(status));
}
