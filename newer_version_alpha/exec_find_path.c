/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_find_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:54:27 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/06 14:02:46 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*static char	**get_builtin_command(char ***og_command_ptr, t_data *data)
{
	char	**result;
	char	**og_command;
	int		i;
	int		j;

	og_command = *og_command_ptr;
	i = 0;
	j = 1;
	while (og_command[i] != NULL)
		i++;
	result = (char **)malloc(sizeof(char) * (i + 2));
	if (result == NULL)
		ft_free_and_exit("Error: Malloc fail", og_command, data, 1);
	result[0] = "-c";
	i = 0;
	while (og_command[i] != NULL)
	{
		result[j] = og_command[i];
		j++;
		i++;
	}
	result[j] = NULL;
	//ft_putstr_fd(result[0], 2);
	//ft_putstr_fd(result[1], 2);
	return (result);
}*/

/*static void	find_bultin_path(t_data *data, char ***command_ptr)
{
	char	**command;
	//char	**comm_builtin_version;

	command = *command_ptr;
	//comm_builtin_version = get_builtin_command(command_ptr, data);
	if (access("/bin/zsh", X_OK) == -1)
		return ;
	else
	{
		if (execve("/bin/zsh", command, data->env) == -1)
			return ;
	}
}*/

char	*find_correct_path(char ***command, t_data *data)
{
	char		**all_paths;
	static int	i = -1;
	char		*full_path;

	if (i == -1)
	{
		run_if_non_shell_command(command, data, 1);
		//find_bultin_path(data, command);
		i++;
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
		//find_bultin_path(data, command);
		i++;
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
