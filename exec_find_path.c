/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_find_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:54:27 by skorbai           #+#    #+#             */
/*   Updated: 2024/01/31 15:58:02 by skorbai          ###   ########.fr       */
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

char	*find_correct_path(char ***command, char ***env)
{
	char		**all_paths;
	static int	i = -1;
	char		*full_path;

	run_if_shell_command(command, env);
	if (i == -1)
	{
		full_path = find_bultin_path();
		i++;
		if (full_path != NULL)
			return (full_path);
	}
	all_paths = find_paths(env, command);
	while (all_paths[i] != NULL)
	{
		full_path = path_strjoin(&all_paths, command, i);
		i++;
		if (access(full_path, X_OK) == 0)
			break ;
		free(full_path);
	}
	free_2d_array(all_paths);
	if (all_paths[i] == NULL)
		return (NULL);
	return (full_path);
}

char	*find_correct_path_cmd2(char ***command, char ***env)
{
	char		**all_paths;
	static int	i = -1;
	char		*full_path;

	run_if_shell_command(command, env);
	if (i == -1)
	{
		full_path = find_bultin_path();
		i++;
		if (full_path != NULL)
			return (full_path);
	}
	all_paths = find_paths(env, command);
	while (all_paths[i] != NULL)
	{
		full_path = path_strjoin(&all_paths, command, i);
		i++;
		if (access(full_path, X_OK) == 0)
			break ;
		free(full_path);
	}
	free_2d_array(all_paths);
	if (all_paths[i] == NULL)
		return (NULL);
	return (full_path);
}
