/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:43:37 by skorbai           #+#    #+#             */
/*   Updated: 2024/01/29 16:44:14 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_message_and_exit(char *str)
{
	ft_putendl_fd(str, 2);
	exit (1);
}

void	ft_close_fds(int *fd)
{
	close(fd[PIPE_READ_END]);
	close(fd[PIPE_WRITE_END]);
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

void	ft_free_and_exit(char *str, char **arr)
{
	free_2d_array(arr);
	ft_putendl_fd(str, 2);
}
