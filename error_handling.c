/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:43:37 by skorbai           #+#    #+#             */
/*   Updated: 2024/01/29 11:57:10 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_message_and_exit(char *str)
{
	ft_putendl_fd(str, 2);
	exit (1);
}

void	ft_close_fds(int **fd)
{
	close(*fd[0]);
	close(*fd[1]);
}

void	free_2d_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
