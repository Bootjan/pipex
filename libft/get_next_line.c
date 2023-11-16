/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:41:05 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/03 16:30:37 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	compute_buffer(char **temp, int fd, int *r, char buffer[])
{
	*r = read(fd, buffer, BUFFER_SIZE);
	if (*r == -1)
	{
		free_temp(temp);
		return ;
	}
	if (*r == 0)
		return ;
	buffer[*r] = '\0';
}

static void	clean_temp(char **temp, int index_n)
{
	char	*out;
	int		len;
	int		i;

	len = ft_strlen(*temp);
	if (len == index_n)
	{
		free_temp(temp);
		return ;
	}
	out = malloc((len - index_n + 1) * SIZE_OF_CHAR);
	if (!out)
	{
		free_temp(temp);
		return ;
	}
	i = 0;
	while (index_n < len)
		out[i++] = (*temp)[index_n++];
	out[i] = '\0';
	free_temp(temp);
	*temp = out;
}

static char	*next_line(char **temp, int index_n)
{
	char	*out;
	int		i;

	if (index_n == -1)
		index_n = (int)ft_strlen(*temp);
	else
		index_n++;
	if (index_n == 0)
		return (free_temp(temp));
	out = malloc((index_n + 1) * SIZE_OF_CHAR);
	if (!out)
		return (free_temp(temp));
	i = 0;
	while (i < index_n)
	{
		out[i] = (*temp)[i];
		i++;
	}
	out[i] = '\0';
	clean_temp(temp, index_n);
	return (out);
}

char	*get_next_line(int fd)
{
	static char	*temp;
	char		buffer[BUFFER_SIZE + 1];
	int			r;
	int			index_n;
	char		*ptr;

	r = BUFFER_SIZE;
	index_n = ft_index_n(temp, '\n');
	while (r == BUFFER_SIZE && index_n == -1)
	{
		compute_buffer(&temp, fd, &r, buffer);
		if ((!temp && r == 0) || r == -1)
			return (NULL);
		if (r == 0)
			break ;
		ptr = buffer;
		if (!temp)
			temp = ft_tempdup(ptr);
		else
			temp = ft_tempjoin(&temp, ptr);
		index_n = ft_index_n(temp, '\n');
	}
	return (next_line(&temp, index_n));
}
