/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_first_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:06:20 by skorbai           #+#    #+#             */
/*   Updated: 2024/01/29 12:15:16 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_first_command(char *file1, char *cmd1, char **env, int **fd)
{
	int		file1_fd;
	char	**command;
	char	*path;

	ft_printf("Executing first child (oh no)\n");
	file1_fd = open(file1, O_RDONLY);
	dup2(STDIN_FILENO, file1_fd);
	dup2(*fd[1], STDOUT_FILENO);
	close(*fd[0]);
	close(*fd[1]);
	//command = ft_split(cmd1, " ");//Should not malloc, since I won't be able to fre after - but how else can I make it NULL-terminated? Do I even need to?
	path = find_correct_path(command, env);
	execve(path, cmd1, env);
	//free_2d_array(command);
	exit(0);
}
