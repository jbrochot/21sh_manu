/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:34:02 by ezonda            #+#    #+#             */
/*   Updated: 2020/02/08 15:22:03 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

t_cmd		*get_redir_type(t_cmd *cmd, int tok, char *f)
{
	if (tok == '>')
		cmd = parse_redir_cmd(cmd, f,
				(O_WRONLY | O_NONBLOCK | O_CREAT | O_TRUNC), 1);
	if (tok == '+')
		cmd = parse_redir_cmd(cmd, f,
				(O_WRONLY | O_NONBLOCK | O_CREAT | O_APPEND), 1);
	if (tok == '=')
		cmd = parse_redir_cmd(cmd, f,
				(O_RDONLY | O_NONBLOCK | O_CREAT | O_APPEND), 0);
	if (tok == '*')
		cmd = parse_redir_cmd(cmd, f,
				(O_WRONLY | O_NONBLOCK | O_CREAT | O_TRUNC), 2);
	if (tok == '/')
		cmd = parse_redir_cmd(cmd, f,
				(O_WRONLY | O_NONBLOCK | O_CREAT | O_APPEND), 2);
	return (cmd);
}

t_cmd		*parse_redir(t_cmd *cmd, char **p, char *end)
{
	int		tok;
	char	*q;
	char	*eq;
	char	*f;

	while (strings_scan_whitespaces(p, end, "12<>"))
	{
		if ((**p == '1' || **p == '2') && (*p)[1] != '>' && (*p)[1] != '<')
			break ;
		tok = tokenizer(p, end, 0, 0);
		tokenizer(p, end, &q, &eq);
		if ((f = ft_strndup(q, eq - q + 1)) && tok == '<')
			cmd = parse_redir_cmd(cmd, f, (O_RDONLY | O_NONBLOCK | O_CREAT), 0);
		else
			cmd = get_redir_type(cmd, tok, f);
	}
	return (cmd);
}

t_cmd		*parse_basic(char **p_input, char *end, int *res)
{
	char			*new_cmd[3];
	int				tok;
	t_exec_cmd		*cmd;
	t_cmd			*ret;
	t_list			*lst;

	ret = parse_basic_cmd();
	cmd = (t_exec_cmd *)ret;
	cmd->argv = NULL;
	ret = parse_redir(ret, p_input, end);
	while (*p_input < end)
	{
		if ((tok = tokenizer(p_input, end, &new_cmd[0], &new_cmd[1])) == 0)
			break ;
		if (tok != 'a' && (*res = 0))
			return (NULL);
		new_cmd[2] = ft_strndup(new_cmd[0], new_cmd[1] - new_cmd[0]);
//		ft_printf("\nMALLOC LST\n");
		lst = ft_lstnew(new_cmd[2], new_cmd[1] - new_cmd[0] + 1);
		ft_lstadd_back(&cmd->argv, lst);
		free(new_cmd[2]);
		ret = parse_redir(ret, p_input, end);
	}
	return (ret);
}

t_cmd		*parse_pipe(char **p_input, char *end, int *res)
{
	t_cmd	*cmd;
//	t_cmd	*tmp1;
//	t_cmd	*tmp2;
	char	*new_cmd;
	char	*new_cmd_end;

	if (strings_scan_pipes(
		p_input, end, &new_cmd, &new_cmd_end))
	{
//		tmp1 = parse_basic(&new_cmd, new_cmd_end, res);
		cmd = parse_basic(&new_cmd, new_cmd_end, res);
		(*p_input)++;
//		tmp2 = parse_pipe(p_input, end, res);
		cmd = parse_pipe_cmd(/*tmp1, tmp2)*/
			cmd, parse_pipe(p_input, end, res));
	}
	else
		cmd = parse_basic(&new_cmd, new_cmd_end, res);
	return (cmd);
}

t_cmd		*shell_parser(char *input)
{
	char		*end;
	t_cmd		*cmd;
	int			res;

	res = 1;
	end = input + ft_strlen(input);
	cmd = parse_pipe(&input, end, &res);
	return (cmd);
}
