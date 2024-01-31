/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_second_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:09:51 by skorbai           #+#    #+#             */
/*   Updated: 2024/01/31 15:57:30 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_second_command(char *cmd2, char *file2, char ***env, int *fd)
{
	int		file2_fd;
	char	**command;
	char	*path;

	close(fd[PIPE_WRITE_END]);
	file2_fd = open(file2, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (file2_fd == -1)
		ft_message_and_exit("Error: could not open output file");
	dup2(fd[PIPE_READ_END], STDIN_FILENO);
	dup2(file2_fd, STDOUT_FILENO);
	close(fd[PIPE_READ_END]);
	close(file2_fd);
	command = ft_split(cmd2, ' ');
	if (command == NULL)
		ft_message_and_exit("Malloc fail");
	path = find_correct_path_cmd2(&command, env);
	while (path != NULL)
	{
		execve(path, command, *env);
		free(path);
		path = find_correct_path_cmd2(&command, env);
	}
	ft_free_and_exit("Failed to execute cmd 2", command);
}
