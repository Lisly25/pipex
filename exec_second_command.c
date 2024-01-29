/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_second_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:09:51 by skorbai           #+#    #+#             */
/*   Updated: 2024/01/29 12:20:08 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_second_command(char *cmd2, char *file2, char **env, int **fd)
{
	int	file2_fd;

	ft_printf("Executing second child (oh no)\n");
	file2_fd = open(file2, O_CREAT, O_WRONLY);
	dup2(*fd[0], STDIN_FILENO);//not okay, I need my filesystem to be: file1 -> pipe_in -> pipe_out -> file-2. Or is it okay?
	dup2(STDOUT_FILENO, file2_fd);
	close(*fd[0]);
	close(*fd[1]);
	//now we can try to execute the command
	exit(0);
}
