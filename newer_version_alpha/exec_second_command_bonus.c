/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_second_command_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:56:34 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/08 16:54:57 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	init_fds_cmd2(t_data *data)
{
	int	file2_fd;

	close(data->pipe_fds[PIPE_WRITE_END]);
	file2_fd = open(data->file2, O_CREAT | O_APPEND | O_WRONLY, 0666);
	if (file2_fd == -1)
		ft_no_such_file(data, 1);
	if (dup2(data->pipe_fds[PIPE_READ_END], STDIN_FILENO) == -1)
	{
		ft_putendl_fd("pipex: dup2 error", 2);
		close(data->pipe_fds[PIPE_READ_END]);
		close(file2_fd);
		free(data);
		exit(1);
	}
	if (dup2(file2_fd, STDOUT_FILENO) == -1)
	{
		ft_putendl_fd("pipex: dup2 error", 2);
		close(data->pipe_fds[PIPE_READ_END]);
		close(file2_fd);
		free(data);
		exit(1);
	}
	close(data->pipe_fds[PIPE_READ_END]);
	close(file2_fd);
}

void	exec_second_command(t_data *data)
{
	char	**command;
	char	*path;
	//int		child_status;

	check_empty_file_arg(data, 2);
	init_fds_cmd2(data);
	check_empty_cmd_arg(data, 2);
	command = ft_split(data->cmd2, ' ');
	if (command == NULL)
		ft_free_struct_and_exit("pipex: malloc error", data, 1);
	path = find_correct_path_cmd2(&command, data);
	if (path == NULL)
		ft_cmd_not_found(data, command);
	//if (waitpid(data->children[0], &child_status, 0) == -1)
	//{
	//	ft_putendl_fd("Wait error!", 2);
	//}
	while (path != NULL)
	{
		execve(path, command, data->env);
		free(path);
		path = find_correct_path_cmd2(&command, data);
	}
	ft_exec_format_error(data, command);
}
