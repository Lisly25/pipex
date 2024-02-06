/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:55:40 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/06 15:51:13 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	int		exit_status;

	if (argc != 5)
		ft_message_and_exit("Format needed: ./pipex file1 cmd1 cmd2 file2", 1);
	data = init_data_struct(argv, env);
	init_pipe(data);
	init_child(data, 1);
	if (data->children[0] == 0)
		exec_first_command(data);
	close(data->pipe_fds[PIPE_WRITE_END]);
	if (data->children[0] > 0)
	{
		init_child(data, 2);
		if (data->children[1] == 0)
			exec_second_command(data);
	}
	close(data->pipe_fds[PIPE_READ_END]);
	close(data->pipe_fds[PIPE_WRITE_END]);
	if (data->children[0] > 0)
		wait_for_children(data);
	exit_status = data->exit_status;
	free(data);
	exit(exit_status);
}
