/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:19:46 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/18 22:25:27 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define FALSE 0
# define TRUE 1

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include "colors.h"
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

typedef struct	s_pipex {
	int		fd_out_prev;
	int		fd_in_prev;
	int		fd_out_curr;
	int		fd_in_curr;
}	t_pipex;

char	*get_right_path(char **envp, char *cmd);
char	*without_cmd(char *cmd, char *file);
void	free_2d_array(char ***paths);
char	**cmd_2d_array(char *cmd, char *file);

#endif