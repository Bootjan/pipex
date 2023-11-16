/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:56:44 by bootjan           #+#    #+#             */
/*   Updated: 2023/10/10 15:16:00 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char *s, char (*f)(unsigned int, char))
{
	char	*out;
	size_t	size;
	size_t	i;

	if (!s)
		return (NULL);
	size = ft_strlen(s) + 1;
	out = (char *)ft_calloc(size, sizeof(char));
	if (!out)
		return (NULL);
	i = 0;
	while (s[i])
	{
		out[i] = (*f)(i, s[i]);
		i++;
	}
	return (out);
}
