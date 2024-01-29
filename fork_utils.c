/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:40:44 by skorbai           #+#    #+#             */
/*   Updated: 2024/01/29 16:49:55 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	init_child(void)
{
	pid_t	child;

	child = fork();
	if (child < 0)
		ft_message_and_exit("Error: fork() failed");
	return (child);
}

void	wait_for_children(pid_t child_1, pid_t child_2)
{
	int		child_1_status;
	int		child_2_status;

	if (waitpid(child_1, &child_1_status, 0) == -1)
		ft_message_and_exit("Error : Wait error (command 1)");
	if (child_2 > 0)
	{
		if (waitpid(child_2, &child_2_status, 0) == -1)
			ft_message_and_exit("Error : Wait error (command 2)");
	}
}
