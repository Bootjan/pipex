/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:41:35 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/21 18:16:19 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

char	*compute_limiter(char *av)
{
	char	*limiter;

	limiter = av;
	if (ft_strncmp(limiter, "", 1) == 0)
	{
		ft_putstr_fd("Empty limiter.\n", 2);
		exit(1);
	}
	return (limiter);
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
			return (free(out), input);
		input = concat_strs(input, out);
		if (!input)
			perror_exit("Concat error:");
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

void	here_doc(char **argv, char **envp)
{
	char	*input;
	char	*limiter;
	int		pid;
	t_pipex	pipex;

	ft_bzero(&pipex, sizeof(t_pipex));
	limiter = compute_limiter(argv[2]);
	input = compute_input(limiter);
	init_pipe(&pipex);
	pid = do_fork();
	if (pid == 0)
		write_input_to_pipe(input, pipex);
	free(input);
	if (pid > 0)
	{
		close(pipex.fd_in_curr);
		init_pipe(&pipex);
		pid = do_fork();
		if (pid == 0)
			do_middle_cmd((char *)argv[3], envp, pipex);
	}
	if (pid > 0)
		do_last_cmd_append(argv, envp, pipex);
}
