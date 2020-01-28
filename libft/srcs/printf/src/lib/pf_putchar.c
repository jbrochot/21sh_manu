/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_putchar.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: dzonda <dzonda@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/09 10:00:25 by ezonda       #+#   ##    ##    #+#       */
/*   Updated: 2019/12/28 20:51:37 by dzonda      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#include "../../includes/ft_printf.h"

void	pf_putchar(char c, t_struct *stru)
{
	write(1, &c, 1);
	stru->count_char++;
}
