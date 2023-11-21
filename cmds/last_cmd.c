/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 15:03:56 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/21 23:47:56 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	find_fds(char *file, t_pipex pipex, int *fd_out)
{
	int	output_check;

	close(pipex.fd_in_curr);
	close(pipex.fd_out_prev);
	do_dup2(pipex.fd_out_curr, STDIN_FILENO);
	*fd_out = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (*fd_out == -1)
		perror_exit("Open error output file:");
	output_check = dup2(*fd_out, STDOUT_FILENO);
	if (output_check == -1)
	{
		close(*fd_out);
		perror_exit("Dup2 error:");
	}
}

static char	*find_path_cmd(char *av, char **envp, char ***cmd, int fd_out)
{
	char	*path;

	*cmd = ft_split(av, ' ');
	if (!*cmd)
	{
		close(fd_out);
		perror_exit("Failed to make cmds:");
	}
	path = compute_path(envp, (*cmd)[0]);
	if (!path)
	{
		close(fd_out);
		free_2d_array(cmd);
		perror_exit("Failed to make path:");
	}
	return (path);
}

void	do_last_cmd(char **argv, char **envp, t_pipex pipex)
{
	char	**cmd;
	char	*path;
	int		fd_out;
	int		output_check;

	cmd = NULL;
	fd_out = 0;
	find_fds(argv[1], pipex, &fd_out);
	path = find_path_cmd(argv[0], envp, &cmd, fd_out);
	output_check = execve(path, cmd, envp);
	free(path);
	free_2d_array(&cmd);
	close(fd_out);
	if (output_check == -1)
		perror_exit("Execve error:");
}
