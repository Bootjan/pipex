/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:27:28 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/19 19:47:33 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_total_words(const char *s, char c)
{
	int	total_words;
	int	on_word;
	int	i;

	total_words = 0;
	on_word = 0;
	i = 0;
	while (s[i])
	{
		if (on_word == 0 && s[i] != c)
		{
			total_words++;
			on_word = 1;
		}
		if (s[i] == c)
			on_word = 0;
		if (s[i] != c)
			on_word = 1;
		i++;
	}
	return (total_words);
}

int	update_start(const char *s, char c, int start, int i)
{
	if (s[i] != c && start == -1)
		return (i);
	if (s[i] == c)
		return (-1);
	return (start);
}

void	free_array(char **out, int total_words)
{
	int	i;

	i = 0;
	if (!out)
		return ;
	while (i < total_words + 1)
	{
		if (out[i])
			free(out[i]);
		i++;
	}
	if (out)
		free(out);
}

char	**compute_array(char **out, const char *s, char c, int *error_flag)
{
	int	start;
	int	i;
	int	j;

	start = -1;
	i = 0;
	j = 0;
	while (s[i] && *error_flag == 0)
	{
		if (s[i] == c && start >= 0)
		{
			out[j] = ft_substr(s, start, i - start);
			if (!out[j++])
				*error_flag = 1;
		}
		start = update_start(s, c, start, i++);
	}
	if (start >= 0 && *error_flag == 0)
	{
		out[j] = ft_substr(s, start, i - start);
		if (!out[j++])
			*error_flag = 1;
	}
	return (out);
}

char	**ft_split(const char *s, char c)
{
	char	**out;
	int		total_words;
	int		error_flag;

	total_words = count_total_words(s, c);
	out = (char **)ft_calloc((total_words + 1), sizeof(char *));
	if (!out)
		return (NULL);
	error_flag = 0;
	out = compute_array(out, s, c, &error_flag);
	if (error_flag == 1)
	{
		free_array(out, total_words);
		out = NULL;
	}
	return (out);
}
