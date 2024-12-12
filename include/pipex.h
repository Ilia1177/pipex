/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:36:52 by npolack           #+#    #+#             */
/*   Updated: 2024/12/12 15:10:40 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
#  include <sys/wait.h>
# include <fcntl.h>
# include "../libft/include/libft.h"
#include <stdio.h>

void	printargs(char **args);
void wait_all_child(int child_nb);
int free_all(char **args);
char	**build_args(char *av, char *cmd);
char *get_full_path(char **paths, char *str);
char	**get_paths(char **env);

#endif
