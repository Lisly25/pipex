/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:56:14 by skorbai           #+#    #+#             */
/*   Updated: 2024/01/31 11:58:52 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>

# define PIPE_READ_END 0
# define PIPE_WRITE_END 1

void	ft_message_and_exit(char *str);

void	ft_close_fds(int *fd);

void	free_2d_array(char **arr);

void	ft_free_and_exit(char *str, char **arr);

pid_t	init_child(void);

void	wait_for_children(pid_t child_1, pid_t child_2);

void	exec_first_command(char *file1, char *cmd1, char ***env, int *fd);

void	exec_second_command(char *cmd2, char *file2, char ***env, int *fd);

char	*find_correct_path(char **command, char ***env);

char	*find_correct_path_cmd2(char **command, char ***env);

void	deleteme_arr_print(char **arr);//DELETEME

char	**dup_2d_arr(char **arr);

#endif