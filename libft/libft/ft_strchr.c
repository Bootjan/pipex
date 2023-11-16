/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 20:53:18 by bootjan           #+#    #+#             */
/*   Updated: 2023/10/10 22:30:00 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*out;
	size_t	i;

	out = (char *)s;
	i = 0;
	while (out[i])
	{
		if (out[i] == (char)c)
			return (&out[i]);
		i++;
	}
	if ((char)c == 0)
		return (&out[i]);
	return (NULL);
}
