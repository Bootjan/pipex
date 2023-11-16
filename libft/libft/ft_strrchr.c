/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:52:43 by bootjan           #+#    #+#             */
/*   Updated: 2023/10/10 22:30:13 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*out;
	char	*current;
	int		i;

	out = NULL;
	current = (char *)s;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (current[i] == (char)c)
			return (&current[i]);
		i--;
	}
	return (out);
}
