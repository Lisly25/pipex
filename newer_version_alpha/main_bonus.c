/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:39:34 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/08 16:54:08 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	int		exit_status;

	if (argc != 6)//this is just for heredoc
		ft_message_and_exit("Format needed: ./pipex here_doc DELIMITER cmd1 cmd2 file2", 1);
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
	exit_status = data->exit_status_2;
	free(data);
	unlink("pipex_temp");
	exit(exit_status);
}
