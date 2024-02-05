/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:40:44 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/05 14:44:44 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*pid_t	init_child(void)
{
	pid_t	child;

	child = fork();
	if (child < 0)
		ft_message_and_exit("Error: fork() failed", 1);
	return (child);
}*/

void	wait_for_children(t_data *data)
{
	int		child_1_status;
	int		child_2_status;

	if (waitpid(data->children[0], &child_1_status, 0) == -1)
	{
		free(data);
		ft_message_and_exit("Error : Wait error (command 1)", 1);
	}
	if (data->children[1] > 0)
	{
		if (waitpid(data->children[1], &child_2_status, 0) == -1)
		{
			free(data);
			ft_message_and_exit("Error : Wait error (command 2)", 1);
		}
	}
}

/*char	**dup_2d_arr(char **arr)
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
}*/
