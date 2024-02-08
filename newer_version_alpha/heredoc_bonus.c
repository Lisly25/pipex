/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:05:59 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/08 14:46:34 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	init_fds_cmd1(t_data *data)
{
	close(data->pipe_fds[PIPE_READ_END]);
	if (dup2(data->pipe_fds[PIPE_WRITE_END], STDOUT_FILENO) == -1)
	{
		ft_putendl_fd("pipex: dup2 error", 2);
		close(data->pipe_fds[PIPE_WRITE_END]);
		free(data);
		exit(1);
	}
	close(data->pipe_fds[PIPE_WRITE_END]);
}

static void	write_hdoc_to_temp(t_data *data, t_vector *hdoc)
{
	int	temp_fd;
	int	i;

	temp_fd = open("pipex_temp", O_CREAT | O_RDWR, 0666);
	while (hdoc->text[i] != NULL)
	{
		ft_putstr_fd(hdoc->text[i], temp_fd);
		i++;
	}
	free_vector(hdoc);
	if (dup2(temp_fd, STDIN_FILENO) == -1)
	{
		ft_putendl_fd("pipex: dup2 error", 2);
		close(temp_fd);
		free(data);
		exit(1);
	}
	close(temp_fd);
}

static void	exec_hdoc(t_data *data)
{
	char	**command;
	char	*path;

	init_fds_cmd1(data);
	check_empty_cmd_arg(data, 1);
	command = ft_split(data->cmd1, ' ');
	if (command == NULL)
		ft_free_struct_and_exit("pipex: malloc error", data, 1);
	path = find_correct_path(&command, data);
	if (path == NULL)
		ft_cmd_not_found(data, command);
	while (path != NULL)
	{
		execve(path, command, data->env);
		free(path);
		path = find_correct_path(&command, data);
	}
	ft_exec_format_error(data, command);
}

static void	exec_first_command_heredoc(t_data *data)
{
	int			i;
	char		*str;
	t_vector	*hdoc;

	hdoc = vector_new(1);
	if (hdoc == NULL)
		ft_free_struct_and_exit("pipex: malloc error", data, 1);
	i = -1;
	while (i == 0)
	{
		str = get_next_line(STDIN_FILENO);
		if (str == NULL)
		{
			free_vector(hdoc);
			ft_free_struct_and_exit("pipex: malloc error", data, 1);
		}
		if ((ft_strlen(str) == 1) && (ft_strncmp(data->delimiter, str, 1) == 0))
			break ;
		if (vector_add_back(hdoc, str) == 1)
			ft_free_struct_and_exit("pipex: malloc error", data, 1);
		free(str);
	}
	write_hdoc_to_temp(data, hdoc);
	exec_hdoc(data);
}

/*
the goal is to get input like:

here_doc LIMITER cmd cmd1 file

in which case we'll keep taking input from the stdin until we find LIMITER, then we execute cmd on it

the output of cmd is sent through the pipe, taken as input by cmd1: and then it is APPENDED to file if it already exists! (O_APPEND)

the 2nd command will only actually be executed after the whole output upto a delimiter has been read

it seems that what's read from the command line as heredoc is first written into a temp file, then that is set as the input file for execve

*/

void	exec_first_command(t_data *data)
{
	char	**command;
	char	*path;
	size_t	file1_len;

	check_empty_file_arg(data, 1);
	file1_len = ft_strlen(data->file1);
	if (ft_strncmp(data->file1, "here_doc", file1_len) == 0) //should move it to main later, and before we call the function, should create the temp file, so we can unlink it - or is the name enough for unlinking?
		exec_first_command_heredoc(data);
	init_fds_cmd1(data);
	check_empty_cmd_arg(data, 1);
	command = ft_split(data->cmd1, ' ');
	if (command == NULL)
		ft_free_struct_and_exit("pipex: malloc error", data, 1);
	path = find_correct_path(&command, data);
	if (path == NULL)
		ft_cmd_not_found(data, command);
	while (path != NULL)
	{
		execve(path, command, data->env);
		free(path);
		path = find_correct_path(&command, data);
	}
	ft_exec_format_error(data, command);
}
