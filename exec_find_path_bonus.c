/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_find_path_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:57:31 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/09 10:43:17 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	check_for_access(t_data *data, char *path, char ***arr_ptr)
{
	char	**arr;

	arr = *arr_ptr;
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
			return (0);
		else
		{
			free(path);
			ft_permission_denied_cmd(data, arr);
		}
	}
	return (1);
}

char	*find_correct_path(char ***command, t_data *data)
{
	char		**all_paths;
	static int	i = -1;
	char		*full_path;

	if (i == -1)
	{
		if (ft_strchr(data->cmd1, '/') != NULL)
			run_if_non_shell_command(command, data);
		i++;
	}
	all_paths = find_paths(data, command);
	while (all_paths[i] != NULL)
	{
		full_path = path_strjoin(&all_paths, command, i, data);
		i++;
		if (check_for_access(data, full_path, command) == 0)
		{
			free_2d_array(all_paths);
			return (full_path);
		}
		free(full_path);
	}
	free_2d_array(all_paths);
	return (NULL);
}

char	*find_correct_path_cmd2(char ***command, t_data *data)
{
	char		**all_paths;
	static int	i = -1;
	char		*full_path;

	if (i == -1)
	{
		if (ft_strchr(data->cmd2, '/') != NULL)
			run_if_non_shell_command(command, data);
		i++;
	}
	all_paths = find_paths(data, command);
	while (all_paths[i] != NULL)
	{
		full_path = path_strjoin(&all_paths, command, i, data);
		i++;
		if (check_for_access(data, full_path, command) == 0)
		{
			free_2d_array(all_paths);
			return (full_path);
		}
		free(full_path);
	}
	free_2d_array(all_paths);
	return (NULL);
}
