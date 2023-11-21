/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 23:37:27 by bootjan           #+#    #+#             */
/*   Updated: 2023/11/21 23:46:20 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*concat_strs(char *input, char *out)
{
	char	*ret;

	ret = ft_strjoin(input, out);
	free(input);
	free(out);
	if (!ret)
		perror_exit("Malloc error:");
	return (ret);
}

static char	*compute_limiter(char *av)
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

static char	*compute_input(char *limiter)
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

static void	write_input_to_pipe(char *input, t_pipex pipex)
{
	if (write(pipex.fd_in_curr, input, ft_strlen(input)) == -1)
	{
		free(input);
		perror_exit("Write error:");
	}
}

void	input_to_pipe(char *av, t_pipex *pipex, int *pid)
{
	char	*limiter;
	char	*input;

	limiter = compute_limiter(av);
	init_pipe(pipex);
	input = compute_input(limiter);
	*pid = fork_wait();
	if (*pid == 0)
		write_input_to_pipe(input, *pipex);
	free(input);
}
