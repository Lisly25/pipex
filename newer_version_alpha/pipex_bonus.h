/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:06:35 by skorbai           #+#    #+#             */
/*   Updated: 2024/02/08 13:34:49 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft/libft.h"
# include "vector.h"
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

# define PIPE_READ_END 0
# define PIPE_WRITE_END 1

typedef struct s_data
{
	char	**env;
	pid_t	children[2];
	int		child_count;
	int		pipe_fds[2];
	char	*cmd1;
	char	*cmd2;
	char	*delimiter;
	char	*file1;
	char	*file2;
	int		exit_status_1;
	int		exit_status_2;
}	t_data;

t_data	*init_data_struct(char **argv, char **env);

void	init_pipe(t_data *data);

void	init_child(t_data *data, int nro);

void	ft_cmd_not_found(t_data *data, char	**arr);

void	ft_no_such_file(t_data *data, int cmd_nro);

void	ft_permission_denied_cmd(t_data *data, char **arr);

void	ft_exec_format_error(t_data *data, char **arr);

void	ft_no_such_file_as_cmd(t_data *data, char **arr);

void	check_empty_file_arg(t_data *data, int child);

void	check_empty_cmd_arg(t_data *data, int child);

void	check_if_dir_error(t_data *data, char *path, char **arr);

void	ft_message_and_exit(char *str, int exit_status);

void	free_2d_array(char **arr);

void	ft_free_and_exit(char *str, char **arr, t_data *data, int e_stat);

void	ft_free_2d_arrs_and_exit(char *str, char **arr1, char **arr2);

void	ft_free_struct_and_exit(char *str, t_data *data, int exit_status);

void	wait_for_children(t_data *data);

void	exec_first_command(t_data *data);

void	exec_second_command(t_data *data);

int		check_for_access(t_data *data, char *path, char ***arr);

char	*find_correct_path(char ***command, t_data *data);

char	*find_correct_path_cmd2(char ***command, t_data *data);

char	*path_strjoin(char ***paths, char ***commands, int i, t_data *data);

void	run_if_non_shell_command(char ***comm_ptr, t_data *data);

char	**find_paths(t_data *data, char ***command);

void	exec_abs_path(t_data *data, char ***command_ptr);

#endif