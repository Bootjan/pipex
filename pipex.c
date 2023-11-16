/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:19:06 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/16 22:28:17 by bschaafs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

#define MSGSIZE 16
char* msg1 = "hello, world #1"; 
char* msg2 = "hello, world #2"; 
char* msg3 = "hello, world #3"; 

void	fork_test(void)
{
	pid_t	pid = fork();
	int		stat = 0;
	pid_t	cpid = wait(&stat);
	ft_printf("STAT: %i.\n", stat);
	pid_t	pid2 = fork();
	pid_t	cpid2 = wait(&stat);
	
	printf("PID: % 7i.   PID2: % 7i.   CPID: % 7i.   CPID2: % 7i.   STAT: %i.\n", pid, pid2, cpid, cpid2, stat);
	// cpid2 = 0;
	// if (pid2 == 0)
	// 	ft_printf("PID2 == 0\n");
	// else
	// 	ft_printf("PID2 == %i\n", pid2);
	// if (pid == 0)
	// 	ft_printf("This is a child process! ID: %i. GETPID: %i. STAT: %i.\n", cpid, getpid(), stat);
	// else
	// 	ft_printf("This is the parent process! ID: %i. CPID: %i.\n", getpid(), cpid);
}

void	pipe_test(void)
{
	char inbuf[MSGSIZE]; 
	int p[2], i; 
	int	fd = open("infile", O_APPEND);
	if (fd == -1)
		return ;
	p[0] = fd;

	if (pipe(p) < 0) 
		exit(1); 

	/* continued */
	/* write pipe */

	ft_printf("%i   %i\n", p[0], p[1]);
	int newfd = dup2(p[0], 1);
	ft_printf("newfd: %i\n", newfd);
	write(p[0], msg1, MSGSIZE); 
	write(p[0], msg2, MSGSIZE); 
	write(p[0], msg3, MSGSIZE);

	if (access("/home/bschaafs/bin/grep", X_OK) == 0)
		ft_printf("SUCCES BROER!\n");
	else if (access("outfile", R_OK) == -1)
		ft_printf("WAS TOCH NIET\n");
	for (i = 0; i < 3; i++) {
		/* read pipe */
		// if (i == 2)
		// 	unlink("outfile");
		read(p[1], inbuf, MSGSIZE); 
		ft_printf("%s\n", inbuf); 
	} 
}

void	exec_test(char **envp)
{
	char	**av = ft_split("cmd a1 infile", ' ');
	// int i = 0;.
	// char	*exec;
	// while (envp[i])
	// {
	// 	if (ft_strncmp(envp[i], "PATH=", 5) == 0)
	// 		exec = ft_strjoin(&(envp[i][5]), "grep");
	// 	i++;
	// }
	// if (av[0])
	// 	free(av[0]);
	// av[0] = exec;
	int		ret = execve("/home/bschaafs/.local/bin/grep", av, envp);
	if (ret == -1)
		ft_printf("Error: %s\n", strerror(errno));
}

// int	error_checking(char **argv)
// {
// 	char	*file1;
// 	char	*file2;

// 	file1 = argv[1];
// 	file2 = argv[4];
// 	if (access(file1, R_OK) == -1)
// 		return (0);
// 	if (access(file2, W_OK) == -1)
// 		return (0);
// 	return (1);
// }

// int	write_to_pipe(int *fds, char **argv, char **envp)
// {
// 	char	*file1;
// 	char	*cmd1;
// 	char	*f_cmd1;

// 	file1 = argv[1];
// 	cmd1 = argv[2];
// 	if (access(file1, R_OK) == -1)
// 		return (errno);
// 	// do command, maybe check it
// 	f_cmd1 = ft_strjoin("#!interpreter ", cmd1);
// 	if (!f_cmd1)
// 		return (errno);
// 	if (execve(f_cmd1, NULL, envp) == -1)
// 		return (errno);
// }

// int	do_pipe(char **argv, char **envp)
// {
// 	int	fds[2];
// 	int	pid;
// 	int	cpid;
// 	int	stat;

// 	stat = 0;
// 	if (pipe(fds) < 0)
// 		return (errno);
// 	pid = fork();
// 	cpid = wait(&stat);
// 	if (pid == 0)
// 		write_to_pipe(fds, argv, envp);
// 	else if (pid > 0)
// 		read_from_pipe(fds, argv);
// 	return (0);
// }

void	free_paths(char ***paths)
{
	int	i;
	
	if (!*paths)
		return ;
	i = 0;
	while ((*paths)[i])
	{
		if ((*paths)[i])
			free((*paths)[i]);
		i++;
	}
	free(*paths);
	*paths = NULL;
}

void	do_first_cmd(char **argv, char **envp)
{
	char	*path;
	char	*cmd;

	cmd = cmd_2d_array(argv[2], argv[1]);
	path = get_right_path(envp, cmd);
}

int	pipex(char **argv, char **envp)
{
	int	fds[2];
	int	pid;
	int	cpid;
	int	status;

	if (pipe(fds) < 0)
		return (perror("Error: "), 0);
	pid = fork();
	cpid = wait(&status);
	if (pid == 0)
		do_first_cmd(argv, envp);
	else
		do_second_cmd(argv, envp);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		return (ft_putendl_fd("Error\nIncorrect amount of arguments.", 2), 1);
	pipex(argv, envp);
	// char	*path = get_right_path(envp, argv[2]);
	// if (!path)
	// 	return (1);
	// char	**av = find_cmd(argv[2], argv[1]);
	// if (!av)
	// 	return (free(path), 1);
	// if (execve(path, av, envp) == -1)
	// 	return (free(path), free_paths(&argv), 1);
	// // do_cmd(argv[1], argv[2], path, envp);
	// argv = NULL;
	// return (0);
}
