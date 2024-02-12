/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:48:17 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/12 10:14:13 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_data	*init_data_struct(char **argv, char **env)
{
	t_data	*data;
	size_t	file1_len;

	data = (t_data *)malloc(sizeof(t_data));
	data->env = env;
	data->exit_status_1 = 0;
	data->exit_status_2 = 0;
	data->file1 = argv[1];
	file1_len = ft_strlen(data->file1);
	if (ft_strncmp(data->file1, "here_doc", file1_len) == 0)
	{
		data->file2 = argv[5];
		data->cmd1 = argv[3];
		data->cmd2 = argv[4];
		data->delimiter = argv[2];
	}
	else
	{
		data->file2 = argv[4];
		data->cmd1 = argv[2];
		data->cmd2 = argv[3];
	}
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
