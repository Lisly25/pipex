/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:19:41 by skorbai           #+#    #+#             */
/*   Updated: 2024/01/31 15:18:30 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**find_paths(char ***environmentals, char ***command)
{
	int		i;
	char	**result;
	char	*path_str;
	char	**env;

	env = *environmentals;
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path_str = ft_strchr(env[i], '/');
			result = ft_split(path_str, ':');
			return (result);
		}
		else
			i++;
	}
	ft_free_and_exit("Error: Failed to locate PATH", *command);
	return (NULL);
}

int	is_shell_command(char **command)
{
	if (command[0] == NULL)
		exit(1);
	return (0);
}

void	find_path_own_exec(char **command)
{
	if (command[0] == NULL)
		exit(1);
	exit (1);
}

char	*path_strjoin(char ***paths_ptr, char ***commands_ptr, int i)
{
	char	*slash;
	char	*temp;
	char	*result;
	char	**paths;
	char	**commands;

	paths = *paths_ptr;
	commands = *commands_ptr;
	slash = (char *)malloc(2);
	slash[0] = '/';
	slash[1] = '\0';
	temp = ft_strjoin(paths[i], slash);
	if (temp == NULL)
		ft_free_2_2d_arrays_and_exit("Error: Malloc fail", paths, commands);
	result = ft_strjoin(temp, commands[0]);
	if (result == NULL)
	{
		free(temp);
		ft_free_2_2d_arrays_and_exit("Error: Malloc fail", paths, commands);
	}
	free(temp);
	return (result);
}
