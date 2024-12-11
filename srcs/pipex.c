/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:35:45 by npolack           #+#    #+#             */
/*   Updated: 2024/12/11 13:26:14 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**get_paths(char **env)
{
	char **paths;
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			break ;
		i++;
	}
	env[i] += 5;
	paths = ft_split(env[i], ':');
	return (paths);
}

char *get_full_path(char **paths, char *str)
{
	int	i;
	char *full_path;
	char *cmd;
	char *tmp;

	tmp = malloc(sizeof(char) * (ft_strnlen(str, ' ') + 1));
	i = -1;
	while (++i < ft_strnlen(str, ' '))
		tmp[i] = str[i];
	tmp[i] = '\0';
	cmd = ft_strjoin("/", tmp);
	free(tmp);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], cmd);
		if (access(full_path, X_OK))
			break ;
		free(full_path);
		i++;
	}
	free(cmd);
	return (full_path);
}

char	**build_args(char *str, char *cmd)
{
	char **args;
	char *string;
	char *tmp;

	tmp = ft_strjoin(cmd, " ");
	string = ft_strjoin(tmp, str);
	args = ft_split(string, ' ');
	free(tmp);
	return (args);
}

int free_all(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
	return (0);
}

void wait_all_child(int child_nb) 
{
	int status;
	pid_t pid;
	int n = 0;
	while (n < child_nb)
	{
		pid = wait(&status);
		n++;
	}
}

int	main(int ac, char** av, char **env)
{
	char	**args;
	char	*cmd;
	int		fd_out;
	int		fd_in;
	char	**file;
	char	**paths;
	pid_t		pid;
	int		pipefd[2];
	int		nb_of_cmd;
	int		i;

	paths = get_paths(env);

	fd_in = open(av[1], O_RDONLY);
	fd_out = open(av[ac - 1], O_CREAT | O_WRONLY);

	nb_of_cmd = ac - 3;
	i = 1;
	while (i <= nb_of_cmd)
	{
		pipe(pipefd);
		pid = fork();
		if (pid == 0)
		{
			cmd = get_full_path(paths, av[i + 1]);
			args = build_args(av[i + 1], cmd);
			if (i == 1)
				dup2(fd_in, 0);
			else
				dup2(pipefd[0], 0);
			if (i == nb_of_cmd)
				dup2(fd_out, 1);
			else
				dup2(pipefd[1], 1);
			close(pipefd[1]);
			close(pipefd[0]);
			if (execve(cmd, args, env) == -1)
				exit(0);
		}
		i++;
	}
	wait_all_child(nb_of_cmd);
    close(pipefd[0]);
    close(pipefd[1]);
	return (0);
}


