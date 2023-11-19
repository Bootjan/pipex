/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 21:16:54 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/19 18:50:08 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*cmd_with_file(char *cmd, char *file)
{
	char	*temp_cmd;

	if (!file)
		return (ft_strdup(cmd));
	temp_cmd = ft_strjoin(cmd, " ");
	if (!temp_cmd)
		return (NULL);
	cmd = ft_strjoin(temp_cmd, file);
	free(temp_cmd);
	if (!cmd)
		return (NULL);
	return (cmd);
}

char	**compute_cmd(char *cmd, char *file)
{
	char	**av;

	cmd = cmd_with_file(cmd, file);
	if (!cmd)
		return (NULL);
	av = ft_split(cmd, ' ');
	free(cmd);
	if (!av)
		return (NULL);
	return (av);
}

char	**compute_cmd_no_file(char *av)
{
	char	**cmd;

	cmd = ft_split(av, ' ');
	if (!cmd)
		perror_exit("Couldn't make command:");
	return (cmd);
}
