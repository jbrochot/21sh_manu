/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 10:32:18 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/03 12:02:07 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"


int		check_flag_n(char **arg_echo)
{
	int i;

	i = 0;
	if (ft_strcmp(arg_echo[1], "-n") == 0)
	{
		while (arg_echo[i])
			i++;
		return (i);
	}
	return (0);
}

int		echo_builtin(t_var *data)
{
	int i;
	int flag_n;
	char **arg_echo;

	new_exp(data);
	i = count_arg(data) + 1;
	if (!(arg_echo = (char **)malloc(sizeof(char*) * i + 1)))
		return (1);
	parse_built(data, arg_echo);
	rm_quotes_n_spaces(arg_echo);
	i = 0;
	flag_n = check_flag_n(arg_echo);
	if (flag_n == 0)
		while (arg_echo[++i])
			ft_printf("%s\n", arg_echo[i]);
	if (flag_n != 0)
	{
		i = 1;
		while (++i < flag_n - 1)
			ft_printf("%s\n", arg_echo[i]);
		ft_printf("%s", arg_echo[i]);
		tputs(tgetstr("mr", NULL), 1, ft_putchar_v2);
		ft_putchar('%');
		tputs(tgetstr("me", NULL), 1, ft_putchar_v2);
		ft_putchar('\n');
	}
	return (1);
}
