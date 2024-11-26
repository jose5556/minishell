/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:58:34 by joseoliv          #+#    #+#             */
/*   Updated: 2024/11/28 00:13:31 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>

extern int	g_signal;

typedef struct s_list
{
	struct s_list *left;
	struct s_list *right;
	struct s_list *root;
} t_list;

typedef struct s_prompt
{
	char	*logname;
	char	*hostname;
	char	*pwd;
	char	*home_directory;
} t_prompt;

void	get_prompt(t_prompt *prompt);
char	*get_logname();
char	*get_hostname();
char	*get_home();
char	*get_pwd(t_prompt *prompt);

void	init_signals();
void	init(t_prompt **prompt);


char	*ft_readline(t_prompt *prompt, char **line);
#endif