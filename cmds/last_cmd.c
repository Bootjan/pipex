/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 15:03:56 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/19 18:46:34 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	find_fds(char **argv, t_pipex pipex, int *fd_out, int i)
{
	int	output_check;

	close(pipex.fd_in_curr);
	do_dup2(pipex.fd_out_curr, STDIN_FILENO);
	*fd_out = open(argv[4 + i - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (*fd_out == -1)
		perror_exit("Last cmd:");
	output_check = dup2(*fd_out, STDOUT_FILENO);
	if (output_check == -1)
	{
		close(*fd_out);
		perror_exit("Last cmd:");
	}
}

static char	*find_path_cmd(char *av, char **envp, char ***cmd, int fd_out)
{
	char	*path;

	*cmd = ft_split(av, ' ');
	if (!*cmd)
	{
		close(fd_out);
		perror_exit("Last cmd:");
	}
	path = compute_path(envp, (*cmd)[0]);
	if (!path)
	{
		close(fd_out);
		free_2d_array(cmd);
		perror_exit("Last cmd:");
	}
	return (path);
}

void	do_last_cmd(char **argv, char **envp, t_pipex pipex, int i)
{
	char	**cmd;
	char	*path;
	int		fd_out;
	int		output_check;

	cmd = NULL;
	fd_out = 0;
	find_fds(argv, pipex, &fd_out, i);
	path = find_path_cmd(argv[2 + i], envp, &cmd, fd_out);
	output_check = execve(path, cmd, envp);
	free(path);
	free_2d_array(&cmd);
	close(fd_out);
	if (output_check == -1)
		perror_exit("Last cmd:");
}
