/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 15:06:49 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/20 18:43:56 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	do_first_cmd(char **argv, char **envp, t_pipex pipex)
{
	char	*path;
	char	**cmd;
	int		output_check;

	do_dup2(pipex.fd_in_curr, STDOUT_FILENO);
	cmd = compute_cmd(argv[2], argv[1]);
	if (!cmd)
		perror_exit("Failed to make cmds (first):");
	path = compute_path_no_fd(envp, &cmd);
	output_check = execve(path, cmd, envp);
	free(path);
	free_2d_array(&cmd);
	close(pipex.fd_in_curr);
	if (output_check == -1)
		perror_exit("Execve error (first):");
}
