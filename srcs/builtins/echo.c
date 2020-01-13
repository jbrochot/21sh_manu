/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 13:28:56 by jebrocho          #+#    #+#             */
/*   Updated: 2019/08/06 15:41:14 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void	rm_echo(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		i++;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	while (str[i])
	{
		str[j] = str[i];
		i++;
		j++;
	}
	str[j] = '\0';
}

void	rm_cote(char *line)
{
	int i;
	int j;
	int k;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '"')
		{
			k = i;
			j = i + 1;
			while (line[j])
			{
				line[k] = line[j];
				k++;
				j++;
			}
			line[k] = '\0';
		}
	}
}

int		algo_quote(char *line, int i)
{
	int index;
	int new_id;

	while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
		i++;
	index = i + 1;
	new_id = index;
	while (line[i] && (line[new_id] == ' ' || line[new_id] == '\t'
				|| line[new_id] == '\n'))
		new_id++;
	while (line[new_id])
	{
		line[index] = line[new_id];
		index++;
		new_id++;
	}
	line[index] = '\0';
	return (i);
}

int 	take_quote(char *cmd, int index, int selec_q)
{
	int i;
	int j;

	j = index;
	i = index + 1;
	while (cmd[i])
	{
		cmd[j] = cmd[i];
		j++;
		i++;
	}
	cmd[j] = '\0';
	if (selec_q == 0)
		while (cmd[index] != '\'' && cmd[index])
			index++;
	if (selec_q == 1)
		while (cmd[index] != '\"' && cmd[index])
			index++;
	j = index;
	i = index + 1;
	while (cmd[i])
	{
		cmd[j] = cmd[i];
		j++;
		i++;
	}
	cmd[j] = '\0';
	return (index);
}

int 	echo_builtin(char *cmd)
{
	int i;
  int id_quote;
	int id_dquote;

	rm_echo(cmd);
	id_quote = 0;
	id_dquote = 0;
	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '\"' && id_quote % 2 == 0)
			id_dquote++;
		else if (cmd[i] == '\'' && id_dquote % 2 == 0)
			id_quote++;
		if (id_dquote % 2 == 0 && id_quote % 2 == 0)
			i = algo_quote(cmd, i);
		else if (id_quote % 2 != 0)
		{
			i = take_quote(cmd, i, 0);
			id_quote++;
		}
		else if (id_dquote % 2 != 0)
		{
			i = take_quote(cmd, i, 1);
			id_dquote++;
		}
	}
	ft_printf("%s\n", cmd);
	free(cmd);
	return (1);
}
