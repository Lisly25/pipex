/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:55:56 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/08 14:57:04 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*pwd_strjoin(char *pwd_str, char ***commands_ptr, t_data *data)
{
	char	*temp;
	char	*result;
	char	**commands;

	commands = *commands_ptr;
	temp = ft_strjoin(pwd_str, "/");
	if (temp == NULL)
		ft_free_and_exit("pipex: malloc error", commands, data, 1);
	result = ft_strjoin(temp, commands[0]);
	if (result == NULL)
	{
		free(temp);
		ft_free_and_exit("pipex: malloc error", commands, data, 1);
	}
	free(temp);
	return (result);
}

char	**find_paths(t_data *data, char ***command)
{
	int		i;
	char	**result;
	char	*path_str;

	i = 0;
	while (data->env[i] != NULL)
	{
		if (ft_strncmp(data->env[i], "PATH=", 5) == 0)
		{
			path_str = ft_strchr(data->env[i], '/');
			result = ft_split(path_str, ':');
			return (result);
		}
		else
			i++;
	}
	ft_cmd_not_found(data, *command);
	return (NULL);
}

static char	*get_pwd(t_data *data, char ***command_ptr)
{
	int		i;
	char	**command;
	char	*result;
	char	*pwd_str;

	command = *command_ptr;
	i = 0;
	while (data->env[i] != NULL)
	{
		if (ft_strncmp(data->env[i], "PWD=", 4) == 0)
		{
			pwd_str = ft_substr(data->env[i], 4, ft_strlen(data->env[i]));
			result = pwd_strjoin(pwd_str, command_ptr, data);
			return (result);
		}
		i++;
	}
	ft_free_and_exit("pipex: Failed to locate PWD", command, data, 1);
	return (NULL);
}

void	run_if_non_shell_command(char ***command_ptr, t_data *data)
{
	char	**command;
	char	*pwd_path;

	command = *command_ptr;
	exec_abs_path(data, command_ptr);
	pwd_path = get_pwd(data, command_ptr);
	if (check_for_access(data, pwd_path, command_ptr) == 0)
	{
		check_if_dir_error(data, pwd_path, command);
		if (execve(pwd_path, command, data->env) == -1)
		{
			free(pwd_path);
			ft_exec_format_error(data, command);
		}
	}
	free(pwd_path);
	ft_no_such_file_as_cmd(data, command);
}

char	*path_strjoin(char ***paths_ptr, char ***comm_ptr, int i, t_data *data)
{
	char	*temp;
	char	*result;
	char	**paths;
	char	**commands;

	paths = *paths_ptr;
	commands = *comm_ptr;
	temp = ft_strjoin(paths[i], "/");
	if (temp == NULL)
	{
		free(data);
		ft_free_2d_arrs_and_exit("pipex: malloc error", paths, commands);
	}
	result = ft_strjoin(temp, commands[0]);
	if (result == NULL)
	{
		free(temp);
		free(data);
		ft_free_2d_arrs_and_exit("pipex: malloc error", paths, commands);
	}
	free(temp);
	return (result);
}
