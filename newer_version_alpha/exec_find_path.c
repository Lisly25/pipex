/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_find_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:54:27 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/07 13:57:23 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_for_access(t_data *data, char *path, char ***arr_ptr, int cmd_nro)
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
			ft_permission_denied_cmd(data, arr, cmd_nro);
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
		run_if_non_shell_command(command, data, 1);
		i++;
	}
	all_paths = find_paths(data, command, 1);
	while (all_paths[i] != NULL)
	{
		full_path = path_strjoin(&all_paths, command, i, data);
		i++;
		if (check_for_access(data, full_path, command, 1) == 0)
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
		i++;
	}
	all_paths = find_paths(data, command, 2);
	while (all_paths[i] != NULL)
	{
		full_path = path_strjoin(&all_paths, command, i, data);
		i++;
		if (check_for_access(data, full_path, command, 2) == 0)
			break ;
		free(full_path);
	}
	free_2d_array(all_paths);
	if (all_paths[i] == NULL)
		return (NULL);
	return (full_path);
}
