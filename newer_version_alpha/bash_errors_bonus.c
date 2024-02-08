/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_errors_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:00:31 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/08 15:00:54 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_cmd_not_found(t_data *data, char	**arr)
{
	ft_putstr_fd("pipex: command not found: ", 2);
	ft_putendl_fd(arr[0], 2);
	free_2d_array(arr);
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
	ft_putstr_fd("pipex: no such file or directory: ", 2);
	/*if (cmd_nro == 1)
		ft_putstr_fd(data->cmd1, 2);
	else
		ft_putstr_fd(data->cmd2, 2);
	ft_putstr_fd(": ", 2);*/
	if (cmd_nro == 1)
		ft_putendl_fd(data->file1, 2);
	else
		ft_putendl_fd(data->file2, 2);
	close(data->pipe_fds[PIPE_READ_END]);
	close(data->pipe_fds[PIPE_WRITE_END]);
	free(data);
	exit(127);
}

void	ft_permission_denied_cmd(t_data *data, char **arr)
{
	ft_putstr_fd("pipex: permission denied: ", 2);
	ft_putendl_fd(arr[0], 2);
	free(data);
	free_2d_array(arr);
	exit(126);
}

void	ft_exec_format_error(t_data *data, char **arr)
{
	ft_putstr_fd("pipex: exec format error: ", 2);
	ft_putendl_fd(arr[0], 2);
	free(data);
	free_2d_array(arr);
	exit(1);
}
