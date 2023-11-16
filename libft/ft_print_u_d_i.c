/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u_d_i.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:49:44 by bschaafs          #+#    #+#             */
/*   Updated: 2023/10/15 18:54:08 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	compute_sign_length(long *n, long *sign, long *len)
{
	long	buf_n;

	buf_n = *n / 10;
	*len = 1;
	while (buf_n)
	{
		(*len)++;
		buf_n /= 10;
	}
	if (*n < 0)
	{
		*sign = 1;
		(*len)++;
		*n *= -1;
	}
}

char	*ft_itou(long n)
{
	long	len;
	long	sign;
	char	*out;

	sign = 0;
	len = 0;
	compute_sign_length(&n, &sign, &len);
	out = ft_calloc(len + 1, sizeof(char));
	if (!out)
		return (NULL);
	if (sign)
		out[0] = '-';
	while (len-- > sign)
	{
		out[len] = n % 10 + '0';
		n /= 10;
	}
	return (out);
}

int	ft_print_u(va_list *args)
{
	char	*out;
	long	args_n;
	size_t	size;

	args_n = 0;
	args_n = va_arg(*args, int);
	if (args_n < 0)
		args_n += MAX_U;
	out = ft_itou(args_n);
	if (!out)
		return (-1);
	if (ft_putstr(out) == -1)
		return (free_function(out));
	size = (int)ft_strlen(out);
	free_function(out);
	return (size);
}

int	ft_print_i_d(va_list *args)
{
	char	*out;
	int		args_n;
	size_t	size;

	args_n = 0;
	args_n = va_arg(*args, int);
	out = ft_itoa(args_n);
	if (!out)
		return (-1);
	if (ft_putstr(out) == -1)
		return (free_function(out));
	size = (int)ft_strlen(out);
	free_function(out);
	return (size);
}
