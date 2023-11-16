/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_min.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:30:01 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/02 18:31:13 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_get_min(int *arr, int len)
{
	int	min;
	int	i;

	i = 1;
	min = arr[0];
	while (i < len)
	{
		if (arr[i] < min)
			min = arr[i];
		i++;
	}
	return (min);
}
