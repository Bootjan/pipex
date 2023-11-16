/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschaafs <bschaafs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:19:06 by bschaafs          #+#    #+#             */
/*   Updated: 2023/11/16 21:10:27 by bschaafs         ###   ########.fr       */
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

char	**compute_paths(char **envp)
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

int	space_index(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != ' ')
		i++;
	return (i);
}

char	*compute_poss_path(char *path, char *sub_cmd)
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

char	*compute_right_path(char **paths, char *cmd)
{
	char	*sub_cmd;
	char	*poss_path;
	int		i;

	sub_cmd = ft_substr(cmd, 0, space_index(cmd));
	if (!sub_cmd)
		return (NULL);
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

char	**clean_cmd(char *cmd)
{
	char	**argv;
	int		len;
	int		i;
	char	*temp_cmd;
	
	temp_cmd = ft_strjoin(cmd, file);
	len = (int)ft_strlen(cmd);
	i = 0;
	while (ft_isalpha(cmd[i]))
		i++;
	argv = ft_split(&cmd[i], ' ');
	if (!argv)
		return (NULL);
	return (argv);
}

int	do_cmd(char *file, char *cmd, char **paths, char **envp)
{
	char	*path;
	char	**argv;

	path = compute_right_path(paths, cmd);
	if (!path)
		return (0); // error msg
	argv = clean_cmd(cmd, file);
	if (!argv)
		return (free_paths(&paths), 0);
	if (execve(path, argv, envp) == -1)
		return (free_paths(&paths), 0);
	ft_printf("PATH=%s\n", path);
	free(path);
	file = NULL;
	return ()
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		return (ft_putendl_fd("Error\nIncorrect amount of arguments.", 2), 1);
	char	**paths = compute_paths(envp);
	if (!paths)
		return (1);
	do_cmd(argv[1], argv[2], paths, envp);
	free_paths(&paths);
	argv = NULL;
}
