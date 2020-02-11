/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 00:15:38 by jebrocho          #+#    #+#             */
/*   Updated: 2020/02/11 00:16:01 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	**ft_tabdup(char **tab, int n)
{
	int		i;
	char	**dest;

	i = 0;
	while (tab[i])
		i++;
	i += n;
	if (!(dest = (char**)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = 0;
	while (tab[i])
	{
		dest[i] = ft_strdup(tab[i]);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}
