/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:11:52 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 17:59:53 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <stdio.h>
# include <stdbool.h>
# include <signal.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define OPERATOR "|<>"
# define SPECIAL_CHARS "@$?*#-!"

# define PATH_MAX 4096

typedef enum e_process_context
{
	PARENT_PROCESS,
	CHILD_PROCESS
}	t_process_context;

typedef enum e_content_type
{
	TOKEN_TYPE,
	ENV_VAR_TYPE
}	t_content_type;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_IN,
	TOKEN_APPEND_OUT,
	TOKEN_HEREDOC,
	TOKEN_WHITESPACE,
	TOKEN_APPEND,
	TOKEN_FILE_OUT,
	TOKEN_FILE_IN,
	TOKEN_DELIMITER
}	t_token_type;

typedef enum e_quote_state
{
	UNQUOTED,
	DOUBLE_QUOTES,
	SINGLE_QUOTES
}	t_quote_state;

typedef enum e_node_type
{
	EXEC_NODE,
	REDIR_NODE,
	PIPE_NODE
}	t_node_type;

typedef struct s_prompt
{
	char	*logname;
	char	*hostname;
	char	*pwd;
	char	*home_path;
	char	*final_str;
}	t_prompt;

typedef struct s_env
{
	char	*key;
	char	*value;
	bool	export_status;
}	t_env;

typedef struct s_index
{
	int	start;
	int	end;
	int	pos;
}	t_index;

typedef struct s_token
{
	int				pos;
	char			*value;
	bool			disable_expansion;
	t_token_type	type;
	t_quote_state	quote_state;
}	t_token;

typedef struct s_cmd
{
	t_node_type	node_type;
	t_list		*token_pos;
}	t_cmd;

typedef struct s_redir_cmd
{
	t_node_type	node_type;
	t_list		*token_pos;
	t_cmd		*cmd;
	char		*file;
	int			open_flags;
	int			fd;
	int			permission;
}	t_redir_cmd;

typedef struct s_pipe_cmd
{
	t_node_type	node_type;
	t_list		*token_pos;
	t_cmd		*left;
	t_cmd		*right;
}	t_pipe_cmd;

typedef struct s_exec_cmd
{
	t_node_type	node_type;
	t_list		*token_pos;
	char		*cmd;
	char		**argv;
}	t_exec_cmd;

typedef struct s_shell
{
	int			pid;
	int			num_pipes;
	char		**paths;
	char		**envp;
	t_prompt	*prompt;
	t_cmd		*cmd;
	t_list		*env_list;
	t_list		*token_list;
	t_index		*index;
}	t_shell;

extern int		g_exit_status;

// MAIN
void			main_loop(t_shell *shell);
void			init_shell_env(t_shell *shell, char **env_var);

// BUILTINS
bool			validate_builtin_args(char **argv);
int				parent_export_handler(t_shell *shell, t_cmd *cmd);
void			extract_key_value(const char *input, char **key, char **value);
int				change_dir(t_shell *shell, t_exec_cmd *cmd);
bool			validate_cd_args(t_shell *shell, char *cmd, char **argv);
int				execute_builtin(t_shell *shell, t_exec_cmd *cmd, int procs);
bool			is_builtin(char *cmd);
void			handle_parent_builtins(t_shell *shell);
int				echo(t_shell *shell, t_exec_cmd *cmd);
void			remove_node_from_list(t_list **list, t_list *node);
t_list			*find_env_by_key(t_list *list, char *key);
void			set_env_variable(t_shell *shell, char *key, char *new_value);
t_list			*find_last_word_token(t_list *token_list);
t_env			*init_env_variable(char *key, char *value);
void			update_env_list(t_shell *shell, t_env *node_content);
int				env(t_shell *shell, t_exec_cmd *cmd);
t_exec_cmd		*find_exec_command_node(t_shell *shell, t_cmd *node);
int				handle_exit_command(t_shell *shell,
					t_exec_cmd *exit_cmd, int procs);
void			print_sorted_env(t_shell *shell);
char			**list_to_array_export(t_list *env);
void			fill_env_array(char **array, t_list *env, int size);
int				export(t_shell *shell, t_exec_cmd *execcmd, int procs);
int				builtin_pwd(t_shell *shell, t_exec_cmd *cmd);
int				unset(t_shell *shell, t_exec_cmd *cmd, int procs);
char			*strip_quotes(char *str);
int				is_exit_code(char *n);
bool			is_valid_number(char *n, long long *exit_code);
void			cd_command_handler(t_shell *shell, char **argv);
void			handle_cd_oldpwd(t_shell *shell);
void			cd_home(t_shell *shell, char *home_path);
void			cd_to_path(t_shell *shell, char *dest_folder);
void			execute_parent_builtin(t_shell *shell, t_list *tmp);
bool			is_builtin_parent(char *cmd);

// CLEANUP
void			tree_cleanup(t_cmd *cmd);
void			clear_exit(t_shell *shell, int status);
void			free_token_list(t_list **token_list);
void			free_env_list(t_list **env_list);
void			free_token_node(void *content);
void			free_env_node(void *content);
void			custom_error(char *prefix, char *context,
					char *message, int exit_code);
void			free_path(char **array);
void			reinit_shell(t_shell *shell);
void			free_prompt_modifier(t_prompt **prompt);
void			free_all_prompt(t_prompt **prompt);

// ENVIRONMENT
void			initialize_empty_env(t_shell *shell);
void			build_env_list(t_shell *shell, char **env_var);
void			update_shell_paths(t_shell *shell);
int				get_key_length(const char *env_var);

// EXECUTION
void			create_pipe(t_shell *shelll, int p[2]);
void			setup_pipe_io(t_shell *shell, t_cmd *cmd, int p[2], int child);
bool			command_error_handler(t_exec_cmd *excmd);
void			exec_tree(t_shell *shell, t_cmd *cmd);
void			execute_shell_command(t_shell *shell, t_exec_cmd *excmd);
void			execute_redirect(t_shell *shell, t_cmd *cmd);
int				safe_fork(t_shell *shell);
void			exec_pipe(t_shell *shell, t_cmd *cmd);
void			run_exec(t_shell *shell, t_cmd *cmd);
void			handle_signal_status(int status);
int				fork_and_setup_child(t_shell *shell, t_cmd *cmd, int *p,
					int pipe_id);

// INPUT
void			validate_shell_args(int argc);
bool			validate_input_syntax(char *input);
bool			syntax_error_handler(char *token);
bool			validate_operator_syntax(char *input, int current_index);
bool			special_exit(char *input);

// PARSING
t_cmd			*parse_simple_command(t_shell *shell, t_list *token_pos);
void			parsing_tree(t_shell *shell);
void			append_command_arg(t_shell *shell, t_exec_cmd *cmd, char *arg);
t_cmd			*create_exec_node(t_shell *shell, t_list *token_pos);
t_cmd			*create_redir_node(t_cmd *subcmd, char *file, int mode, int fd);
t_cmd			*create_pipe_node(t_shell *shell, t_cmd *left, t_cmd *right);

// SIGNALS
void			setup_child_process_signals(void);
void			setup_parent_shell_signals(void);
void			setup_readline_signals(void);
void			setup_heredoc_signals(void);
void			sigint_child_handler(int signo);
void			sigint_readline_handler(int signo);

// TOKEN_EXPANSION

void			handle_quote_expansion(t_shell *shell, t_list *token);
void			handle_token_expansion(t_shell *shell, t_list *token);
char			*get_env_var(t_list *env_list, char *token);
char			*expand_var(t_shell *shell, char *str, int *i);
void			copy_token_content(t_list *token);
void			heredoc_type_handler(t_list *token);
char			*process_token_value(t_shell *shell, t_list *token, int *i);
char			*extract_until_dollar(char *str, int *i);
int				is_valid_expansion_char(char key);
char			*expand_special_parameter(t_shell *shell, char token);

// TOKENIZATION
char			*expand_heredoc_variable(t_shell *shell, char *str);
int				write_heredoc_line(char *filename, char *content);
char			*initialize_heredoc_file(t_shell *shell, int i);
void			handle_heredoc(t_shell *shell, t_list **tokens, char *input);
void			transform_nodes(t_list *start, int type);
void			set_heredoc_type(t_list *start);
void			merge_consecutive_tokens(t_shell *shell, t_list **tokens);
void			remove_nodes(t_shell *shell, t_list **tokens);
char			*resolve_home_directory(t_shell *shell, t_list *tmp);
bool			is_home_directory_token(t_list *tmp);
void			expand_unquoted_variables(t_shell *shell, t_list **tokens);
void			expand_double_quoted_variables(t_shell *shell, t_list **tokens);
void			lexer(t_shell *shell, char *input);
char			*read_prompt_input(t_shell *shell);
void			update_redirection_types(t_list *token_list);
void			create_token_list(t_shell *shell, char *input);
void			find_token_end(char *input, int *end);
char			*initialize_heredoc(t_shell *shell, int i);
void			handle_heredoc_child(t_shell *shell, t_list *token,
					char *filename, char *input_buffer);
void			handle_heredoc_parent(t_shell *shell, t_list *token,
					char *filename, int status);
void			heredoc_input_handler(t_shell *shell, t_list *tmp,
					char *temp_file, char *input);
void			update_token_value(t_list *token, char *new_value);
bool			ends_with_single_pipe(const char *input);

// PROMPT
char			*get_logname(void);
char			*get_hostname(void);
char			*get_home(void);
char			*get_pwd(t_prompt *prompt);
char			*get_prompt(t_prompt *prompt);

// UTILS
long long		ft_atol(const char *nptr);
char			*trim_str(char *s1, char const *set);
bool			contains_char(char *str, char c);
void			skip_quoted_section(const char *input, int *index,
					char quote_char);
void			swap(char **x, char **y);
void			free_key_pair(char *key, char *value);
bool			is_only_whitespace(char *input, int curr_pos);
int				count_command_args(t_list *token_list);
void			free_array(char **array, int size);
bool			is_pipe(char c);
bool			is_output_redir(char c);
bool			is_input_redir(char c);
t_token			*get_token_content(t_list *token);
void			special_redirect_handler(char **input, t_shell *shell);
void			remove_node(t_list **list, t_list *target);
bool			is_directory(char *cmd);
char			*resolve_command_path(t_shell *shell, char *command);
char			**linked_list_to_str_array(t_shell *shell, t_list *list,
					t_content_type type);
char			**ft_split_special(char const *s, char *c);

#endif
