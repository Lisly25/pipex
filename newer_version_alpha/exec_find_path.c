/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_find_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:54:27 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/05 16:14:39 by skorbai          ###   ########.fr       */
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

char	*find_correct_path(char ***command, t_data *data)
{
	char		**all_paths;
	static int	i = -1;
	char		*full_path;

	if (i == -1)
	{
		run_if_non_shell_command(command, data, 1);
		full_path = find_bultin_path();
		i++;
		if (full_path != NULL)
			return (full_path);
	}
	all_paths = find_paths(data, command);
	while (all_paths[i] != NULL)
	{
		full_path = path_strjoin(&all_paths, command, i, data);
		i++;
		if (access(full_path, X_OK) == 0)
			break ;
		free(full_path);
	}
	if (all_paths[i] == NULL)
		return (NULL);
	free_2d_array(all_paths);
	return (full_path);
}

char	*find_correct_path_cmd2(char ***command, t_data *data)
{
	char		**all_paths;
	static int	i = -1;
	char		*full_path;

	if (i == -1)
	{
		run_if_non_shell_command(command, data, 2);
		full_path = find_bultin_path();
		i++;
		if (full_path != NULL)
			return (full_path);
	}
	all_paths = find_paths(data, command);
	while (all_paths[i] != NULL)
	{
		full_path = path_strjoin(&all_paths, command, i, data);
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
