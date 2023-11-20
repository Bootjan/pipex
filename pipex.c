/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:19:06 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/20 18:15:52 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(int argc, char **argv, char **envp)
{
	int		pid;
	int		i;
	t_pipex	pipex;	

	ft_bzero(&pipex, sizeof(t_pipex));
	init_pipe(&pipex);
	pid = fork_wait();
	if (pid == 0)
		do_first_cmd(argv, envp, pipex);
	i = 0;
	while (i++ < argc - 5 && pid > 0)
	{
		close(pipex.fd_in_curr);
		init_pipe(&pipex);
		pid = fork_wait();
		if (pid == 0)
			do_middle_cmd(argv[2 + i], envp, pipex);
	}
	if (pid > 0)
		do_last_cmd(&(argv[2 + i]), envp, pipex);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
		return (ft_putendl_fd("Error\nIncorrect amount of arguments.", 2), 1);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0 && argc == 6)
		here_doc(argv, envp);
	else
		pipex(argc, argv, envp);
}
