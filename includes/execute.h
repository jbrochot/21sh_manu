/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 12:57:21 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/04 10:08:42 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "core.h"

char	*init_path(char *str, char *cmd);
void	error_msg(char **bin_path, char *path);
int		free_tab(char **tab);
char	*get_var(char *str, char **env);
char	*get_dollar_var(char *cmd, t_var *data);
void	exec_cmd(char **bin_path, t_var *data);
void	init_exec(t_var *data);

void	get_cmd_type(t_cmd *cmd, t_var *data);
void	execute_redir(t_cmd *cmd, t_var *data);

void	cmd_basic(t_cmd *cmd, t_var *data);
void	cmd_redir(t_cmd *cmd, t_var *data);

int		init_heredoc(t_var *data, t_redirection_cmd *rcmd);
int		is_aggreg(char *file);
int		is_cat_heredoc(t_var *data);

void	add_to_files(t_var *data, char *str);

#endif
