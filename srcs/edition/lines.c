/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebrocho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:14:04 by jebrocho          #+#    #+#             */
/*   Updated: 2020/01/20 16:14:22 by jebrocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

int  how_many_before(t_var *data, int pos)
{
  pos--;
  while (pos > 0 && data->lex_str[pos - 1] != '\n')
    pos--;
  return (pos);
}

/*int   how_many_after(t_var *data, int pos)
{

}*/

int   count_current_ret(t_var *data, int pos)
{
  int i;
  int current;

  current = 0;
  i = pos;
  while (i > 0)
  {
    if (data->lex_str[i] == '\n')
      current++;
    i--;
  }
  return (current);
}
