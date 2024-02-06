/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:30:24 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/06 14:53:05 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_cmd_not_found(t_data *data, char	**arr, int cmd_nro)
{
	free_2d_array(arr);
	ft_putstr_fd("pipex: command not found: ", 2);
	if (cmd_nro == 1)
		ft_putendl_fd(data->cmd1, 2);
	else
		ft_putendl_fd(data->cmd2, 2);
	free(data);
	exit(127);
}

void	ft_no_such_file(t_data *data, int cmd_nro)
{
	if (cmd_nro == 1)
		ft_putstr_fd(data->cmd1, 2);
	else
		ft_putstr_fd(data->cmd2, 2);
	ft_putstr_fd(": ", 2);
	if (cmd_nro == 1)
		ft_putstr_fd(data->file1, 2);
	else
		ft_putstr_fd(data->file2, 2);
	ft_putendl_fd(": No such file or directory", 2);
	free(data);
	exit(1);
}

void	ft_permission_denied_cmd(t_data *data, char **arr, int cmd_nro)
{
	ft_putstr_fd("pipex: permission denied: ", 2);
	if (cmd_nro == 1)
		ft_putendl_fd(data->cmd1, 2);
	else
		ft_putendl_fd(data->cmd2, 2);
	free(data);
	free_2d_array(arr);
	exit(126);
}

//add error for "cannot execute binary file"
//example:
///bin/cat: /bin/cat: cannot execute binary file