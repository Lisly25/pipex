/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_first_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:06:20 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/08 11:53:01 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_fds_cmd1(t_data *data)
{
	int	file_desc;

	close(data->pipe_fds[PIPE_READ_END]);
	file_desc = open(data->file1, O_RDONLY);
	if (file_desc == -1)
		ft_no_such_file(data, 1);
	if (dup2(file_desc, STDIN_FILENO) == -1)
	{
		ft_putendl_fd("pipex: dup2 error", 2);
		close(data->pipe_fds[PIPE_WRITE_END]);
		close(file_desc);
		free(data);
		exit(1);
	}
	if (dup2(data->pipe_fds[PIPE_WRITE_END], STDOUT_FILENO) == -1)
	{
		ft_putendl_fd("pipex: dup2 error", 2);
		close(data->pipe_fds[PIPE_WRITE_END]);
		close(file_desc);
		free(data);
		exit(1);
	}
	close(data->pipe_fds[PIPE_WRITE_END]);
	close(file_desc);
}

void	exec_first_command(t_data *data)
{
	char	**command;
	char	*path;

	check_empty_file_arg(data, 1);
	init_fds_cmd1(data);
	check_empty_cmd_arg(data, 1);
	command = ft_split(data->cmd1, ' ');
	if (command == NULL)
		ft_free_struct_and_exit("pipex: malloc error", data, 1);
	path = find_correct_path(&command, data);
	if (path == NULL)
		ft_cmd_not_found(data, command);
	while (path != NULL)
	{
		execve(path, command, data->env);
		free(path);
		path = find_correct_path(&command, data);
	}
	ft_exec_format_error(data, command);
}
