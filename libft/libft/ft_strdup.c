/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 00:10:16 by bootjan           #+#    #+#             */
/*   Updated: 2023/10/11 00:31:16 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		size;
	char	*out;

	size = ft_strlen(s1) + 1;
	out = (char *)ft_calloc(size, sizeof(char));
	if (!out)
		return (NULL);
	ft_memcpy(out, s1, size - 1);
	return (out);
}
