/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 14:14:49 by ezonda            #+#    #+#             */
/*   Updated: 2019/04/06 15:41:07 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_strclr(char *s)
{
	int i;

	i = 0;
	if (!(s))
		return ;
	while (s[i])
	{
		s[i] = '\0';
		i++;
	}
}
