/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_second_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:09:51 by skorbai           #+#    #+#             */
/*   Updated: 2024/01/31 14:03:33 by skorbai          ###   ########.fr       */
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
	char *input = get_next_line(STDIN_FILENO);
	ft_putstr_fd("\nWithin exec 2nd command what we receive through he pipe is: ", 2);
	ft_putstr_fd(input, 2);
	command = ft_split(cmd2, ' ');
	if (command == NULL)
		ft_message_and_exit("Malloc fail");
	path = find_correct_path_cmd2(command, env);
	if (path == NULL)
		ft_free_and_exit("Error: no valid path for execution", command);
	while (execve("/usr/bin/grep", command, *env) == -1)
	{
		free(path);
		path = find_correct_path_cmd2(command, env);
		//ft_printf("Path we'll try next for 2nd command is %s, command itself is\n", path);
		//deleteme_arr_print(command);
		if (path == NULL)
			break ;
	}
	free_2d_array(command);
	free(path);
	ft_message_and_exit("Failed to execute command2");
	exit(0);
}
