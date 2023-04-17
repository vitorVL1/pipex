/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima <vlima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:51:46 by vlima             #+#    #+#             */
/*   Updated: 2023/04/14 11:33:39 by vlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	error(char *str)
{
	perror(str);
	exit(1);
}

int	str_ichr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	if (s[i] == (char)c)
		return (i);
	return (-1);
}

char	*path_finder(char **cmds, char **envp)
{
	int		i;
	char	*cmd;
	char	*path;
	char	*dir;
	char	*bin;

	cmd = cmds[0];
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (cmd);
	path = envp[i] + 5;
	while (path && str_ichr(path, ':') > -1)
	{
		dir = ft_substr(path, 0, str_ichr(path, ':'));
		bin = ft_strjoin(ft_strjoin(dir, "/"), cmd);
		free(dir);
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
		path += str_ichr(path, ':') + 1;
	}
	return (cmd);
}

void	child_parent(char **av, int *pipe_fd, char **envp, int fd)
{
	char	**cmds;

	if (fork() == 0)
	{
		dup2(fd, 0);
		dup2(pipe_fd[1], 1);
		close(pipe_fd[0]);
		cmds = ft_split(av[2], ' ');
		execve(path_finder(cmds, envp), cmds, NULL);
	}
	else
	{
		dup2(fd, 1);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[1]);
		cmds = ft_split(av[3], ' ');
		execve(path_finder(cmds, envp), cmds, NULL);
	}
}

int	main(int ac, char **av, char **envp)
{
	int		file1;
	int		file2;
	int		pipe_fd[2];
	pid_t	pid;

	if (ac != 5)
		error("Invalid parameters!\n");
	file1 = open(av[1], O_CREAT | O_RDWR);
	file2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (file1 < 0 || file2 < 0)
		error("Error while opening infile or outfile\n");
	if (pipe(pipe_fd) == -1)
		error("Error creating the pipe");
	pid = fork();
	if (pid == -1)
		error("Error while creating a fork");
	if (pid == 0)
		child_parent(av, pipe_fd, envp, file1);
	child_parent(av, pipe_fd, envp, file2);
	return (0);
}
