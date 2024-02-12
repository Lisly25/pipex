/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_middle_command_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:09:12 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/12 15:45:52 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	init_fds_middle_cmd(t_data *data)
{
	close(data->pipe_fds[PIPE_WRITE_END]);
	close(data->next_pipe_fds[PIPE_READ_END]);
	if (dup2(data->pipe_fds[PIPE_READ_END], STDIN_FILENO) == -1)
	{
		ft_putendl_fd("pipex: dup2 error", 2);
		close(data->pipe_fds[PIPE_READ_END]);
		close(data->next_pipe_fds[PIPE_WRITE_END]);
		free(data);
		exit(1);
	}
	if (dup2(data->next_pipe_fds[PIPE_WRITE_END], STDOUT_FILENO) == -1)
	{
		ft_putendl_fd("pipex: dup2 error", 2);
		close(data->pipe_fds[PIPE_READ_END]);
		close(data->next_pipe_fds[PIPE_WRITE_END]);
		free(data);
		exit(1);
	}
	close(data->pipe_fds[PIPE_READ_END]);
	close(data->next_pipe_fds[PIPE_WRITE_END]);
}

void	exec_middle_command(t_data *data, char **argv, int i)//I should only need "data", but I need to change how we initialize it
{
	init_fds_middle_cmd(data);
	check_empty_cmd_arg(data, i + 1);//should also change how this and all other such error checker functions work
	
}
