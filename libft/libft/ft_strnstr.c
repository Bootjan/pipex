/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 20:14:00 by bootjan           #+#    #+#             */
/*   Updated: 2023/10/06 10:43:44 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	if (!*needle)
		return ((char *)haystack);
	while (*haystack && len-- > 0)
	{
		if (*haystack == *needle)
		{
			i = 0;
			while (needle[i] == haystack[i])
			{
				if (!needle[i + 1] && i <= len)
					return ((char *)haystack);
				if (!haystack[i + 1])
					return (NULL);
				i++;
			}
		}
		haystack++;
	}
	return (NULL);
}
