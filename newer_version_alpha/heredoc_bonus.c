/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:05:59 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/09 12:12:42 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	write_hdoc_to_temp(t_data *data, t_vector *hdoc)
{
	int		temp_fd;
	size_t	i;

	i = 0;
	temp_fd = open("here_doc", O_CREAT | O_WRONLY, 0644);
	if (temp_fd == -1)
	{
		free_vector(hdoc);
		ft_putstr_fd("pipex: no such file or directory: here_doc", 2);
		free(data);
		exit(127);
	}
	while (i < hdoc->used_nodes)
	{
		ft_putstr_fd(hdoc->text[i], temp_fd);
		i++;
	}
	free_vector(hdoc);
	close(temp_fd);
}

void	create_temp(t_data *data)
{
	int			i;
	char		*str;
	t_vector	*hdoc;

	hdoc = vector_new(1);
	if (hdoc == NULL)
		ft_free_struct_and_exit("pipex: malloc error", data, 1);
	i = 0;
	while (i == 0)
	{
		ft_putstr_fd("pipex heredoc> ", 1);
		str = get_next_line(STDIN_FILENO);
		if (str == NULL)
		{
			free_vector(hdoc);
			ft_free_struct_and_exit("pipex: malloc error", data, 1);
		}
		if ((ft_strlen(str) == 2) && (str[0] == data->delimiter[0]))
			break ;
		if (vector_add_back(hdoc, str) == 1)
			ft_free_struct_and_exit("pipex: malloc error", data, 1);
	}
	write_hdoc_to_temp(data, hdoc);
}

void	check_if_heredoc(t_data *data)
{
	size_t	file1_len;

	file1_len = ft_strlen(data->file1);
	if (ft_strncmp(data->file1, "here_doc", file1_len) == 0)
		create_temp(data);
}
