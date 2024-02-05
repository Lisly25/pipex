/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:19:41 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/05 10:44:53 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*pwd_strjoin(char *pwd_str, char ***commands_ptr)
{
	char	*temp;
	char	*result;
	char	**commands;

	commands = *commands_ptr;
	temp = ft_strjoin(pwd_str, "/");
	if (temp == NULL)
		ft_free_and_exit("Error: Malloc fail", commands);
	result = ft_strjoin(temp, commands[0]);
	if (result == NULL)
	{
		free(temp);
		ft_free_and_exit("Error: Malloc fail", commands);
	}
	free(temp);
	return (result);
}

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

static char	*get_pwd(char ***env_ptr, char ***command_ptr)
{
	int		i;
	char	**env;
	char	**command;
	char	*result;
	char	*pwd_str;

	env = *env_ptr;
	command = *command_ptr;
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			pwd_str = ft_substr(env[i], 4, ft_strlen(env[i]));
			result = pwd_strjoin(pwd_str, command_ptr);
			return (result);
		}
		i++;
	}
	ft_free_and_exit("Error: Failed to locate PWD", command);
	return (NULL);
}

void	run_if_non_shell_command(char ***command_ptr, char ***env_ptr)
{
	char	**command;
	char	**env;
	char	*pwd_path;

	command = *command_ptr;
	env = *env_ptr;
	pwd_path = get_pwd(env_ptr, command_ptr);
	if (access(pwd_path, X_OK) == 0)
	{
		if (command[0][0] == '.' && command[0][1] == '/')//change how this is checked maybe - could cause segfault if this string is less than two chars
		{
			if (execve(pwd_path, command, env) == -1)
			{
				free(pwd_path);
				ft_free_and_exit("Failed to execute command", command);
			}
		}
		else
		{
			free(pwd_path);
			ft_free_and_exit("pipex: command not found", command);
		}
	}
	else
		free(pwd_path);
}

char	*path_strjoin(char ***paths_ptr, char ***commands_ptr, int i)
{
	char	*temp;
	char	*result;
	char	**paths;
	char	**commands;

	paths = *paths_ptr;
	commands = *commands_ptr;
	temp = ft_strjoin(paths[i], "/");
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
