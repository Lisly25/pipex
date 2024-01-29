/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:55:40 by skorbai           #+#    #+#             */
/*   Updated: 2024/01/29 11:30:22 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	pid_t	child_1;
	pid_t	child_2;
	int		child_1_status;
	int		child_2_status;
	int		fd[2];

	if (pipe(fd) == -1)
		ft_message_and_exit("Error: could not create pipe");
	if (argc != 5)
		ft_putendl_fd("Error: Format must be ./pipex file1 cmd1 cmd2 file2", 2);//later, change this to ft_message_and_exit!
	child_1 = fork();
	if (child_1 > 0)
		child_2 = fork();
	if (child_1 < 0 || child_2 < 0)
		ft_message_and_exit("Error: fork() failed");
	if (child_1 == 0)
		exec_first_command(argv[1], argv[2], env, &fd);
	else if (child_2 > 0 && waitpid(child_1, &child_1_status, 0) == -1)
		ft_putendl_fd("Error : Wait error (command 1)", 2);
	if (child_2 == 0)
		exec_second_command(argv[3], argv[4], env, &fd);
	if (waitpid(child_2, &child_2_status, 0) == -1)
		ft_putendl_fd("Error : Wait error (command 2)", 2);
	ft_close_fds(&fd);
	exit(0);
}
