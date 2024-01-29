/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_first_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:06:20 by skorbai           #+#    #+#             */
/*   Updated: 2024/01/29 16:43:50 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_first_command(char *file1, char *cmd1, char **env, int *fd)
{
	int		file1_fd;
	char	**command;
	char	*path;

	ft_printf("Executing first child (oh no)\n");
	file1_fd = open(file1, O_RDONLY);
	dup2(STDIN_FILENO, file1_fd);
	dup2(fd[PIPE_WRITE_END], STDOUT_FILENO);
	close(fd[PIPE_READ_END]);
	close(fd[PIPE_WRITE_END]);
	close(file1_fd);
	command = ft_split(cmd1, ' ');
	if (command == NULL)
		ft_message_and_exit("Malloc fail");
	path = find_correct_path(command, env);
	if (path == NULL)
		ft_free_and_exit("Error: no valid path for execution", command);
	if (execve(path, command, env) == -1)
	{
		free_2d_array(command);
		free(path);
		ft_message_and_exit("Failed to execute command1");
	}
	exit(0);
}
