/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:30:24 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/05 16:00:52 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_cmd_not_found(t_data *data, char	**arr, int cmd_nro)
{
	free_2d_array(arr);
	ft_putstr_fd("pipex: command not found: ", 2);
	if (cmd_nro == 1)
		ft_putendl_fd(data->cmd1, 2);
	else
		ft_putendl_fd(data->cmd2, 2);
	free(data);
	exit(127);
}
