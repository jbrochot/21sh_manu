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

int		env_builtin(char **environ)
{
	int i;

	i = 0;
	while (environ[i])
		ft_putendl(environ[i++]);
	return (1);
}