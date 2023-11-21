/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:27:56 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/21 18:30:23 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	perror_exit(const char *msg)
{
	ft_putendl_fd((char *)msg, 2);
	perror("");
	exit(1);
}

void	free_2d_array(char ***paths)
{
	int	i;

	if (!*paths)
		return ;
	i = 0;
	while ((*paths)[i])
	{
		if ((*paths)[i])
			free((*paths)[i]);
		(*paths)[i++] = NULL;
	}
	free(*paths);
	*paths = NULL;
}
