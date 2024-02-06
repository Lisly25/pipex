/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:43:37 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/06 14:56:14 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_message_and_exit(char *str, int exit_status)
{
	ft_putendl_fd(str, 2);
	exit (exit_status);
}

void	ft_free_struct_and_exit(char *str, t_data *data, int exit_status)
{
	free(data);
	ft_putendl_fd(str, 2);
	exit (exit_status);
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

void	ft_free_and_exit(char *str, char **arr, t_data *data, int e_stat)
{
	free_2d_array(arr);
	free(data);
	ft_putendl_fd(str, 2);
	exit(e_stat);
}

void	ft_free_2d_arrs_and_exit(char *str, char **arr1, char **arr2)
{
	free_2d_array(arr1);
	free_2d_array(arr2);
	ft_putendl_fd(str, 2);
	exit(1);
}
