/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 10:53:35 by ezonda            #+#    #+#             */
/*   Updated: 2019/09/11 10:56:54 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

int choose_env(t_var *data, char **arg_env, int* ind)
{
	int i;
	int selector;

	i = 0;
	selector = 0;
	while (arg_env[++i])
	{
		*ind = i;
		if (arg_env[i][0] != '-')
			selector = 1;
		if (arg_env[i][0] == '-' && arg_env[i][1] != 'i'
		 		&& arg_env[1][1] && selector == 0)
			return (102);
		if (!ft_strchr(arg_env[i], '=') && selector == 1)
			return (103);
		if (arg_env[i][0] == '=')
			return (104);
		if (arg_env[i][0] == '$')
			return (105);
	}
	if (ft_strcmp(arg_env[1], "-i") == 0)
	{
		*ind = 2;
		return (100);
	}
	else
	{
		*ind = 1;
		return (101);
	}
}

int 	error_env(t_var *data, int mod, char **arg_env, int ind)
{
	int i;
	int j;

	j = 0;
	i = 0;
	if (mod == 0)
		ft_printf("env: %s: No such file or directory\n", arg_env[ind]);
	if (mod == 1)
	{
		ft_printf("env: illegal option -- %c\n", arg_env[ind][1]);
		ft_printf("usage: env [-i]\n");
		ft_printf("           [name=value ...]\n");
	}
	if (mod == 2)
	{
		while (arg_env[ind][i + 1])
		{
			arg_env[ind][i] = arg_env[ind][i + 1];
			i++;
		}
		arg_env[ind][i] = '\0';
		ft_printf("21sh: %s not found\n", arg_env[ind]);
	}
	if (mod == 3)
	{
		while (arg_env[ind][i] != '=')
			i++;
		while (arg_env[ind][i])
		{
			arg_env[ind][j] = arg_env[ind][i];
			j++;
			i++;
		}
		arg_env[ind][j] = '\0';
		ft_printf("env: setenv %s: Invalid argument\n", arg_env[ind]);
	}
	ft_strdel(&data->raw_cmd);
	return (1);
}

void 	rm_exp(char **arg_env, int ind)
{
	int i;
	int j;

	while (arg_env[ind])
	{
		i = 0;
		while (arg_env[ind][i])
		{
			if (arg_env[ind][i] == '$')
			{
				j = i;
				while (arg_env[ind][i] != '=' && arg_env[ind][i])
					i++;
				while (arg_env[ind][i])
				{
					arg_env[ind][j] = arg_env[ind][i];
					j++;
					i++;
				}
				arg_env[ind][j] = '\0';
			}
			i++;
		}
		ind++;
	}
}

int		env_builtin(t_var *data)
{
	int i;
	int ind;
	char 	**p_environ;
	char	**arg_env;

	new_exp(data);
	i = count_arg(data) + 1;
	p_environ = ft_tabdup(data->environ, 0);
	if (!(arg_env = (char **)malloc(sizeof(char*) * i + 1)))
		return (1);
	parse_built(data, arg_env);
	rm_quotes_n_spaces(arg_env);
	i = choose_env(data, arg_env, &ind);
	if (i == 102)
		return (error_env(data, 1, arg_env, ind));
	if (i == 103)
		return (error_env(data, 0, arg_env, ind));
	if (i == 104)
		return (error_env(data, 2, arg_env, ind));
	if (i == 105)
		return (error_env(data, 3, arg_env, ind));
	rm_exp(arg_env, ind);
	if (i == 100)
		while(arg_env[ind])
			ft_printf("%s\n", arg_env[ind++]);
	if (i == 101)
	{
		while (arg_env[ind])
			p_environ = ft_tabjoinstr_free(p_environ, arg_env[ind++], 0);
		ind = -1;
		while (p_environ[++ind])
			ft_printf("%s\n", p_environ[ind]);
	}
	ft_strdel(&data->raw_cmd);
	return (1);
}
