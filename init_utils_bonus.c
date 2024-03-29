/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:48:17 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/16 11:26:46 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	check_arg_validity(char **argv, int argc)
{
	size_t	file1_len;

	if (argc != 5 && argc != 6)
		return (1);
	file1_len = ft_strlen(argv[1]);
	if (ft_strncmp(argv[1], "here_doc", file1_len) == 0 && file1_len != 0)
	{
		if (argc != 6)
		{
			ft_putstr_fd("Exited before this\n", 2);
			return (1);
		}
		else
			return (0);
	}
	else if (argc == 6)
		return (1);
	return (0);
}

t_data	*init_data_struct(char **argv, char **env)
{
	t_data	*data;
	size_t	file1_len;

	data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
		ft_message_and_exit("pipex: malloc error", 1);
	data->env = env;
	data->exit_status_1 = 0;
	data->exit_status_2 = 0;
	data->file1 = argv[1];
	file1_len = ft_strlen(data->file1);
	if (ft_strncmp(data->file1, "here_doc", file1_len) == 0 && file1_len != 0)
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

static void	close_pipe(t_data *data, int child_nro)
{
	close(data->pipe_fds[PIPE_READ_END]);
	if (child_nro == 1)
		close(data->pipe_fds[PIPE_WRITE_END]);
}

void	init_child(t_data *data, int nro)
{
	if (nro == 1)
	{
		data->children[0] = fork();
		if (data->children[0] < 0)
		{
			close_pipe(data, 1);
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
			close_pipe(data, 2);
			free(data);
			ft_putendl_fd("pipex: fork 2 failed", 2);
			exit(1);
		}
		return ;
	}
	return ;
}
