/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:55:40 by skorbai           #+#    #+#             */
/*   Updated: 2024/01/31 16:05:05 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	pid_t	child_1;
	pid_t	child_2;
	int		fd[2];
	char	**cpy_env;

	cpy_env = dup_2d_arr(env);
	if (argc != 5)
		ft_message_and_exit("Required format: ./pipex file1 cmd1 cmd2 file2");
	if (pipe(fd) == -1)
		ft_message_and_exit("Error: could not create pipe");
	child_1 = init_child();
	if (child_1 == 0)
		exec_first_command(argv[1], argv[2], &cpy_env, fd);
	close(fd[PIPE_WRITE_END]);
	if (child_1 > 0)
	{
		child_2 = init_child();
		if (child_2 == 0)
			exec_second_command(argv[3], argv[4], &cpy_env, fd);
	}
	ft_close_fds(fd);
	if (child_1 > 0)
		wait_for_children(child_1, child_2);
	exit(0);
}
