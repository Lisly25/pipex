/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:40:44 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/05 11:02:20 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	init_child(void)
{
	pid_t	child;

	child = fork();
	if (child < 0)
		ft_message_and_exit("Error: fork() failed", 1);
	return (child);
}

void	wait_for_children(pid_t child_1, pid_t child_2)
{
	int		child_1_status;
	int		child_2_status;

	if (waitpid(child_1, &child_1_status, 0) == -1)
		ft_message_and_exit("Error : Wait error (command 1)", 1);
	if (child_2 > 0)
	{
		if (waitpid(child_2, &child_2_status, 0) == -1)
			ft_message_and_exit("Error : Wait error (command 2)", 1);
	}
}

char	**dup_2d_arr(char **arr)
{
	char	**result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (arr[i] != NULL)
	{
		i++;
	}
	result = (char **)malloc(sizeof(char *) * (i + 1));
	while (arr[j] != NULL)
	{
		result[j] = ft_strdup(arr[j]);
		j++;
	}
	result[j] = NULL;
	return (result);
}
