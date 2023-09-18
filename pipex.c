/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlima <vlima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:51:46 by vlima             #+#    #+#             */
/*   Updated: 2023/09/18 14:54:42 by vlima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>

char	*ft_path(char *cmd, char **envp)
{
	int		i;
	char	**all_paths;
	char	*res;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (envp[i] == NULL)
		return (0);
	if (envp[i])
	{
		all_paths = ft_split(envp[i] + 5, ':');
		i = -1;
		while (all_paths[++i])
		{
			res = ft_strcat(ft_strcat(all_paths[i], "/"), cmd);
			if (access(res, F_OK) == 0)
				break ;
		}
		free_all(all_paths);
		return (res);
	}
	return (NULL);
}

char	*ft_pwd_path(char *cmd, char **env)
{
	int		i;
	char	*pwd_path;
	char	*res;
	int		j;

	i = 0;
	j = -1;
	while (env[i] && ft_strnstr(env[i], "PWD=", 4) == NULL)
		i++;
	if (env[i] == NULL)
		error("something worng with envp");
	pwd_path = (char *)malloc((ft_strlen(env[i]) - 4) * sizeof(char));
	if (pwd_path == NULL)
		error("error in malloc");
	while (++j < ft_strlen(env[i]) - 4)
		pwd_path[j] = env[i][j + 4];
	pwd_path[j++] = '\0';
	pwd_path = ft_strcat(pwd_path, "/");
	res = ft_strcat(pwd_path, cmd);
	free(pwd_path);
	if (access(res, F_OK | X_OK) == 0)
		return (res);
	error("Command error not exist\n");
	return (0);
}

void	ft_get_cmd(char *av, char **envp)
{
	char	**cmd;
	char	**cmd2;
	char	*path;
	int		i;

	i = 0;
	cmd2 = ft_split(av, ' ');
	cmd = ft_split(av, ' ');
	if (access(cmd[0], X_OK) == 0)
	{
		cmd = ft_split(av, '/');
		while (cmd[i])
			i++;
		cmd = ft_split(cmd[i - 1], ' ');
		execve(cmd2[0], cmd, envp);
	}
	free_all(cmd2);
	path = ft_path(cmd[0], envp);
	if (path == NULL)
		path = ft_pwd_path(cmd[0], envp);
	if (execve(path, cmd, envp) == -1)
		i = -1;
	//free(path);
	free_all(cmd);
	if (i == -1)
		error("Command error in get cmd");
}

void	ft_parent_process(char **av, char **envp, int *fd)
{
	int	fd_out;
	if (envp == NULL)
		error("something worng with envp");
	fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		close(fd[0]);
		close(fd[1]);
		error("Permission denied error\n");
	}
	dup2(fd[0], 0);
	dup2(fd_out, 1);
	close(fd[1]);
	ft_get_cmd(av[3], envp);
	close(fd_out);
}

void	ft_child_process(char **av, char **envp, int *fd)
{
	if (envp == NULL)
		error("something worng with envp\n");
	if (access(av[1], F_OK) != 0)
		error("No such file or directory error\n");
	if (access(av[1], R_OK) != 0)
		error("Permission denied error\n");
	dup2(fd[1], 1);
	dup2(open(av[1], O_RDONLY), 0);
	close(fd[0]);
	ft_get_cmd(av[2], envp);
}

int	main(int ac, char **av, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (ac != 5)
		error("Invalid parameters!\n");
	if (pipe(fd) == -1)
		error("Error creating the pipe");
	pid = fork();
	if (pid == -1)
		error("Error while creating a fork");
	if (pid == 0)
		ft_child_process(av, envp, fd);
	ft_parent_process(av, envp, fd);
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	return (0);
}
