/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:13:34 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:14:23 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*handle_redirection(t_shell *shell, t_cmd *cmd)
{
	int		redir_type;
	t_token	*token;

	token = cmd->token_pos->content;
	redir_type = token->type;
	if (redir_type == TOKEN_APPEND)
		cmd = create_redir_node(cmd, token->value, O_WRONLY
				| O_CREAT | O_APPEND, 1);
	else if (redir_type == TOKEN_FILE_IN || redir_type == TOKEN_DELIMITER)
		cmd = create_redir_node(cmd, token->value, O_RDONLY, 0);
	else if (redir_type == TOKEN_FILE_OUT)
		cmd = create_redir_node(cmd, token->value, O_WRONLY
				| O_CREAT | O_TRUNC, 1);
	if (!cmd)
		clear_exit(shell, 1);
	return (cmd);
}

static t_cmd	*parse_pipeline(t_shell *shell, t_list *token_pos)
{
	t_cmd	*cmd;
	t_token	*token;

	(void)shell;
	cmd = parse_simple_command(shell, token_pos);
	if (!cmd)
		return (NULL);
	token_pos = cmd->token_pos;
	if (token_pos)
	{
		token = (t_token *)token_pos->content;
		if (token && token->type == TOKEN_PIPE)
		{
			token_pos = token_pos->next;
			cmd = create_pipe_node(shell, cmd,
					parse_pipeline(shell, token_pos));
		}
	}
	return (cmd);
}

t_cmd	*parse_simple_command(t_shell *shell, t_list *token_pos)
{
	t_cmd		*status;
	t_list		*tmp;
	t_token		*token;
	t_exec_cmd	*exec_cmd;

	(void)shell;
	status = create_exec_node(shell, token_pos);
	exec_cmd = (t_exec_cmd *)status;
	tmp = status->token_pos;
	while (tmp)
	{
		token = tmp->content;
		status->token_pos = tmp;
		if (token->type == TOKEN_PIPE)
			break ;
		else if (token->type == TOKEN_WORD)
			append_command_arg(shell, exec_cmd, token->value);
		else if (token->type == TOKEN_APPEND || token->type == TOKEN_DELIMITER
			|| token->type == TOKEN_FILE_IN || token->type == TOKEN_FILE_OUT)
			status = handle_redirection(shell, status);
		tmp = tmp->next;
	}
	return (status);
}

void	parsing_tree(t_shell *shell)
{
	shell->cmd = parse_pipeline(shell, shell->token_list);
}
