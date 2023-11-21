/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 15:02:52 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/21 19:45:30 by bschaafs         ###   ########.fr       */
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

int	do_middle_cmds(int argc, char **argv, char **envp, t_pipex *pipex)
{
	int	i;
	int	pid;

	i = 0;
	pid = 1;
	while (i++ < argc - 5 && pid > 0)
	{
		close(pipex->fd_in_curr);
		init_pipe(pipex);
		pid = do_fork();
		if (pid == 0)
			do_middle_cmd(argv[2 + i], envp, *pipex);
	}
	return (i);
}
