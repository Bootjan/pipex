/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 15:06:49 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/19 17:12:24 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	do_first_cmd(char **argv, char **envp, t_pipex pipex)
{
	char	*path;
	char	**cmd;
	int		output_check;

	output_check = dup2(pipex.fd_in_curr, STDOUT_FILENO);
	if (output_check != STDOUT_FILENO)
		perror_exit("First cmd:");
	cmd = cmd_2d_array(argv[2], argv[1]);
	if (!cmd)
		perror_exit("First cmd:");
	path = get_right_path(envp, cmd[0]);
	if (!path)
	{
		free_2d_array(&cmd);
		perror_exit("First cmd:");
	}
	output_check = execve(path, cmd, envp);
	free(path);
	free_2d_array(&cmd);
	close(pipex.fd_in_curr);
	if (output_check == -1)
		perror_exit("First cmd:");
}
