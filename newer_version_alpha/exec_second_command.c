/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_second_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:09:51 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/07 12:14:39 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_second_command(t_data *data)
{
	int		file2_fd;
	char	**command;
	char	*path;

	close(data->pipe_fds[PIPE_WRITE_END]);
	file2_fd = open(data->file2, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (file2_fd == -1)
		ft_no_such_file(data, 1);
	dup2(data->pipe_fds[PIPE_READ_END], STDIN_FILENO);
	dup2(file2_fd, STDOUT_FILENO);
	close(data->pipe_fds[PIPE_READ_END]);
	close(file2_fd);
	command = ft_split(data->cmd2, ' ');
	if (command == NULL)
		ft_free_struct_and_exit("pipex: malloc error", data, 1);
	path = find_correct_path_cmd2(&command, data);
	if (path == NULL)
		ft_cmd_not_found(data, command, 2);
	while (path != NULL)
	{
		execve(path, command, data->env);
		free(path);
		path = find_correct_path_cmd2(&command, data);
	}
	ft_exec_format_error(data, command, 2);
}
