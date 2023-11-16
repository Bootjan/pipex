/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:53:59 by bschaafs          #+#    #+#             */
/*   Updated: 2023/10/15 18:51:19 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int		ft_print_i_d(va_list *args);
int		ft_print_u(va_list *args);
int		ft_print_s(va_list *args);
int		ft_print_c(va_list *args);
int		ft_print_per(void);
int		ft_print_p(va_list *args);
int		ft_print_x(va_list *args);
int		ft_print_upper_x(va_list *args);
char	*base_converter(long n, char *base, int base_len);
char	*base_converter_ul(unsigned long n, char *base, int base_len);
void	ft_putstr_fd(const char *s, int fd);
void	ft_putchar_fd(char c, int fd);
char	*ft_itoa(int n);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_printf(const char *format, ...);
char	*ft_strdup(const char *s);
int		ft_putchar(char c);
int		ft_putstr(const char *s);
int		free_function(void *ptr);

# define LOWER_16_BASE "0123456789abcdef"
# define UPPER_16_BASE "0123456789ABCDEF"
# define MAX_U 4294967296

#endif