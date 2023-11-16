/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_per_s_c.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:43:05 by bschaafs          #+#    #+#             */
/*   Updated: 2023/10/10 21:38:54 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_s(va_list *args)
{
	char	*str;

	str = va_arg(*args, char *);
	if (!str)
		str = "(null)";
	if (ft_putstr(str) == -1)
		return (-1);
	return ((int)ft_strlen(str));
}

int	ft_print_c(va_list *args)
{
	char	c;

	c = 0;
	c = va_arg(*args, int);
	if (ft_putchar(c) == -1)
		return (-1);
	return (1);
}

int	ft_print_per(void)
{
	if (ft_putchar('%') == -1)
		return (-1);
	return (1);
}
