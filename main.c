/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:55:40 by skorbai           #+#    #+#             */
/*   Updated: 2024/01/31 12:03:39 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	deleteme_arr_print(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		ft_putstr_fd(arr[i], 2);
		ft_putchar_fd('\n', 2);
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	pid_t	child_1;
	pid_t	child_2;
	int		fd[2];
	char	**cpy_env;
	//int		child_1_status;
	//int		child_2_status;

	cpy_env = dup_2d_arr(env);
	if (argc != 5)
		ft_putendl_fd("Error: Format must be ./pipex file1 cmd1 cmd2 file2", 2);//later, change this to ft_message_and_exit!
	if (pipe(fd) == -1)
		ft_message_and_exit("Error: could not create pipe");
	child_1 = init_child();
	if (child_1 == 0)
		exec_first_command(argv[1], argv[2], &cpy_env, fd);
	close(fd[PIPE_WRITE_END]);
	//if (waitpid(child_1, &child_1_status, 0) == -1)
	//	ft_message_and_exit("Error : Wait error (command 1)");
	if (child_1 > 0)
	{
		child_2 = init_child();
		if (child_2 == 0)
			exec_second_command(argv[3], argv[4], &cpy_env, fd);
	}
	//if (waitpid(child_2, &child_2_status, 0) == -1)
	//	ft_message_and_exit("Error : Wait error (command 2)");
	ft_close_fds(fd);
	if (child_1 > 0)
		wait_for_children(child_1, child_2);
	exit(0);
}
