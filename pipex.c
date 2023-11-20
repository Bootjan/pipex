/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:19:06 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/20 00:58:36 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(int argc, char **argv, char **envp)
{
	int		pid;
	int		i;
	t_pipex	pipex;	
	int		dup_check;

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
	dup_check = dup2(pipex.fd_out_curr, STDIN_FILENO);
	if (dup_check != STDIN_FILENO)
		perror_exit("Dup error:");
	if (pid > 0)
		do_last_cmd(argv, envp, pipex, i);
}

char	*concat_strs(char *input, char *out)
{
	char	*ret;

	ret = ft_strjoin(input, out);
	free(input);
	free(out);
	if (!ret)
		perror_exit("Malloc error:");
	return (ret);
}

char	*compute_input(char *limiter)
{
	char	*input;
	char	*out;
	int		lim_len;

	input = ft_strdup("");
	if (!input)
		perror_exit("Malloc error:");
	lim_len = ft_strlen(limiter);
	while (1)
	{
		ft_putstr("here_doc> ");
		out = get_next_line(STDIN_FILENO);
		if (!out)
		{
			free(input);
			perror_exit("Gnl error:");
		}
		if (ft_strncmp(out, limiter, lim_len) == 0 && out[lim_len] == '\n')
			return (input);
		input = concat_strs(input, out);
		if (!input)
			perror_exit("Malloc error:");
	}
}

void	write_input_to_pipe(char *input, t_pipex pipex)
{
	if (write(pipex.fd_in_curr, input, ft_strlen(input)) == -1)
	{
		free(input);
		perror_exit("Write error:");
	}
}

void	here_doc(int argc, char **argv, char **envp)
{
	char	*input;
	char	*limiter;
	int		pid;
	t_pipex	pipex;

	if (!argc || !envp)
		perror_exit("hoertje:");
	ft_bzero(&pipex, sizeof(t_pipex));
	limiter = argv[2];
	if (ft_strncmp(limiter, "", 1) == 0)
		perror_exit("Empty limiter:");
	input = compute_input(limiter);
	init_pipe(&pipex);
	pid = fork_wait();
	if (pid == 0)
		write_input_to_pipe(input, pipex);
	
}

int	main(int argc, char **argv, char **envp)
{
	// if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	// 	here_doc(argc, argv, envp);
	if (argc < 5)
		return (ft_putendl_fd("Error\nIncorrect amount of arguments.", 2), 1);
	else
		pipex(argc, argv, envp);
}
