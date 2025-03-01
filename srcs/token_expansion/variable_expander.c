/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:13:57 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:13:18 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_var(t_list *env_list, char *token)
{
	char	*key;
	char	*value;
	t_list	*env;

	env = env_list;
	value = ft_strdup("");
	while (env)
	{
		key = ((t_env *)env->content)->key;
		if (!ft_strcmp(token, key) && ((t_env *)env->content)->export_status)
		{
			free(value);
			value = ft_strdup(((t_env *)env->content)->value);
			break ;
		}
		else if (!ft_strcmp(key, "HOME") && !ft_strcmp("~", token))
		{
			free(value);
			value = ft_strdup(((t_env *)env->content)->value);
			break ;
		}
		env = env->next;
	}
	return (value);
}

char	*expand_var(t_shell *shell, char *str, int *i)
{
	int		start;
	char	*key;
	char	*exp_val;

	if (ft_isdigit(str[*i]) || contains_char(SPECIAL_CHARS, str[*i]))
	{
		exp_val = expand_special_parameter(shell, str[*i]);
		(*i)++;
		return (exp_val);
	}
	start = *i;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	key = ft_substr(str, start, (*i) - start);
	exp_val = get_env_var(shell->env_list, key);
	free(key);
	return (exp_val);
}

void	copy_token_content(t_list *token)
{
	free(get_token_content(token)->value);
	get_token_content(token)->value = ft_strdup
	(get_token_content(token->next)->value);
	get_token_content(token)->quote_state = get_token_content
	(token->next)->quote_state;
}

void	heredoc_type_handler(t_list *token)
{
	free(get_token_content(token)->value);
	get_token_content(token)->value = ft_strjoin
	("$", get_token_content(token->next)->value);
}

char	*process_token_value(t_shell *shell, t_list *token, int *i)
{
	char	*expanded;

	if (get_token_content(token)->value[*i] == '$')
	{
		(*i)++;
		if (is_valid_expansion_char(get_token_content(token)->value[*i]))
			expanded = expand_var(shell, get_token_content(token)->value, i);
		else
			expanded = ft_strjoin("$", extract_until_dollar
					(get_token_content(token)->value, i));
	}
	else
		expanded = extract_until_dollar(get_token_content(token)->value, i);
	return (expanded);
}
