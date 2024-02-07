/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:30:24 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/07 11:47:59 by skorbai          ###   ########.fr       */
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

static void	ft_permission_denied_file(t_data *data, int cmd_nro)
{
	if (cmd_nro == 1)
	{
		if (access(data->file1, F_OK) == 0)
		{
			ft_putstr_fd("pipex: permission denied: ", 2);
			ft_putendl_fd(data->file1, 2);
			free(data);
			exit(126);
		}
		else
			return ;
	}
	if (cmd_nro == 2)
	{
		if (access(data->file2, F_OK) == 0)
		{
			ft_putstr_fd("pipex: permission denied ", 2);
			ft_putendl_fd(data->file2, 2);
			free(data);
			exit(126);
		}
		else
			return ;
	}
}

void	ft_no_such_file(t_data *data, int cmd_nro)
{
	ft_permission_denied_file(data, cmd_nro);
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
	exit(127);
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

//have a special permission denied message for directories (with open there's an option to open a folder)
//check if I give the same error message as the terminal when PATH is unset
// also "zsh: exec format error: ./metal" - if execve fails (just need to edit error message)