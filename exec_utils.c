/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:19:41 by skorbai           #+#    #+#             */
/*   Updated: 2024/01/29 16:40:57 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*find_path_env_variable(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (ft_strchr(env[i], '/'));
		else
			i++;
	}
	return (NULL);
}

static int	is_shell_command(char **command)
{
	ft_printf("To be done (?) later\n");
	ft_printf(command[0]);
	return (1);
}

static void	find_path_own_exec(char **command)
{
	ft_printf("To be done (?) later\n");
	ft_printf(command[0]);
	exit (1);
}

char	*find_correct_path(char **command, char **env)
{
	char	*paths;
	char	**all_paths;
	int		i;
	char	*result;

	i = 0;
	if (is_shell_command(command) != 1)
		find_path_own_exec(command);
	paths = find_path_env_variable(env);
	all_paths = ft_split(paths, ':');
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
			return (result);
		}
	}
	free_2d_array(all_paths);
	return (NULL);
}
