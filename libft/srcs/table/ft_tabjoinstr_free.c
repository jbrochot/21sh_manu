/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabjoinstr_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 00:07:25 by jebrocho          #+#    #+#             */
/*   Updated: 2020/02/11 00:08:15 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	**ft_tabjoinstr_free(char **tab_src, char *new_l, int mod)
{
	int 	i;
	char 	**new_tab;

	i = ft_tablen(tab_src);
	if (!(new_tab = (char **)malloc(sizeof(char *) * (i + 2))))
		return (NULL);
	i = -1;
	while (tab_src[++i])
		new_tab[i] = ft_strdup(tab_src[i]);
	new_tab[i++] = ft_strdup(new_l);
	new_tab[i] = NULL;
	if (mod == 0 || mod == 2)
		free_tab(tab_src);
	if (mod == 1 || mod == 2)
		free(new_l);
	return (new_tab);
}
