/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:09:56 by bootjan           #+#    #+#             */
/*   Updated: 2023/10/10 22:57:53 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_trimmable(char c, char const *set)
{
	if (!*set)
		return (0);
	if (c == *set)
		return (1);
	return (is_trimmable(c, set + 1));
}

char	*ft_strtrim(const char *s, char const *set)
{
	int		start;
	int		end;
	char	*out;
	int		i;

	if (!s)
		return (NULL);
	start = 0;
	while (is_trimmable(s[start], set))
		start++;
	end = ft_strlen(s) - 1;
	if (!*s || start == end + 1)
		return (ft_strdup(""));
	while (is_trimmable(s[end], set) && end > 0)
		end--;
	out = (char *)ft_calloc((end - start + 2), sizeof(char));
	if (!out)
		return (NULL);
	i = -1;
	while (start + i++ <= end - 1)
		out[i] = s[start + i];
	return (out);
}
