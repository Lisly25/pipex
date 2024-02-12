/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:39:34 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/12 10:42:19 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	int		exit_status;

	if (argc < 5)
		ft_message_and_exit("pipex: error: invalid format", 1);
	data = init_data_struct(argv, env);
	check_if_heredoc(data);
	init_pipe(data);
	init_child(data, 1);
	if (data->children[0] == 0)
		exec_first_command(data);
	close(data->pipe_fds[PIPE_WRITE_END]);
	init_child(data, 2);
	if (data->children[1] == 0)
		exec_second_command(data);
	close(data->pipe_fds[PIPE_READ_END]);
	close(data->pipe_fds[PIPE_WRITE_END]);
	wait_for_children(data);
	exit_status = data->exit_status_2;
	free(data);
	unlink("here_doc");
	exit(exit_status);
}
