/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 15:06:49 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/21 23:42:54 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	open_file(char *file)
{
	int	fd_in;
	int	fd_check;

	fd_in = open(file, O_RDONLY);
	if (fd_in == -1)
		perror_exit("Failed to open input file:");
	fd_check = dup2(fd_in, STDIN_FILENO);
	if (fd_check != STDIN_FILENO)
	{
		close(fd_in);
		perror_exit("Dup2 error:");
	}
	return (fd_in);
}

void	do_first_cmd(char **argv, char **envp, t_pipex pipex)
{
	char	*path;
	char	**cmd;
	int		output_check;
	int		fd_in;

	fd_in = open_file(argv[1]);
	do_dup2(pipex.fd_in_curr, STDOUT_FILENO);
	cmd = compute_cmd(argv[2], NULL);
	if (!cmd)
		perror_exit("Failed to make cmds (first):");
	path = compute_path_no_fd(envp, &cmd);
	output_check = execve(path, cmd, envp);
	free(path);
	free_2d_array(&cmd);
	close(pipex.fd_in_curr);
	close(fd_in);
	if (output_check == -1)
		perror_exit("Execve error (first):");
}
