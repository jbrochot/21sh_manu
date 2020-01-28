/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 14:10:40 by ezonda            #+#    #+#             */
/*   Updated: 2020/01/28 10:48:01 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void      add_this(char *car, t_var *data)
{
	if (data->pos == data->char_count)
	{
		data->lex_str = ft_strjoin_free(data->lex_str, car, 0);
		data->pos++;
	}
	else
		realloc_str(car[0], data);
}

void	parse_multi_quotes(t_var *data, int index)
{
	char buffer[6];
	char *stock;

	data->q_prompt = 1;
	stock = ft_strdup(data->lex_str);
	ft_bzero(data->lex_str, ft_strlen(data->lex_str));
	add_to_here_stock('\\', data);
	add_to_here_stock('n', data);
	data->pos = 0; //rajoute
	ft_putchar('\n');
	while (data->quotes % 2 != 0)
	{
		get_curs_pos(data, data->pos);
		prompt(data);
		update_data(0, data);
		ft_bzero(buffer, 6);
		get_winsize(data);
		check_overflow(data);
		read(0, &buffer, sizeof(buffer));
		if (buffer[0] >= 32 && buffer[0] < 127 && buffer[1] == 0)
		{
			ft_putchar(buffer[0]);
//			add_to_here_stock(buffer[0], data);
			add_this(buffer, data);
//			data->lex_str = ft_strjoin_free(data->lex_str, &buffer[0], 0);
//			data->pos = ft_strlen(data->lex_str);
			data->char_count++;
		}
		if (!ft_strcmp(buffer, RET))
		{
			data->here_stock = ft_strjoin_free(data->here_stock, data->lex_str, 0);
			if (data->lex_str[ft_strlen(data->lex_str) - 1] == '\'')
				break ;
			add_to_here_stock('\\', data);
			add_to_here_stock('n', data);
			data->pos = 0; //rajoute
			ft_bzero(data->lex_str, ft_strlen(data->lex_str));
			ft_putchar('\n');
		}
		get_key(data, buffer);
	}
	data->lex_str = ft_strdup(data->here_stock);
	data->lex_str = ft_strjoin(stock, data->lex_str);
	rm_char(&data->lex_str[index], '\'');
	data->q_prompt = 0;
}

int		check_backslah(t_var *data)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (data->here_stock[i])
	{
		if (data->here_stock[i] == '\\' && data->here_stock[i + 1] == '"')
		{
			ret = 1;
			data->here_stock[i] = data->here_stock[i + 1];
			i++;
		}
		i++;
	}
	return (ret);
}

void	parse_multi_dquotes(t_var *data, int index)
{
	char buffer[6];
	char *stock;

	data->dq_prompt = 1;
	stock = ft_strdup(data->lex_str);
	ft_bzero(data->lex_str, ft_strlen(data->lex_str));
	add_to_here_stock('\\', data);
	add_to_here_stock('n', data);
	data->pos = 0; // rajoute
	ft_putchar('\n');
	while (data->dquotes % 2 != 0)
	{
		get_curs_pos(data, data->pos);
		prompt(data);
		update_data(0, data);
		ft_bzero(buffer, 6);
		get_winsize(data);
		check_overflow(data);
		read(0, &buffer, sizeof(buffer));
		if (buffer[0] >= 32 && buffer[0] < 127 && buffer[1] == 0)
		{
			ft_putchar(buffer[0]);
	//		add_to_here_stock(buffer[0], data);
	//		data->lex_str = ft_strjoin_free(data->lex_str, &buffer[0], 0);
	//		data->pos = ft_strlen(data->lex_str);
			add_this(buffer, data); //rajoute
			data->char_count++;
		}
		if (!ft_strcmp(buffer, RET))
		{
			data->here_stock = ft_strjoin_free(data->here_stock, data->lex_str, 0); // rajoute
			if (ft_strchr(data->lex_str, '"'))
				if (!check_backslah(data))
					break ;
			add_to_here_stock('\\', data);
			add_to_here_stock('n', data);
			data->pos = 0;  // rajoute
			ft_bzero(data->lex_str, ft_strlen(data->lex_str));
			ft_putchar('\n');
		}
		get_key(data, buffer);
	}
	data->lex_str = ft_strdup(data->here_stock);
	data->lex_str = ft_strjoin(stock, data->lex_str);
	rm_char(&data->lex_str[index], '"');
	data->dq_prompt = 0;
}

void	parse_simple_quotes(t_var *data, int index)
{
	int		i;
	int		last_pos;
	char	*tmp_start;
	char	*tmp_end;

	i = 0;
	tmp_start = ft_strnew(ft_strlen(data->lex_str));
	tmp_end = ft_strnew(ft_strlen(data->lex_str));
	while (data->lex_str[i] && data->lex_str[i] != '\'')
	{
		tmp_start[i] = data->lex_str[i];
		i++;
	}
	i = 0;
	index++;
	while (data->lex_str[index] && data->lex_str[index] != '\'')
	{
		data->qstr[i] = data->lex_str[index];
		if (data->qstr[i] == '"')
			data->dquotes--;
		i++;
		index++;
	}
	i = 0;
	index++;
	last_pos = index - 2;
	while (data->lex_str[index])
	{
		tmp_end[i] = data->lex_str[index];
		i++;
		index++;
	}
	data->lex_str = ft_strjoin(tmp_start, data->qstr);
	data->lex_str = ft_strjoin(data->lex_str, tmp_end);
	free(data->qstr);
	data->quotes -= 2;
	read_quotes(data, last_pos);
}

void	parse_simple_dquotes(t_var *data, int index)
{
	int		i;
	int		last_pos;
	char	*tmp_start;
	char	*tmp_end;

	i = 0;
	tmp_start = ft_strnew(ft_strlen(data->lex_str));
	tmp_end = ft_strnew(ft_strlen(data->lex_str));
	while (data->lex_str[i] && data->lex_str[i] != '"')
	{
		tmp_start[i] = data->lex_str[i];
		i++;
	}
	i = 0;
	index++;
	while (data->lex_str[index] && data->lex_str[index] != '"')
	{
		if (data->lex_str[index] == '\\' && data->lex_str[index + 1] == '"')
		{
			last_pos = index;
			while (data->lex_str[index])
			{
				data->lex_str[index] = data->lex_str[index + 1];
				index++;
			}
			index = last_pos;
			data->dquotes--;
		}
		data->qstr[i] = data->lex_str[index];
		if (data->qstr[i] == '\'')
			data->quotes--;
		i++;
		index++;
	}
	i = 0;
	index++;
	last_pos = index - 2;
	while (data->lex_str[index])
	{
		tmp_end[i] = data->lex_str[index];
		i++;
		index++;
	}
	data->lex_str = ft_strjoin(tmp_start, data->qstr);
	data->lex_str = ft_strjoin(data->lex_str, tmp_end);
	free(data->qstr);
	data->dquotes -= 2;
	read_quotes(data, last_pos);
}

int		check_quotes(t_var *data)
{
	int i;

	i = 0;
	data->quotes = 0;
	data->dquotes = 0;
	while (data->lex_str[i])
	{
		if (data->lex_str[i] == '\'')
			data->quotes++;
		if (data->lex_str[i] == '"')
			data->dquotes++;
		i++;
	}
	if (data->quotes == 0 && data->dquotes == 0)
		return (0);
	else
		return (1);
}

void	read_quotes(t_var *data, int i)
{
	data->qstr = ft_strnew(ft_strlen(data->lex_str));
	if (!data->lex_str[i])
		return ;
	while (data->lex_str[i]
			&& data->lex_str[i] != '\'' && data->lex_str[i] != '"')
		i++;
	if (data->lex_str[i] == '\'' && data->quotes == 1)
		parse_multi_quotes(data, i);
	else if (data->lex_str[i] == '\'' && data->quotes != 0)
		parse_simple_quotes(data, i);
	else if (data->lex_str[i] == '"' && data->dquotes == 1)
		parse_multi_dquotes(data, i);
	else if (data->lex_str[i] && data->dquotes != 0)
		parse_simple_dquotes(data, i);
}
