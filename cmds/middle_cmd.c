/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 15:02:52 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/22 14:18:17 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	do_middle_cmd(char *av, char **envp, t_pipex pipex)
{
	char	**cmd;
	char	*path;
	int		output_check;

	do_dup2(pipex.fd_out_prev, STDIN_FILENO);
	do_dup2(pipex.fd_in_curr, STDOUT_FILENO);
	cmd = compute_cmd_no_file(av);
	path = compute_path_no_fd(envp, &cmd);
	output_check = execve(path, cmd, envp);
	free(path);
	free_2d_array(&cmd);
	if (output_check == -1)
		perror_exit("Execve failed (middle):");
}

void	do_middle_cmds(char *av, char **envp, t_pipex pipex, int *pid)
{
	close(pipex.fd_in_curr);
	init_pipe(&pipex);
	*pid = do_fork();
	if (*pid == 0)
		do_middle_cmd(av, envp, pipex);
}
