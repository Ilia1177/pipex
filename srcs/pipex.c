/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:35:45 by npolack           #+#    #+#             */
/*   Updated: 2024/12/11 21:56:26 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	printargs(char **args);

char	**get_paths(char **env)
{
	char **paths;
	int		i;

	paths = NULL;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			env[i] += 5;
			paths = ft_split(env[i], ':');
			env[i] -= 5;
			return (paths);
		}
		i++;
	}

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
		if (!access(full_path, X_OK))
		{
			free(cmd);
			return (full_path);	
		}
		free(full_path);
		i++;
	}
	free(cmd);
	return (NULL);
}

char	**build_args(char *av, char *cmd)
{
	char **args;
	char *string;
	char *tmp;

	while(*av && *av != ' ')
		av++;
	string = ft_strjoin(cmd, " ");
	tmp = string;
	string = ft_strjoin(tmp, av);
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
	int n = 0;
	while (n < child_nb)
	{
		wait(&status);
		n++;
	}
}
void	printargs(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		ft_putendl_fd(args[i], 2);
		i++;
	}
}

int	main(int ac, char** av, char **env)
{
	char	**args;
	char	*cmd;
	int		fd_out;
	int		fd_in;
	char	**paths;
	pid_t		pid;
	int		pipefd[2];
	int		nb_of_cmd;
	int		i;

	paths = get_paths(env);
	fd_in = open("test", O_RDONLY, 0777);
	fd_out = open("OUTF", O_CREAT | O_WRONLY | O_APPEND, 0666);
	nb_of_cmd = ac - 3;
	i = 1;
	while (i <= nb_of_cmd)
	{
		//if (i % 2 == 1)
			pipe(pipefd);
		pid = fork();
		if (!pid)
		{
			cmd = get_full_path(paths, av[i + 1]);
			args = build_args(av[i + 1], cmd);
			if (i == 1)
			{
				dup2(fd_in, 0);
				dup2(pipefd[1], 1);
				//close(pipefd[1]);
			}
			if (i == 2)
			{
				dup2(fd_out, 1);
				dup2(pipefd[0], 0);
				//close(pipefd[0]);
			}
			if (execve(cmd, args, env) == -1)
			{
				ft_putendl_fd("ERROR", 2);
				exit(0);
			}
		}
		//else
		//	waitpid(-1, NULL, 0);
		i++;
	}
	// Wait for all child processes
	waitpid(-1, NULL, 0);
    close(pipefd[0]);
    close(pipefd[1]);
	return (0);
}


