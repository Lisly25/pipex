/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:55:26 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/12 15:24:46 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	check_ch_exit_stat(int child_status, t_data *data, int child_nro)
{
	int	exit_status;

	if (WIFSIGNALED(child_status) == 1)
	{
		exit_status = WTERMSIG(child_status);
		if (child_nro == 1)
			data->exit_status_1 = exit_status;
		else
			data->exit_status_2 = exit_status;
		return ;
	}
	if (WIFEXITED(child_status) == 1)
	{
		exit_status = WEXITSTATUS(child_status);
		if (child_nro == 1)
			data->exit_status_1 = exit_status;
		else
			data->exit_status_2 = exit_status;
	}
}

static void	print_segfault(t_data *data, int exit_status, int cmd_nro)
{
	if (exit_status == 11)
	{
		ft_putstr_fd("pipex: segmentation fault ", 2);
		if (cmd_nro == 1)
		{
			ft_putendl_fd(data->cmd1, 2);
			data->exit_status_1 = 139;
		}
		else
		{
			ft_putendl_fd(data->cmd2, 2);
			data->exit_status_2 = 139;
		}
	}
}

static void	print_bus_error(t_data *data, int exit_status, int cmd_nro)
{
	if (exit_status == 10)
	{
		ft_putstr_fd("pipex: bus error ", 2);
		if (cmd_nro == 1)
		{
			ft_putstr_fd(data->cmd1, 2);
			ft_putchar_fd(' ', 2);
			ft_putendl_fd(data->file1, 2);
			data->exit_status_1 = 138;
		}
		else
		{
			ft_putstr_fd(data->cmd2, 2);
			ft_putchar_fd(' ', 2);
			ft_putendl_fd(data->file2, 2);
			data->exit_status_2 = 138;
		}
	}
	print_segfault(data, exit_status, cmd_nro);
}

void	wait_for_children(t_data *data)
{
	int		child_1_status;
	int		child_2_status;

	if (waitpid(data->children[0], &child_1_status, 0) == -1)
	{
		free(data);
		ft_message_and_exit("pipex: Wait error (command 1)", 1);
	}
	check_ch_exit_stat(child_1_status, data, 1);
	if (data->children[1] > 0)
	{
		if (waitpid(data->children[1], &child_2_status, 0) == -1)
		{
			free(data);
			ft_message_and_exit("pipex: Wait error (command 2)", 1);
		}
		check_ch_exit_stat(child_2_status, data, 2);
		print_bus_error(data, data->exit_status_1, 1);
		print_bus_error(data, data->exit_status_2, 2);
	}
}

void	piping_loop(t_data *data, char *argv, int argc)
{
	int	i;

	i = 0;
	while (i < (argc - 3))
	{
		if (i % 2 == 0)
			init_pipe2(data);
		else
			init_pipe(data);
		init_middle_child(data, i);
		if (i % 2 == 0)
		{
			exec_middle_command(data, argv, i);
			close(data->pipe_fds[PIPE_READ_END]);
			close(data->next_pipe_fds[PIPE_WRITE_END]);
		}
		else
		{
			exec_middle_command_rev(data, argv, i);
			close(data->pipe_fds[PIPE_WRITE_END]);
			close(data->next_pipe_fds[PIPE_READ_END]);
		}
	}
}
