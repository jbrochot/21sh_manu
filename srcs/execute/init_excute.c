/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_excute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 13:55:06 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/05 15:05:41 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void 	form_cmd_raw(t_var *data, char **cmd)
{
	int i;

	i = 0;
	data->raw_cmd = ft_strdup(cmd[i]);
	while (cmd[++i])
	{
		data->raw_cmd = ft_strjoin_free(data->raw_cmd, " ", 0);
		data->raw_cmd = ft_strjoin_free(data->raw_cmd, cmd[i], 0);
	}
}

int		is_builtin(t_var *data, char **cmd)
{
	if (!ft_strcmp(cmd[0], "exit"))
		exit_shell(data);
	else if (!ft_strcmp(cmd[0], "cd"))
	{
		cd_builtin(data, cmd);
		free_tab(cmd);
		return (1);
	}
	else if (!ft_strcmp(cmd[0], "env"))
	{
		form_cmd_raw(data, cmd);
		return (env_builtin(data));
	}
	else if (!ft_strcmp(cmd[0], "echo"))
	{
		form_cmd_raw(data, cmd);
		return (echo_builtin(data));
	}
	else if (!ft_strcmp(cmd[0], "setenv"))
		return (setenv_builtin(data, cmd));
	else if (!ft_strcmp(cmd[0], "unsetenv"))
		return (unsetenv_builtin(data, cmd));
	return (0);
}

int		check_exe(t_var *data, char *cmd)
{
	int		i;
	char	**split_cmd;

	i = 0;
	split_cmd = ft_split(cmd, ' ');
	while (split_cmd[i])
	{
		if (split_cmd[i][0] == '$')
			split_cmd[i] = get_dollar_var(split_cmd[i], data);
		i++;
	}
	if (is_builtin(data, split_cmd))
		return (1);
	free_tab(split_cmd);
	return (0);
}

void	init_exec(t_var *data)
{
	char	*path;
	char	**bin_path;

	path = get_var("PATH=", data->environ);
	bin_path = path ? ft_split(path, ':') : NULL;
	if (data->cmd_index == 0)
		ft_putchar_fd('\n', 0);
	if (!check_exe(data, data->cmds[data->cmd_index]))
		exec_cmd(bin_path, data);
	if (bin_path)
		free_tab(bin_path);
}
