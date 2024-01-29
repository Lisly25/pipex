/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:56:14 by skorbai           #+#    #+#             */
/*   Updated: 2024/01/29 12:03:16 by skorbai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>

void	ft_message_and_exit(char *str);

void	ft_close_fds(int **fd);

void	free_2d_array(char **arr);

void	exec_first_command(char *file1, char *cmd1, char **env, int **fd);

void	exec_second_command(char *cmd2, char *file2, char **env, int **fd);

char	*find_correct_path(char **command, char **env);

#endif