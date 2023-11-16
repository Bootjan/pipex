/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:32:42 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/02 18:33:36 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_swap_list(int *arr, int x, int y)
{
	int	temp;

	temp = arr[x];
	arr[x] = arr[y];
	arr[y] = temp;
	return (arr);
}
