/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 00:01:18 by jebrocho          #+#    #+#             */
/*   Updated: 2020/02/11 00:01:40 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

int 	check_raw(char c, int res)
{
	static int mod;
	static int mod_q;
	static int mod_dq;

	if (res == 0)
	{
		if (c == '"' && mod_q == 0)
		{
			mod++;
			if (mod % 2 == 0)
				mod_dq = 0;
			else
				mod_dq = 1;
		}
		if (c == '\'' && mod_dq == 0)
		{
			mod++;
			if (mod % 2 == 0)
				mod_q = 0;
			else
				mod_q = 1;
		}
	}
	else
		mod = 0;
	return (mod);
}

char 	*add_arg(t_var *data, int pos_m, int pos_l)
{
	char 	*arg;
	int 	i;

	i = 0;
	if (!(arg = (char *)malloc(sizeof(char) * (pos_l - pos_m) + 1)))
		return (NULL);
	while (pos_m < pos_l)
	{
		arg[i] = data->raw_cmd[pos_m];
		i++;
		pos_m++;
	}
	arg[i] = '\0';
	return (arg);
}

void 	parse_built(t_var *data, char **arg_env)
{
	int 	i;
	int 	index;
	int 	mod;
	int 	j;

	i = -1;
	j = 0;
	index = 0;
	while (data->raw_cmd[++i])
	{
		mod = check_raw(data->raw_cmd[i], 0);
		if (is_whitespaces(data->raw_cmd[i]) && (mod % 2 == 0))
		{
			arg_env[index] = add_arg(data, j, i);
			j = i;
			index++;
		}
		if (data->raw_cmd[i + 1] == '\0')
		{
			arg_env[index] = add_arg(data, j, i + 1);
			j = i;
			index++;
		}
	}
	arg_env[index] = NULL;
	check_raw('c', 1);
}

void 	rm_quotes_n_spaces(char **arg_env)
{
	int i;
	int j;
	int k;

	k = -1;
	i = -1;
	j = -1;
	while (arg_env[++i])
	{
		while (is_whitespaces(arg_env[i][++j]))
		{
			k = j - 1;
			while (arg_env[i][++k])
				arg_env[i][k] = arg_env[i][k + 1];
			arg_env[i][k] = '\0';
		}
		j = -1;
	}
	j = 0;
	i = -1;
	while (arg_env[++i])
	{
		while (arg_env[i][j] != '"' && arg_env[i][j] != '\'' && arg_env[i][j])
			j++;
		rm_char(arg_env[i], arg_env[i][j]);
		j = 0;
	}
}

int 	count_arg(t_var *data)
{
	int i;
	int index;
	int mod;

	i = -1;
	index = 0;
	while (data->raw_cmd[++i])
	{
		mod = check_raw(data->raw_cmd[i], 0);
		if (is_whitespaces(data->raw_cmd[i]) && (mod % 2 == 0))
			index++;
	}
	check_raw('c', 1);
	return (index);
}
