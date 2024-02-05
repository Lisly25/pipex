/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_abs_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:33:58 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/05 16:39:46 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_abs_path(t_data *data, char ***command_ptr, int cmd_nro)
{
	char	**command;

	command = *command_ptr;
	if (access(command[0], X_OK) == 0)
	{
		if (ft_strchr(command[0], '/') != NULL)
		{
			if (execve(command[0], command, data->env) == -1)
				ft_free_and_exit("Failed to execute command", command, data, 1);
		}
		else
			ft_cmd_not_found(data, command, cmd_nro);
	}
}
