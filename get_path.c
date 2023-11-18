/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 21:14:56 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/17 01:02:27 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	space_index(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && cmd[i] != ' ')
		i++;
	return (i);
}

static char	*compute_poss_path(char *path, char *sub_cmd)
{
	int		i;
	int		j;
	char	*out;

	out = ft_calloc(ft_strlen(path) + ft_strlen(sub_cmd) + 2, sizeof(char));
	if (!out)
		return (NULL);
	i = 0;
	j = 0;
	while (path[i])
		out[j++] = path[i++];
	out[j++] = '/';
	i = 0;
	while (sub_cmd[i])
		out[j++] = sub_cmd[i++];
	return (out);
}

static char	*compute_right_path(char **paths, char *cmd)
{
	char	*sub_cmd;
	char	*poss_path;
	int		i;

	sub_cmd = ft_substr(cmd, 0, space_index(cmd));
	if (!sub_cmd)
		return (NULL);
	if (access(sub_cmd, X_OK) == 0)
		return (sub_cmd);
	i = 0;
	while (paths[i])
	{
		poss_path = compute_poss_path(paths[i++], sub_cmd);
		if (!poss_path)
			return (NULL);
		if (access(poss_path, X_OK) == 0)
			return (free(sub_cmd), poss_path);
		free(poss_path);
	}
	return (free(sub_cmd), NULL);
}

static char	**compute_paths(char **envp)
{
	char	**paths;
	int		i;
	char	*path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path = envp[i];
		i++;
	}
	paths = ft_split(&path[5], ':');
	if (!paths)
		return (NULL);
	return (paths);
}

char	*get_right_path(char **envp, char *cmd)
{
	char	**paths;
	char	*path;

	paths = compute_paths(envp);
	if (!paths)
		return (NULL);
	path = compute_right_path(paths, cmd);
	free_2d_array(&paths);
	if (!path)
		return (NULL);
	return (path);
}
