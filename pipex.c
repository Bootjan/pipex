/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bootjan <bootjan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:19:06 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/18 22:26:05 by bootjan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

void	perror_exit(void)
{
	perror("Error");
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

void	do_first_cmd(char **argv, char **envp, t_pipex pipex)
{
	char	*path;
	char	**cmd;

	dup2(pipex.fd[1], STDOUT_FILENO);
	close(pipex.fd[0]);
	close(pipex.fd[1]);
	// fd_in = open(argv[1], O_RDONLY);
	// if (fd_in == -1)
	// 	perror_exit();
	// dup2(fd_in, STDIN_FILENO);
	cmd = cmd_2d_array(argv[2], argv[1]);
	if (!cmd)
		perror_exit();
	path = get_right_path(envp, cmd[0]);
	if (!path)
	{
		free_2d_array(&cmd);
		perror_exit();
	}
	if (execve(path, cmd, envp) == -1)
		perror_exit();
	free(path);
	free_2d_array(&cmd);
}

void	do_second_cmd(char **argv, char **envp, t_pipex pipex)
{
	char	**cmd;
	char	*path;
	int		fd_out;

	dup2(pipex.fd[0], STDIN_FILENO);
	close(pipex.fd[0]);
	close(pipex.fd[1]);
	fd_out = open(argv[4], O_RDWR | O_CREAT);
	if (fd_out == -1)
		perror_exit();
	int fd_check = dup2(fd_out, STDOUT_FILENO);
	if (fd_check == -1)
	{
		close(fd_out);
	}
	cmd = ft_split(argv[3], ' ');
	if (!cmd)
		perror_exit();
	path = get_right_path(envp, cmd[0]);
	if (!path)
	{
		free_2d_array(&cmd);
		perror_exit();
	}
	if (execve(path, cmd, envp) == -1)
		perror_exit();
	free(path);
	free_2d_array(&cmd);
	close(fd_out);
}

int	pipex(char **argv, char **envp)
{
	t_pipex	pipex;
	int		pid;
	int		cpid;
	int		status;
	int		dup_check;

	ft_bzero(&pipex, sizeof(t_pipex));
	if (pipe(pipex.fd) < 0)
		perror_exit();
	pid = fork();
	dup_check = dup2(pipex.fd[0], STDIN_FILENO);
	if (dup_check != STDIN_FILENO)
		perror_exit();
	cpid = wait(&status);
	if (pid == 0)
		do_first_cmd(argv, envp, pipex);
	else
		do_second_cmd(argv, envp, pipex);
	close(pipex.fd[0]);
	close(pipex.fd[1]);
	return (cpid);
}

void	init_pipe(t_pipex *pipex)
{
	int	fd[2];

	if (!pipex->fd_in_curr)
	{
		pipex->fd_in_prev = pipex->fd_in_curr;
		pipex->fd_out_prev = pipex->fd_out_curr;
	}
	if (pipe(fd) == -1)
		perror_exit();
	pipex->fd_in_curr = fd[1];
	pipex->fd_out_curr = fd[0];
}

int	pipex(int argc, char **argv, char **envp)
{
	int		pid;
	int		i;
	t_pipex	pipex;	
	int		dup_check;

	ft_bzero(&pipex, sizeof(t_pipex));
	init_pipe(&pipex);
	pid = fork();
	do_first_cmd();
	i = 0;
	while (i++ < argc - 5 && pid > 0)
	{
		init_pipe(&pipex);
		pid = fork();
		if (pid == -1)
			perror_exit();
		
	}
	dup_check = dup2(pipex.fd[0], STDIN_FILENO);
	if (dup_check != STDIN_FILENO)
		perror_exit();
	if (pid > 0)
		do_last_cmd(argv, envp, pipex);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		return (ft_putendl_fd("Error\nIncorrect amount of arguments.", 2), 1);
	pipex(argv, envp);
}
