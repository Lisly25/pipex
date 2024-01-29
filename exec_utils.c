/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 11:19:41 by skorbai           #+#    #+#             */
/*   Updated: 2024/01/29 12:12:52 by skorbai          ###   ########.fr       */
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
			return (env[i]);
		else
			i++;
	}
	return (NULL);
}

char	*find_correct_path(char **command, char **env)
{
	char	*paths;
	char	**all_paths;
	int		i;
	char	*result;

	paths = find_path_env_variable(env);
	all_paths = ft_split(paths, ":");
	if (all_paths == NULL)
		ft_message_and_exit("Malloc fail when finding correct executable path");
	while (all_paths[i] != NULL)
	{
		if (access(all_paths[i], X_OK) == -1)
			i++;
		else
		{
			result = ft_strnstr(paths, all_paths[i], ft_strlen(all_paths[i]));
			free_2d_array(all_paths);
			return (result);
		}
	}
	free_2d_array(all_paths);
	ft_message_and_exit("Error: failed to execute command - but change this later according to how the shell handles this");
}
