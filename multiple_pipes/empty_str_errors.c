/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_str_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:36:33 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/08 12:00:27 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_empty_file_arg(t_data *data, int child)
{
	char	*file;

	if (child == 1)
		file = data->file1;
	else
		file = data->file2;
	if (ft_strlen(file) == 0)
	{
		ft_putendl_fd("pipex: no such file or directory: ", 2);
		free(data);
		exit(1);
	}
}

void	check_empty_cmd_arg(t_data *data, int child)
{
	char	*cmd;

	if (child == 1)
		cmd = data->cmd1;
	else
		cmd = data->cmd2;
	if (ft_strlen(cmd) == 0)
	{
		ft_putendl_fd("pipex: permission denied: ", 2);
		free(data);
		exit(126);
	}
}
