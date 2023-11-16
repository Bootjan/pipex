/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 21:16:54 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/16 22:25:03 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*cmd_with_file(char *cmd, char *file)
{
	char	*temp_cmd;

	temp_cmd = ft_strjoin(cmd, " ");
	if (!temp_cmd)
		return (NULL);
	cmd = ft_strjoin(temp_cmd, file);
	free(temp_cmd);
	if (!cmd)
		return (NULL);
	return (cmd);
}

char	**cmd_2d_array(char *cmd, char *file)
{
	char	**argv;
	
	cmd = cmd_with_file(cmd, file);
	if (!cmd)
		return (NULL);
	argv = ft_split(cmd, ' ');
	if (!argv)
		return (NULL);
	return (argv);
}

static int	word_count(char *str)
{
	int	total_words;
	int	on_word;
	int	i;

	on_word = FALSE;
	total_words = 0;
	i = 0;
	while (str[i])
	{
		if (ft_ischar(str[i]) && on_word == FALSE)
		{
			on_word = TRUE;
			total_words++;
		}
		else if (!ft_ischar(str[i]))
			on_word = FALSE;
		i++;
	}
	return (total_words);
}

static int	chars_count(char *str)
{
	int	i;
	int	total_chars;

	i = 0;
	total_chars = 0;
	while (str[i])
		if (ft_ischar(str[i++]))
			total_chars++;
	return (total_chars);
}

char	*clean_cmd(char *cmd, char *out)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (out[0] != '\0')
			out[j] = ' ';
		while (!ft_ischar(cmd[i]))
			i++;
		while (ft_ischar(cmd[i]))
			out[j++] = cmd[i++];
	}
	return (out);
}

char	*trim_cmd(char *cmd)
{
	int		words;
	int		chars;
	char	*out;

	words = word_count(cmd);
	chars = chars_count(cmd);
	out = ft_calloc(words + chars, sizeof(char));
	if (!out)
		return (NULL);
	return (clean_cmd(cmd, out));
}
