/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_first_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:06:20 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/05 11:00:53 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_first_command(char *file1, char *cmd1, char ***env, int *fd)
{
	int		file1_fd;
	char	**command;
	char	*path;

	close(fd[PIPE_READ_END]);
	file1_fd = open(file1, O_RDONLY);
	if (file1_fd == -1)
		ft_message_and_exit("No such file or directory", 1);
	dup2(file1_fd, STDIN_FILENO);
	dup2(fd[PIPE_WRITE_END], STDOUT_FILENO);
	close(fd[PIPE_WRITE_END]);
	close(file1_fd);
	command = ft_split(cmd1, ' ');
	if (command == NULL)
		ft_message_and_exit("Error: Malloc fail", 1);
	path = find_correct_path(&command, env);
	while (path != NULL)
	{
		execve(path, command, *env);
		free(path);
		path = find_correct_path(&command, env);
	}
	ft_free_and_exit("Failed to execute command1", command);
}
