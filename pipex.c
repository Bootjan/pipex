/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:19:06 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/22 14:16:41 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex(int argc, char **argv, char **envp)
{
	int		pid;
	int		i;
	t_pipex	pipex;
	int		status;

	status = 0;
	ft_bzero(&pipex, sizeof(t_pipex));
	init_pipe(&pipex);
	pid = do_fork();
	if (pid == 0)
		do_first_cmd(argv, envp, pipex);
	i = 0;
	while (i++ < argc - 5 && pid > 0)
		do_middle_cmds(argv[2 + i], envp, pipex, &pid);
	if (pid > 0)
		last_cmd_status(&(argv[2 + i]), envp, pipex, &status);
	wait_for_childs(argc - 4);
	if (pid > 0)
		close_pipes(pipex);
	return (check_status(status));
}

int	main(int argc, char **argv, char **envp)
{
	int	ret;

	ret = 0;
	if (argc < 5)
		return (ft_putendl_fd("Error\nIncorrect amount of arguments.", 2), 1);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0 && argc == 6)
		ret = here_doc(argv, envp);
	else
		ret = pipex(argc, argv, envp);
	return (ret);
}
