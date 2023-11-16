/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:53:43 by bschaafs          #+#    #+#             */
/*   Updated: 2023/10/10 21:50:17 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_type(va_list *args, char type)
{
	if (type == 's')
		return (ft_print_s(args));
	if (type == 'c')
		return (ft_print_c(args));
	if (type == 'p')
		return (ft_print_p(args));
	if (type == 'x')
		return (ft_print_x(args));
	if (type == 'X')
		return (ft_print_upper_x(args));
	if (type == 'i' || type == 'd')
		return (ft_print_i_d(args));
	if (type == 'u')
		return (ft_print_u(args));
	if (type == '%')
		return (ft_print_per());
	ft_printf("<Bad type>");
	return (0);
}

int	convert_format(va_list *args, const char *format)
{
	int	i;
	int	total_written;
	int	write_check;

	i = 0;
	total_written = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			write_check = print_type(args, format[i + 1]);
			if (write_check == -1)
				return (-1);
			total_written += write_check;
			i += 2;
		}
		else
		{
			if (ft_putchar(format[i++]) == -1)
				return (-1);
			total_written++;
		}
	}
	return (total_written);
}

int	ft_printf(const char *format, ...)
{
	int		out;
	va_list	args;

	out = 0;
	if (!format)
		return (0);
	va_start(args, format);
	out = convert_format(&args, format);
	va_end(args);
	return (out);
}
