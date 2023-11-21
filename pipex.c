/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:19:06 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/21 20:04:18 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex(int argc, char **argv, char **envp)
{
	int		pid;
	t_pipex	pipex;
	int		status;
	int		i;

	status = 0;
	i = 0;
	ft_bzero(&pipex, sizeof(t_pipex));
	init_pipe(&pipex);
	pid = do_fork();
	if (pid == 0)
		do_first_cmd(argv, envp, pipex);
	if (pid > 0)
		i = do_middle_cmds(argc, argv, envp, &pipex);
	if (pid > 0)
		last_cmd(&(argv[2 + i]), envp, pipex, &status);
	if (pid > 0)
		wait_for_childs(argc - 4);
	return (WIFEXITED(status));
}

int	main(int argc, char **argv, char **envp)
{
	int	ret;

	ret = 0;
	if (argc < 5)
		return (ft_putendl_fd("Error\nIncorrect amount of arguments.", 2), 1);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0 && argc == 6)
		here_doc(argv, envp);
	else
		ret = pipex(argc, argv, envp);
	return (ft_printf("Ret value: %i\n", ret), ret);
}
