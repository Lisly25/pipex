/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_errors_pt2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:07:49 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/07 13:53:45 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_if_dir_error(t_data *data, int cmd_nbr, char *path, char **arr)
{
	int	fd;

	fd = open(path, O_DIRECTORY);
	if (fd >= 0)
	{
		ft_putstr_fd("pipex: permission denied: ", 2);
		if (cmd_nbr == 1)
			ft_putendl_fd(data->cmd1, 2);
		else
			ft_putendl_fd(data->cmd2, 2);
		close(fd);
		free(path);
		free(data);
		free_2d_array(arr);
		exit(126);
	}
}
