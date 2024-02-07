/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_abs_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:33:58 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/07 16:10:03 by skorbai          ###   ########.fr       */
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
		check_if_dir_error(data, path, command);
		if (ft_strchr(path, '/') != NULL)
		{
			if (execve(path, command, data->env) == -1)
			{
				free(path);
				ft_exec_format_error(data, command, cmd_nro);
			}
		}
		else
		{
			free(path);
			ft_cmd_not_found(data, command);
		}
	}
}
