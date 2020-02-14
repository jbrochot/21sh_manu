/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 10:42:07 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/12 11:01:32 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "core.h"

int		env_builtin(t_var *data);
int		setenv_builtin(t_var *data, char **cmd);
int		unsetenv_builtin(t_var *data, char **cmd);
char	*get_env(char **environ, char *selec);

int 	count_arg(t_var *data);
void 	rm_quotes_n_spaces(char **arg_env);
void 	parse_built(t_var *data, char **arg_env);

int		cd_builtin(t_var *data, char **cmd);
void	form_path(char *str, char c);
char	*error_cd(char *str, int mod);
char	*parse_error(char *s, t_var *data);
void	rm_error(char *s);
void	old_pwd(char *old, t_var *data);
void	new_env(t_var *data, char *newp);

int		echo_builtin(t_var *data);

void 	reset_builtin(t_var *data, int *i);

#endif
