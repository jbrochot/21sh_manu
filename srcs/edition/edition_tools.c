/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edition_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 10:44:48 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/07 09:45:38 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

int		ft_putchar_v2(int c)
{
	write(1, &c, 1);
	return (c);
}

void	init_var(t_var *data)
{
	data->pos = 0;
	data->cat_here = 0;
	data->char_count = 0;
	data->in_selection = 0;
	data->new_history = 0;
	data->left = 0;
	data->right = 0;
	data->quotes = 0;
	data->dquotes = 0;
	data->std_prompt = 1;
	data->mod_quotes = 0;
	data->p_prompt = 0;
	data->h_prompt = 0;
	data->n_prompt = 0;
	data->c_prompt = 0;
	data->q_prompt = 0;
	data->dq_prompt = 0;
	data->redir_count = 0;
	data->cmd_index = 0;
	data->hist_pos = 0;
	data->pipe = 0;
}

void	init_shell(t_var *data)
{
	int i;

	i = 0;
	init_var(data);
	if (!(data->history = (char**)malloc(sizeof(char*) * BUFF_SHELL)))
		return ;
	ft_memset(data->history, 0, sizeof(char*) * BUFF_SHELL);
	if (!(data->selection = (char*)malloc(sizeof(char) * BUFF_SHELL)))
		return ;
	if (!(data->tab = malloc(sizeof(int) * BUFF_SHELL)))
		return ;
	if (!(data->stock = (char*)malloc(sizeof(char) * BUFF_SHELL)))
		return ;
	if (!(data->here_stock = (char*)malloc(sizeof(char) * BUFF_SHELL)))
		return ;
	ft_memset(data->here_stock, 0, sizeof(data->here_stock));
	if (!(data->files = (char*)malloc(sizeof(char) * BUFF_SHELL)))
		return ;
	while (i < BUFF_SHELL)
	{
		data->tab[i] = 0;
		i++;
	}
}
