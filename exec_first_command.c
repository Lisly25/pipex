/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_first_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:06:20 by skorbai           #+#    #+#             */
/*   Updated: 2024/01/31 13:55:43 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_first_command(char *file1, char *cmd1, char ***env, int *fd)
{
	int		file1_fd;
	char	**command;
	char	*path;

	//ft_printf("In exec first command\n\n\n");
	//deleteme_arr_print(*env);
	close(fd[PIPE_READ_END]);
	file1_fd = open(file1, O_RDONLY);
	if (file1_fd == -1)
		ft_message_and_exit("Error: could not open input file");
	dup2(file1_fd, STDIN_FILENO);
	dup2(fd[PIPE_WRITE_END], STDOUT_FILENO);
	close(fd[PIPE_WRITE_END]);
	close(file1_fd);
	char *input = get_next_line(STDIN_FILENO);
	//ft_putstr_fd("we are here\n",2);
	ft_putstr_fd(input, 2);
	command = ft_split(cmd1, ' ');
	if (command == NULL)
		ft_message_and_exit("Malloc fail");
	path = find_correct_path(command, env);
	if (path == NULL)
		ft_free_and_exit("Error: no valid path for execution", command);
	ft_putstr_fd(path, 2);
	while (execve("/bin/cat", command, *env) == -1)
	{
		free(path);
		path = find_correct_path(command, env);
		ft_putstr_fd("\nNext path to check: ", 2);
		ft_putstr_fd(path, 2);
		if (path == NULL)
			break ;
	}
	free_2d_array(command);
	free(path);
	ft_message_and_exit("Failed to execute command1");
	exit(0);
}
