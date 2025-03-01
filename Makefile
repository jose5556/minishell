# Colors
RESET 		=	\033[0m	
RED 		=	\033[1;31m
GREEN 		=	\033[1;32m
YELLOW 		=	\033[1;33m
CYAN 		=	\033[1;36m
PINK		=	\033[38;5;218m
BOLD_PINK	=	\033[1;38;5;218m
ITALIC		=	\033[3m

# Project Configuration
NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -rf

# Directories
SRCS_DIR	=	srcs
OBJS_DIR	=	objs
LIBFT_DIR	=	./libft
INCLUDES	=	includes

# Source Directories
SUB_DIR		=	environment cleanup input signals tokenization parsing  \
				execution builtins token_expansion utils prompt main

# Create Object Directories
ALL_OBJS_DIR	= $(foreach dir, $(SUB_DIR), $(addprefix $(OBJS_DIR)/, $(dir)))

# Files
SRCS		=	main/main.c \
				main/init_shell.c \
				\
				utils/general_utils.c \
				utils/list_utils.c \
				utils/path_utils.c \
				utils/string_utils.c \
				utils/token_utils.c \
				utils/linked_list_utils.c \
				utils/split_utils.c \
				\
				builtins/builtins_executor.c \
				builtins/env.c \
				builtins/env_list.c \
				builtins/cd.c \
				builtins/cd_utils.c \
				builtins/pwd.c \
				builtins/builtins_utils.c \
				builtins/echo.c \
				builtins/unset.c \
				builtins/export.c \
				builtins/export_utils.c \
				builtins/export_utils2.c \
				builtins/exit.c \
				builtins/exit_utils.c \
				\
				environment/env_init.c \
				environment/env_path.c \
				\
				execution/cmd_exec.c \
				execution/cmd_validator.c \
				execution/cmd_utils.c \
				execution/cmd_utils2.c \
				\
				cleanup/memory_cleanup.c \
				cleanup/shell_cleanup.c \
				cleanup/tree_cleanup.c \
				cleanup/clear_prompt.c \
				\
				token_expansion/token_utils.c \
				token_expansion/token_expander.c \
				token_expansion/variable_expander.c \
				\
				input/input_validator.c \
				input/syntax_validator.c \
				input/input_validator2.c \
				\
				parsing/parse_tree.c \
				parsing/create_tree_nodes.c \
				\
				signals/signal_setup.c \
				signals/signal_handlers.c \
				\
				prompt/get_prompt.c \
				prompt/prompt_values.c \
				\
				tokenization/token_transformer.c \
				tokenization/token_redirect.c \
				tokenization/token_generator.c \
				tokenization/lexer.c \
				tokenization/token_expander.c \
				tokenization/token_analyzer.c \
				tokenization/input_reader.c \
				tokenization/input_reader_utils.c \
				tokenization/home_expander.c \
				tokenization/home_expander_utils.c \
				tokenization/heredoc_manager.c \
				tokenization/heredoc_manager2.c \
				tokenization/heredoc_helper.c

# Object Files
OBJS		=	$(SRCS:%.c=$(OBJS_DIR)/%.o)
LIBFT		=	./libft/libft.a

# ASCII Art
define MINISHELL_ART

$(BOLD_PINK)
    ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     
    ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     
    ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     
    ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     
    ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗
    ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝
$(RESET)
endef
export MINISHELL_ART

define UP_TO_DATE_ART

$(BOLD_PINK)
   ██╗   ██╗██████╗    ████████╗ ██████╗     ██████╗  █████╗ ████████╗███████╗
   ██║   ██║██╔══██╗   ╚══██╔══╝██╔═══██╗    ██╔══██╗██╔══██╗╚══██╔══╝██╔════╝
   ██║   ██║██████╔╝      ██║   ██║   ██║    ██║  ██║███████║   ██║   █████╗  
   ██║   ██║██╔═══╝       ██║   ██║   ██║    ██║  ██║██╔══██║   ██║   ██╔══╝  
   ╚██████╔╝██║           ██║   ╚██████╔╝    ██████╔╝██║  ██║   ██║   ███████╗
    ╚═════╝ ╚═╝           ╚═╝    ╚═════╝     ╚═════╝ ╚═╝  ╚═╝   ╚═╝   ╚══════╝
$(RESET)
endef
export UP_TO_DATE_ART

# Rules
all: header $(NAME)

header:
	@if [ -f $(NAME) ] && [ -z "$$(find $(SRCS_DIR) -newer $(NAME))" ]; then \
		echo "$$UP_TO_DATE_ART"; \
		echo "$(PINK)╔═══════════════════════════ Nothing to Update ═══════════════════════════╗$(RESET)"; \
		echo "$(PINK)║ $(GREEN)🎀 All files are up to date! 🚀$(RESET) 				  $(PINK)║$(RESET)"; \
		echo "$(PINK)╚═════════════════════════════════════════════════════════════════════════╝$(RESET)"; \
		exit 0; \
	else \
		echo "$$MINISHELL_ART"; \
		echo "$(PINK)╔════════════════════════════ Building Minishell ═══════════════════════════╗$(RESET)"; \
	fi

$(NAME): $(OBJS) $(LIBFT) includes/minishell.h
	@echo "$(PINK)║ $(ITALIC)✨ Linking everything together...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
	@echo "$(PINK)║ $(GREEN)🎀 Minishell successfully compiled! 🚀$(RESET)"
	@echo "$(PINK)╚═══════════════════════════════════════════════════════════════════════════╝$(RESET)"
	@find $(OBJS_DIR) -name ".compiled" -type f -delete

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR) $(ALL_OBJS_DIR)
	@echo "$(PINK)║ $(YELLOW)✨ Created build directories$(RESET)"

$(OBJS): $(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c | $(OBJS_DIR)
	@$(CC) -I $(INCLUDES) $(CFLAGS) -c $< -o $@
	@if [ "$$(dirname $< | xargs basename)" = "srcs" ]; then \
		echo "$(PINK)║ $(ITALIC)Compiling: $(RESET)$(notdir $<)"; \
	else \
		echo "$(PINK)║ $(ITALIC)Compiling @$$(dirname $< | xargs basename)/$(notdir $<)$(RESET)"; \
	fi

$(LIBFT):
	@echo "$(PINK)║ $(YELLOW)Building libft...$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIR)

clean:
	@echo "$(PINK)╔════════════════════════════ Cleaning Project ════════════════════════════╗$(RESET)"
	@$(RM) $(OBJS_DIR)
	@echo "$(PINK)║ $(CYAN)🧹 Cleaned all object files$(RESET)"
	@$(MAKE) $(MK_FLAG) clean -sC $(LIBFT_DIR)
	@echo "$(PINK)╚══════════════════════════════════════════════════════════════════════════╝$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) $(MK_FLAG) fclean -sC $(LIBFT_DIR)
	@echo "$(PINK)║ $(CYAN)Cleaned executable$(RESET)"

leaks: readline.supp
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-fds=yes --log-file=output.log ./minishell

readline.supp:
	echo "{" > readline.supp
	echo "    leak readline" >> readline.supp
	echo "    Memcheck:Leak" >> readline.supp
	echo "    ..." >> readline.supp
	echo "    fun:readline" >> readline.supp
	echo "}" >> readline.supp
	echo "{" >> readline.supp
	echo "    leak add_history" >> readline.supp
	echo "    Memcheck:Leak" >> readline.supp
	echo "    ..." >> readline.supp
	echo "    fun:add_history" >> readline.supp
	echo "}" >> readline.supp

re: fclean all

.PHONY: all clean fclean re
