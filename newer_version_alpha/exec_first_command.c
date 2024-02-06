/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_first_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:06:20 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/06 15:47:15 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_first_command(t_data *data)
{
	int		file1_fd;
	char	**command;
	char	*path;

	close(data->pipe_fds[PIPE_READ_END]);
	file1_fd = open(data->file1, O_RDONLY);
	if (file1_fd == -1)
		ft_no_such_file(data, 1);
	dup2(file1_fd, STDIN_FILENO);
	dup2(data->pipe_fds[PIPE_WRITE_END], STDOUT_FILENO);
	close(data->pipe_fds[PIPE_WRITE_END]);
	close(file1_fd);
	command = ft_split(data->cmd1, ' ');
	if (command == NULL)
		ft_free_struct_and_exit("pipex: malloc error", data, 1);
	path = find_correct_path(&command, data);
	if (path == NULL)
		ft_cmd_not_found(data, command, 1);
	while (path != NULL)
	{
		execve(path, command, data->env);
		free(path);
		path = find_correct_path(&command, data);
	}
	ft_free_and_exit("pipex: execution failed", command, data, 1);
}
