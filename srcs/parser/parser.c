/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezonda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:34:02 by ezonda            #+#    #+#             */
/*   Updated: 2019/12/06 03:39:33 by ezonda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

t_cmd		*parse_redir(t_cmd *cmd, char **p, char *end)
{
	int		tok;
	char	*q;
	char	*eq;
	char	*f;

	while (strings_scan_whitespaces(p, end, "12<>"))
	{
		if ((**p == '1' || **p == '2') && (*p)[1] != '>' && (*p)[1] != '<')
		{
//			ft_printf("\nBREAK, **p:%c, (*p)[1]:%c\n", **p, (*p)[1]);
			break ;
		}
		tok = tokenizer(p, end, 0, 0);
		tokenizer(p, end, &q, &eq);
		if ((f = ft_strndup(q, eq - q + 1)) && tok == '<')
		{
//			ft_printf("\nparse_redir >> file : %s\n", f);
//			getchar();
			cmd = parse_redir_cmd(cmd, f, M_READ, 0);
		}
		if (tok == '>')
		{
		//	ft_printf("\nparse_redir > file : %s\n", f);
		//	getchar();
			cmd = parse_redir_cmd(cmd, f, M_WRITE_TRUNC, 1);
		}
		if (tok == '+')
		{
//			ft_printf("\nparse_redir + file : %s\n", f);
//			getchar();
			cmd = parse_redir_cmd(cmd, f, M_WRITE_APPEND, 1);
		}
		if (tok == '=')
		{
//			ft_printf("\nparse_redir = file : %s\n", f);
//			getchar();
			cmd = parse_redir_cmd(cmd, f, M_READ_APPEND, 0);
		}
		if (tok == '*')
		{
//			ft_printf("\nparse_redir >> file : %s\n", f);
//			getchar();
			cmd = parse_redir_cmd(cmd, f, M_WRITE_TRUNC, 2);
		}
		if (tok == '/')
		{
//			ft_printf("\nparse_redir >> file : %s\n", f);
//			getchar();
			cmd = parse_redir_cmd(cmd, f, M_WRITE_APPEND, 2);
		}
	}
	return (cmd);
}

t_cmd		*parse_basic(char **p_input, char *end, int *res)
{
	char			*new_cmd;
	char			*new_cmd_end;
	int				tok;
	t_exec_cmd		*cmd;
	t_cmd			*ret;

//	ft_printf("\nparse_basic - input : {%s} - {%s}\n", *p_input, end);
//	getchar();
	ret = parse_basic_cmd();
	cmd = (t_exec_cmd *)ret;
	cmd->argv = NULL;
	ret = parse_redir(ret, p_input, end);
	while (*p_input < end)
	{
//		ft_printf("\np_input : %d -- end : %d -- diff : %d\n", *p_input, end, 
//				end - *p_input);
		if ((tok = tokenizer(p_input, end, &new_cmd, &new_cmd_end)) == 0)
		{
			break ;
		}
//		ft_printf("\ntokenizer = %d\n", tok);
//		ft_printf("\nhere3\n");
//		getchar();
//		if (tok == 49 || tok == 50)
//			return (NULL) ;
		if (tok != 'a' && (*res = 0))
			return (NULL);
		ft_lstadd_back(&cmd->argv, ft_lstnew(
			ft_strndup(new_cmd, new_cmd_end - new_cmd),
			new_cmd_end - new_cmd + 1));
		ret = parse_redir(ret, p_input, end);
//		ft_printf("\np_input : %d -- end : %d -- diff : %d\n", *p_input, end, 
//				end - *p_input);
	}
//	ft_printf("\nHERE\n");
//	getchar();
//	ft_printf("\ncmd : {%s}\n", ft_strndup(new_cmd, new_cmd_end - new_cmd));
	return (ret);
}

t_cmd		*parse_pipe(char **p_input, char *end, int *res)
{
	t_cmd	*cmd;
	char	*new_cmd;
	char	*new_cmd_end;

	if (strings_scan_pipes(
		p_input, end, &new_cmd, &new_cmd_end))
	{
//		ft_printf("\nin scan_pipes\n");
		cmd = parse_basic(&new_cmd, new_cmd_end, res);
		(*p_input)++;
//		ft_printf("\np_input: {%s}\n", *p_input);
		cmd = parse_pipe_cmd(
			cmd, parse_pipe(p_input, end, res));
	}
	else
	{
//		ft_printf("\nin scan_basic\n");
		cmd = parse_basic(&new_cmd, new_cmd_end, res);
	}
//	ft_printf("\nnew_cmd : {%s} - new_cmd_end : {%s}", new_cmd, new_cmd_end);
	if (!ft_strcmp("|", new_cmd))
	{
	}
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
/*	if (input != end || res == 0)
	{
		ft_putendl_fd("Syntax error", 2);
		return (NULL);
	}
	else*/
		return (cmd);
}
