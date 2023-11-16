/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 21:32:01 by bootjan           #+#    #+#             */
/*   Updated: 2023/10/15 18:51:11 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	int	out;

	out = write(1, &c, 1);
	if (out == -1)
		return (-1);
	return (1);
}

int	ft_putstr(const char *s)
{
	int	out;

	if (!s)
		return (0);
	out = write(1, s, ft_strlen(s));
	if (out == -1)
		return (-1);
	return (1);
}

int	free_function(void *ptr)
{
	if (ptr)
		free(ptr);
	return (-1);
}
