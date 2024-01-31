/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:19:41 by skorbai           #+#    #+#             */
/*   Updated: 2024/01/31 13:35:22 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*find_path_env_variable(char ***environmentals)
{
	int		i;
	char	*result;
	char	**env;

	env = *environmentals;
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			result = ft_strchr(env[i], '/');
			return (result);
		}
		else
			i++;
	}
	return (NULL);
}

static int	is_shell_command(char **command)
{
	//ft_printf("To be done (?) later - is shell command\n");
	//ft_printf(command[0]);
	if (command[0] == NULL)
		exit(1);
	return (0);
}

static void	find_path_own_exec(char **command)
{
	//ft_printf("To be done (?) later - find path own exec\n");
	//ft_printf(command[0]);
	if (command[0] == NULL)
		exit(1);
	exit (1);
}

/*char	*find_correct_path(char **command, char ***env)
{
	char			*paths;
	char			**all_paths;
	static int		i = 0;
	char			*result;

	if (is_shell_command(command) == 1)
		find_path_own_exec(command);
	paths = find_path_env_variable(env);
	//ft_printf("string is: %s\n", paths);
	all_paths = ft_split(paths, ':');
	//deleteme_arr_print(all_paths);
	if (all_paths == NULL)
		ft_message_and_exit("Malloc fail when finding correct executable path");
	while (all_paths[i] != NULL)
	{
		if (access(all_paths[i], F_OK) == -1)
			i++;
		else
		{
			result = ft_strdup(all_paths[i]);
			free_2d_array(all_paths);
			//ft_printf("Did we return here? Result is %s\n", result);
			i++;
			return (result);
		}
	}
	free_2d_array(all_paths);
	return (NULL);
}*/

/*char	*find_correct_path_cmd2(char **command, char ***env)
{
	char			*paths;
	char			**all_paths;
	static int		i = 0;
	char			*result;

	if (is_shell_command(command) == 1)
		find_path_own_exec(command);
	paths = find_path_env_variable(env);
	//ft_printf("string is: %s\n", paths);
	all_paths = ft_split(paths, ':');
	//deleteme_arr_print(all_paths);
	if (all_paths == NULL)
		ft_message_and_exit("Malloc fail when finding correct executable path");
	while (all_paths[i] != NULL)
	{
		if (access(all_paths[i], F_OK) == -1)
			i++;
		else
		{
			result = ft_strdup(all_paths[i]);
			free_2d_array(all_paths);
			//ft_printf("Did we return here? Result is %s\n", result);
			i++;
			return (result);
		}
	}
	free_2d_array(all_paths);
	return (NULL);
}*/

char	*find_correct_path(char **command, char ***env)
{
	char		**all_paths;
	static int	i = -1;
	char		*full_path;

	if (is_shell_command(command) == 1)
		find_path_own_exec(command);
	all_paths = ft_split(find_path_env_variable(env), ':');
	if (all_paths == NULL)
		ft_message_and_exit("Malloc fail when finding correct executable path");
	if (i == -1)
	{
		if (access("/bin/bash", X_OK) == -1)
			i++;
		else
			return ("/bin/bash");
	}
	while (all_paths[i] != NULL)
	{
		full_path = ft_strjoin(all_paths[i], command[0]);
		if (full_path == NULL)
			ft_free_and_exit("Error: malloc fail", all_paths);
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
	all_paths = ft_split(find_path_env_variable(env), ':');
	if (all_paths == NULL)
		ft_message_and_exit("Malloc fail when finding correct executable path");
	if (i == -1)
	{
		if (access("/bin/bash", X_OK) == -1)
			i++;
		else
			return ("/bin/bash");
	}
	while (all_paths[i] != NULL)
	{
		full_path = ft_strjoin(all_paths[i], command[0]);
		if (full_path == NULL)
			ft_free_and_exit("Error: malloc fail", all_paths);
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
