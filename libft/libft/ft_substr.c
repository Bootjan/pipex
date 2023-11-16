/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:30:59 by bschaafs          #+#    #+#             */
/*   Updated: 2023/10/10 23:57:04 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*out;
	int		i;
	int		j;
	int		length;

	length = (int)ft_strlen(s);
	if (len + start > (size_t)length)
		len = length - start;
	if ((size_t)length < start)
		len = 0;
	out = (char *)ft_calloc((len + 1), sizeof(char));
	if (!out)
		return (NULL);
	j = 0;
	while (s[j] && start--)
		j++;
	i = 0;
	while (s[j] && len--)
		out[i++] = s[j++];
	return (out);
}
