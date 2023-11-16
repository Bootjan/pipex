/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:20:20 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/16 17:22:32 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(const char *file_name)
{
	int	fd;

	if (access(file_name, R_OK) == -1)
		return (-1);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (-1);
	return (fd);	
}