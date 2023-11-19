/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 15:02:52 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/19 17:12:20 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	do_middle_cmd(char *av, char **envp, t_pipex pipex)
{
	char	**cmd;
	char	*path;
	int		output_check;

	output_check = dup2(pipex.fd_out_prev, STDIN_FILENO);
	if (output_check != STDIN_FILENO)
		perror_exit("Middle cmd:");
	output_check = dup2(pipex.fd_in_curr, STDOUT_FILENO);
	if (output_check != STDOUT_FILENO)
		perror_exit("Middle cmd:");
	cmd = ft_split(av, ' ');
	if (!cmd)
		perror_exit("Middle cmd:");
	path = get_right_path(envp, cmd[0]);
	if (!path)
	{
		free_2d_array(&cmd);
		perror_exit("Middle cmd:");
	}
	output_check = execve(path, cmd, envp);
	free(path);
	free_2d_array(&cmd);
	if (output_check == -1)
		perror_exit("Middle cmd:");
}
