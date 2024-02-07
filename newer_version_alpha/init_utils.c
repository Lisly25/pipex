/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:15:06 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/07 11:15:00 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_data	*init_data_struct(char **argv, char **env)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	data->cmd1 = argv[2];
	data->cmd2 = argv[3];
	data->file1 = argv[1];
	data->file2 = argv[4];
	data->env = env;
	data->exit_status_1 = 0;
	data->exit_status_2 = 0;
	return (data);
}

void	init_pipe(t_data *data)
{
	if (pipe(data->pipe_fds) == -1)
	{
		free(data);
		ft_putendl_fd("pipex: pipe creation failed", 2);
		exit(1);
	}
}

void	init_child(t_data *data, int nro)
{
	if (nro == 1)
	{
		data->children[0] = fork();
		if (data->children[0] < 0)
		{
			free(data);
			ft_putendl_fd("pipex: fork 1 failed", 2);
			exit(1);
		}
		return ;
	}
	if (nro == 2)
	{
		data->children[1] = fork();
		if (data->children[1] < 0)
		{
			free(data);
			ft_putendl_fd("pipex: fork 2 failed", 2);
			exit(1);
		}
		return ;
	}
	return ;
}
