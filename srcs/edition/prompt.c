/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 13:47:01 by ezonda            #+#    #+#             */
/*   Updated: 2020/01/28 10:22:46 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

static void		print_str(t_var *data)
{
	int i;

	i = 0;
	while (data->lex_str[i])
	{
		if (data->tab[i] == 0)
			ft_putchar(data->lex_str[i]);
		else
		{
			TERMCAP("mr");
			ft_putchar(data->lex_str[i]);
			TERMCAP("me");
		}
		i++;
	}
}

static void		print_prompt(t_var *data)
{
	if (data->q_prompt == 1)
		ft_putstr("quote> ");
	else if (data->dq_prompt == 1)
		ft_putstr("dquote> ");
	else if (data->p_prompt == 1)
		ft_putstr("pipe> ");
	else if (data->h_prompt == 1)
		ft_putstr("heredoc> ");
	else if (data->n_prompt == 1)
		ft_putstr("> ");
	else if (data->c_prompt == 1)
		ft_putstr("cursh> ");
	else
	{
		TERMCAP("md");
		data->std_prompt = 1;
		ft_putstr("21sh $> ");
		TERMCAP("me");
	}
}

void			prompt(t_var *data)
{
	int tmp;

	tmp = data->pos;
	if (!data->lex_str)
		if (!(data->lex_str = (char*)malloc(sizeof(char) * BUFF_SHELL)))
			return ;
	if (data->q_prompt == 1)
		data->pos = -8;
	else if (data->dq_prompt == 1)
		data->pos = -9;
	else if (data->p_prompt != 1)
		data->pos = -9;
	else if (data->p_prompt == 1)
		data->pos = -7;
	else if (data->h_prompt == 1)
		data->pos = -10;
	else if (data->n_prompt == 1)
		data->pos = -3;
	else if (data->c_prompt == 1)
		data->pos = -8;
/*	if (data->save_pos == 0 || data->save_pos == 1 || data->save_pos == 2)
		get_curs_pos_line_left(data, data->pos, tmp, 0);
	else
		get_curs_pos_line_right(data, data->pos, tmp, 0);*/
	get_curs_pos(data, data->pos);
	TERMCAP("cd");
	print_prompt(data);
	print_str(data);
	data->pos = tmp;
//	if (data->save_pos == 0 || data->save_pos == 1 || data->save_pos == 2)
//		get_curs_pos_line_left(data, data->pos, data->pos, 1);
//	else
//		get_curs_pos_line_right(data, data->pos, data->pos, 1);
	data->history_mod = 0;
	data->save_pos = 0;
	get_curs_pos(data, data->pos);
}

void			get_winsize(t_var *data)
{
	ioctl(STDIN_FILENO, TIOCGWINSZ, &wind);
	data->nb_cols = wind.ws_col - 8;
	data->nb_rows = wind.ws_row;
}

void			get_curs_pos(t_var *data, int index)
{
	index = ft_strlen(data->lex_str);
	while (index > data->pos)
	{
		TERMCAP("le");
		index--;
	}
}

void 			get_curs_pos_line_left(t_var *data, int index, int pos, int mod)
{
	int first_c;
	int current_ret;
	int nb_prompt;
	int tmp;

	tmp = 0;
	if (data->pos >= 0 && data->lex_str[pos] == '\n'
			&& mod == 0 && data->save_pos != 1)
		TERMCAP("up");
	if (mod == 0)
		index = pos;
	else
		index = ft_strlen(data->lex_str);
	while (index > data->pos)
	{
		if (index > 0 && data->lex_str[index - 1] == '\n' && data->quotes % 2 == 0
				&& data->dquotes % 2 == 0 && data->history_mod == 0)
		{
			index--;
			first_c = how_many_before(data, index);
			current_ret = count_current_ret(data, index - 1);
			if (current_ret > 0)
				nb_prompt = 0;
			else
				nb_prompt = -8;
			TERMCAP("up");
			while (nb_prompt < 0)
			{
				TERMCAP("nd");
				nb_prompt++;
			}
			while (first_c < index)
			{
				TERMCAP("nd");
				first_c++;
			}
		}
		else
		{
			TERMCAP("le");
			index--;
		}
		if (data->save_pos == 2 && tmp == 0)
		{
			tmp++;
			TERMCAP("up");
		}
	}
}

void 			get_curs_pos_line_right(t_var *data, int index, int pos, int mod)
{
	int first_c;
	int current_ret;
	int nb_prompt;
	int tmp;

	tmp = 1;
	if (mod == 0)
		index = pos;
	else
		index = ft_strlen(data->lex_str);
	while (index > data->pos)
	{
		if (index > 0 && data->lex_str[index - 1] == '\n' && data->quotes % 2 == 0
				&& data->dquotes % 2 == 0 && data->history_mod == 0)
		{
			if (index == pos)
				tmp = 0;
			index--;
			first_c = how_many_before(data, index);
			current_ret = count_current_ret(data, index - 1);
			if (current_ret > 0)
				nb_prompt = 0;
			else
				nb_prompt = -8;
			if (tmp != 0)
				TERMCAP("up");
			while (nb_prompt < 0)
			{
				TERMCAP("nd");
				nb_prompt++;
			}
			while (first_c < index)
			{
				if (tmp != 0)
					TERMCAP("nd");
				first_c++;
			}
		}
		else
		{
			TERMCAP("le");
			index--;
		}
		tmp++;
	}
}
