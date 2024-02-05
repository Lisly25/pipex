/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:40:44 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/05 15:23:35 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_for_children(t_data *data)
{
	int		child_1_status;
	int		child_2_status;

	if (waitpid(data->children[0], &child_1_status, 0) == -1)
	{
		free(data);
		ft_message_and_exit("Error : Wait error (command 1)", 1);
	}
	if (WIFEXITED(child_1_status) == 1)
		data->exit_status = WEXITSTATUS(child_1_status);
	if (data->children[1] > 0)
	{
		if (waitpid(data->children[1], &child_2_status, 0) == -1)
		{
			free(data);
			ft_message_and_exit("Error : Wait error (command 2)", 1);
		}
	}
	if (WIFEXITED(child_2_status) == 1)
		data->exit_status = WEXITSTATUS(child_2_status);
}
