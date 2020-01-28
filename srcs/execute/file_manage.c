/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 10:48:59 by ezonda            #+#    #+#             */
/*   Updated: 2020/01/23 16:22:39 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void		add_to_files(t_var *data, char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (data->files[i])
		i++;
	while (str[j])
	{
		data->files[i] = str[j];
		i++;
		j++;
	}
	data->files[i++] = ' ';
	data->files[i] = '\0';
}

void		update_files(t_var *data)
{
	int		fd;
	int		back_fd;
	char	*line;
	char	**split;

	split = ft_strsplit(data->files, ' ');
	fd = open(split[0], O_RDONLY, O_APPEND);
	back_fd = dup(1);
	dup2(fd, 1);
}

char		*rm_char(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			while (str[i])
			{
				str[i] = str[i + 1];
				i++;
			}
			i = 0;
		}
		i++;
	}
	return (str);
}

void 		realloc_here(char c, t_var *data)
{
	int		i;
	int		j;
	char	s1[BUFF_SHELL];
	char	s2[BUFF_SHELL];

	j = 0;
	i = data->pos;
	while (data->here_stock[i])
		s2[j++] = data->here_stock[i++];
	s2[j] = '\0';
	i = 0;
	j = 0;
	while (i < data->pos)
		s1[j++] = data->here_stock[i++];
	s1[i++] = c;
	s1[i] = '\0';
	free(data->here_stock);
	data->here_stock = ft_strjoin(s1, s2);
//	data->pos++;
//	prompt(data);
}

void		add_to_here_stock(char c, t_var *data)
{
	int i;
	char *tmp;


	i = 0;
	tmp = ft_strdup(data->here_stock);
	free(data->here_stock);
	while (tmp[i])
		i++;
	tmp[i++] = c;
	tmp[i] = '\0';
	data->here_stock = ft_strdup(tmp);
	//	data->pos++;
		free(tmp);
}

void		rm_herend(t_var *data)
{
	int i;

	i = ft_strlen(data->here_stock);
	while (data->here_stock[i] != '\n')
	{
		data->here_stock[i] = '\0';
		i--;
	}
	data->here_stock[i] = '\0';
}
