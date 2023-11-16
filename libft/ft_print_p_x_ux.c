/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p_x_ux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:10:46 by bschaafs          #+#    #+#             */
/*   Updated: 2023/10/15 18:51:56 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_p(va_list *args)
{
	char			*out;
	unsigned long	args_n;
	size_t			size;

	args_n = va_arg(*args, unsigned long);
	if (args_n == 0)
	{
		if (ft_putstr("(nil)") == -1)
			return (-1);
		return (5);
	}
	out = base_converter_ul(args_n, LOWER_16_BASE, ft_strlen(LOWER_16_BASE));
	if (!out)
		return (-1);
	if (ft_putstr("0x") == -1)
		return (free_function(out));
	if (ft_putstr(out) == -1)
		return (free_function(out));
	size = (int)ft_strlen(out) + 2;
	free_function(out);
	return (size);
}

int	ft_print_x(va_list *args)
{
	char	*out;
	long	args_n;
	size_t	size;

	args_n = va_arg(*args, int);
	if (args_n < 0)
		args_n += MAX_U;
	out = base_converter(args_n, LOWER_16_BASE, ft_strlen(LOWER_16_BASE));
	if (!out)
		return (-1);
	if (ft_putstr(out) == -1)
		return (free_function(out));
	size = (int)ft_strlen(out);
	free_function(out);
	return (size);
}

int	ft_print_upper_x(va_list *args)
{
	char	*out;
	long	args_n;
	size_t	size;

	args_n = va_arg(*args, int);
	if (args_n < 0)
		args_n += MAX_U;
	out = base_converter(args_n, UPPER_16_BASE, ft_strlen(UPPER_16_BASE));
	if (!out)
		return (-1);
	if (ft_putstr(out) == -1)
		return (free_function(out));
	size = (int)ft_strlen(out);
	free_function(out);
	return (size);
}
