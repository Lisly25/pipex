/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_abs_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:33:58 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/06 15:47:07 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_abs_path(t_data *data, char ***command_ptr, int cmd_nro)
{
	char	**command;
	char	*path;

	command = *command_ptr;
	path = ft_strdup(command[0]);
	if (path == NULL)
		ft_free_and_exit("pipex: malloc error", command, data, 1);
	if (check_for_access(data, path, command_ptr, cmd_nro) == 0)
	{
		if (ft_strchr(path, '/') != NULL)
		{
			if (execve(path, command, data->env) == -1)
			{
				free(path);
				ft_free_and_exit("pipex: execution failed", command, data, 1);
			}
		}
		else
		{
			free(path);
			ft_cmd_not_found(data, command, cmd_nro);
		}
	}
}
