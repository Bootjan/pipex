/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base_converter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:18:18 by bschaafs          #+#    #+#             */
/*   Updated: 2023/10/10 22:21:53 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*push_front(char *str, char c)
{
	size_t	size;
	char	*out;
	size_t	i;

	size = 0;
	if (str)
		size = ft_strlen(str);
	out = ft_calloc(size + 2, sizeof(char));
	if (!out)
	{
		free_function(str);
		return (NULL);
	}
	out[0] = c;
	i = 0;
	while (i < size)
	{
		out[i + 1] = str[i];
		i++;
	}
	free_function(str);
	return (out);
}

char	*base_converter_ul(unsigned long n, char *base, int base_len)
{
	char	*out;

	out = NULL;
	if (n == 0)
		return (ft_strdup("0"));
	while (n > 0)
	{
		out = push_front(out, base[n % base_len]);
		if (!out)
			return (NULL);
		n /= base_len;
	}
	return (out);
}

char	*base_converter(long n, char *base, int base_len)
{
	char	*out;

	out = NULL;
	if (n == 0)
		return (ft_strdup("0"));
	while (n > 0)
	{
		out = push_front(out, base[n % base_len]);
		if (!out)
			return (NULL);
		n /= base_len;
	}
	return (out);
}
