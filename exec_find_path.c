/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_find_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:54:27 by skorbai           #+#    #+#             */
/*   Updated: 2024/01/31 15:19:19 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*find_bultin_path(void)
{
	if (access("/bin/bash/", X_OK) == -1)
		return (NULL);
	else
		return ("/bin/bash/");
}

char	*find_correct_path(char **command, char ***env)
{
	char		**all_paths;
	static int	i = -1;
	char		*full_path;

	if (is_shell_command(command) == 1)
		find_path_own_exec(command);
	all_paths = find_paths(env, &command);
	if (i == -1)
	{
		full_path = find_bultin_path();
		if (full_path != NULL)
			return (full_path);
		i++;
	}
	while (all_paths[i] != NULL)
	{
		full_path = path_strjoin(&all_paths, &command, i);
		if (access(full_path, X_OK) == -1)
			i++;
		else
		{
			free_2d_array(all_paths);
			i++;
			return (full_path);
		}
	}
	free_2d_array(all_paths);
	return (NULL);
}

char	*find_correct_path_cmd2(char **command, char ***env)
{
	char		**all_paths;
	static int	i = -1;
	char		*full_path;

	if (is_shell_command(command) == 1)
		find_path_own_exec(command);
	all_paths = find_paths(env, &command);
	if (i == -1)
	{
		full_path = find_bultin_path();
		if (full_path != NULL)
			return (full_path);
		i++;
	}
	while (all_paths[i] != NULL)
	{
		full_path = path_strjoin(&all_paths, &command, i);
		if (access(full_path, X_OK) == -1)
			i++;
		else
		{
			free_2d_array(all_paths);
			i++;
			return (full_path);
		}
	}
	free_2d_array(all_paths);
	return (NULL);
}
