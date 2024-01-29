/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_second_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:09:51 by skorbai           #+#    #+#             */
/*   Updated: 2024/01/29 16:43:45 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_second_command(char *cmd2, char *file2, char **env, int *fd)
{
	int		file2_fd;
	char	**command;
	char	*path;

	ft_printf("Executing second child (oh no)\n");
	file2_fd = open(file2, O_CREAT, O_WRONLY);
	dup2(fd[PIPE_READ_END], STDIN_FILENO);//not okay, I need my filesystem to be: file1 -> pipe_in -> pipe_out -> file-2. Or is it okay?
	dup2(STDOUT_FILENO, file2_fd);
	close(fd[PIPE_READ_END]);
	close(fd[PIPE_WRITE_END]);
	close(file2_fd);
	command = ft_split(cmd2, ' ');
	if (command == NULL)
		ft_message_and_exit("Malloc fail");
	path = find_correct_path(command, env);
	if (path == NULL)
		ft_free_and_exit("Error: no valid path for execution", command);
	if (execve(path, command, env) == -1)
	{
		free_2d_array(command);
		free(path);
		ft_message_and_exit("Failed to execute command2");
	}
	exit(0);
}
