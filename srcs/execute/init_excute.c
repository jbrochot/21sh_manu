/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_excute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 13:55:06 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/12 11:01:44 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void 	form_cmd_raw(t_var *data, char **cmd, int *i)
{
	int j;
	int k;

	j = 0;
	k = 0;
	free(data->raw_cmd);
	data->raw_cmd = ft_strdup(data->cmds[*i]);
	while (data->raw_cmd[j] == ' ')
		j++;
	while (data->raw_cmd[j])
	{
		data->raw_cmd[k] = data->raw_cmd[j];
		k++;
		j++;
	}
	data->raw_cmd[k] = '\0';
	reset_builtin(data, i);
}

void 	reset_builtin(t_var *data, int *i)
{
	*i = *i + 1;
	if (!data->cmds[*i])
		*i = 0;
}

char *form_name_raw(t_var *data)
{
	char *name;
	int i;

	i = 0;
	while (data->raw_cmd[i] != ' ' && data->raw_cmd[i])
		i++;
	if (!(name = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = -1;
	while (data->raw_cmd[++i] != ' ' && data->raw_cmd[i])
		name[i] = data->raw_cmd[i];
	name[i] = '\0';
	return (name);
}

int		is_builtin(t_var *data, char **cmd)
{
	static int i;
	int j;
	char *name;

	j = -1;
	form_cmd_raw(data, cmd, &i);
	name = form_name_raw(data);
	if (!ft_strcmp(name, "exit"))
		exit_shell(data);
	else if (!ft_strcmp(name, "cd"))
	{
		cd_builtin(data, cmd);
		free_tab(cmd);
		return (1);
	}
	else if (!ft_strcmp(name, "env"))
		return (env_builtin(data));
	else if (!ft_strcmp(name, "echo"))
		return (echo_builtin(data));
	else if (!ft_strcmp(name, "setenv"))
		return (setenv_builtin(data, cmd));
	else if (!ft_strcmp(name, "unsetenv"))
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
	{
		ft_strdel(&data->raw_cmd);
		return (1);
	}
	ft_strdel(&data->raw_cmd);
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
