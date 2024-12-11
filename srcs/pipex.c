/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:35:45 by npolack           #+#    #+#             */
/*   Updated: 2024/12/11 00:27:38 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
/*
char	**get_cmds(int ac, char **av)
{
	char	**cmds;
	int		i,

	cmds = (char**)malloc(sizeof (char *) * (ac - 2));
	i = 0;
	while (i < ac - 2)
	{
		cmds[i] = ft_strdup(av[i + 1]);
		i++;
	}
	return (cmds);
}
*/

char	**get_files(int ac, char **av)
{
	int	i;
	char **file;

	file = malloc(sizeof (char *) * 2);
	file[0] = ft_strdup(av[1]);
	file[1] = ft_strdup(av[ac - 1]);
	return (file);
}

int	find_path(char *str)
{
	char *cmd;

	cmd = ft_strjoin("usr/bin/", str);
	access(cmd, X_OK);
	return (0);
}
int	main(int ac, char** av, char **env)
{
	char **arg;
	char **cmd;
	int fd_out;
	int	fd_in;
	int child;
	char **file;
	int	i = 0;
	char	**paths;
	int	pid;

	int pipefd[2];

	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			break ;
		i++;
	}
	env[i] += 5;
	paths = ft_split(env[i], ':');
	cmd = malloc(sizeof (char *) * 2);
	i = 0;
	while (paths[i])
	{
		cmd[0] = ft_strjoin(paths[i], ft_strjoin("/", av[2]));
		if (access(cmd[0], X_OK))
			break ;
		i++;
	}

	i = 0;
	while (paths[i])
	{
		cmd[1] = ft_strjoin(paths[i], ft_strjoin("/", av[3]));
		if (access(cmd[1], X_OK))
			break ;
		i++;
	}
	arg = malloc(sizeof (char *) * 2),

	pid = fork();
	pipe(pipefd);
	fd_in = open(av[1], O_RDONLY);
	fd_out = open(av[4], O_CREAT | O_WRONLY);

	if (pid == 0)
	{
		arg[0] = ft_strdup(cmd[0]);
		arg[1] = NULL;
		dup2(pipefd[0], 0);
		close(pipefd[1]);
		execve(cmd[0], arg, env);
	} 
  	else
    {
		arg[0] = ft_strdup(cmd[1]);
		arg[1] = NULL;
		dup2(pipefd[1], 1);
        close(pipefd[0]);
        execve(cmd[1], arg, env);
    }
    // close unused pipe
    close(pipefd[0]);
    close(pipefd[1]);
	//waitpid(pid);
/*
	child = fork();
	if (child == 0)
	{
		execve(cmd);
	}
	else
	{
		waitpid();

	}
*/

	return (0);
}


