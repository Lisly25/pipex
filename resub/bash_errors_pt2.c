/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_errors_pt2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:07:49 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/07 16:12:10 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_if_dir_error(t_data *data, char *path, char **arr)
{
	int	fd;

	fd = open(path, O_DIRECTORY);
	if (fd >= 0)
	{
		ft_putstr_fd("pipex: permission denied: ", 2);
		ft_putendl_fd(arr[0], 2);
		close(fd);
		free(path);
		free(data);
		free_2d_array(arr);
		exit(126);
	}
}

void	ft_no_such_file_as_cmd(t_data *data, char **arr)
{
	ft_putstr_fd("pipex: no such file or directory: ", 2);
	ft_putendl_fd(arr[0], 2);
	free_2d_array(arr);
	free(data);
	exit(127);
}
