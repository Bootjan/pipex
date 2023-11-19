/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 15:03:56 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/19 17:12:40 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	do_last_cmd(char **argv, char **envp, t_pipex pipex, int i)
{
	char	**cmd;
	char	*path;
	int		fd_out;
	int		output_check;

	close(pipex.fd_in_curr);
	dup2(pipex.fd_out_curr, STDIN_FILENO);
	fd_out = open(argv[4 + i - 1], O_RDWR | O_CREAT);
	if (fd_out == -1)
		perror_exit("Last cmd:");
	output_check = dup2(fd_out, STDOUT_FILENO);
	if (output_check == -1)
	{
		close(fd_out);
		perror_exit("Last cmd:");
	}
	cmd = ft_split(argv[3 + i - 1], ' ');
	if (!cmd)
		perror_exit("Last cmd:");
	path = get_right_path(envp, cmd[0]);
	if (!path)
	{
		free_2d_array(&cmd);
		perror_exit("Last cmd:");
	}
	output_check = execve(path, cmd, envp);
	free(path);
	free_2d_array(&cmd);
	close(fd_out);
	if (output_check == -1)
		perror_exit("Last cmd:");
}
