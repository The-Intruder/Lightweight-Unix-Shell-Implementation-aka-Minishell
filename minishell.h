/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaimi   <mnaimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 21:32:20 by mnaimi            #+#    #+#             */
/*   Updated: 2022/06/24 10:52:05 by mnaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ------------------------------- LIBRARIES -------------------------------- */
// Libraries: Functions
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <termios.h>
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>

// Libraries: Macros and Data-Types
# include <stdbool.h>
# include <limits.h>

// Libraries: Custom
# include "libft/libft.h"

/* --------------------------------- MACROS --------------------------------- */
// COLOR CODES //	
# define RL_SUCCESS		"minishell-6.9 $> "

# define WHITESPACE		" \r\v\n\t\f"

/* --------------------------------- TYPEDEFs ------------------------------- */
// ------------ ENUMs ----------- //
typedef enum e_flags {
	EXPAND = -38,
	OUT,
	IN,
	APPEND,
	HEREDOC,
	COMMAND,
	PIPE,
	SPACE_,
	DQ,
	SQ,
}	t_flags;

// ----------- STRUCTs ---------- //
typedef struct s_env_vars {
	char				*key;
	char				*value;
	struct s_env_vars	*next;
}	t_env_vars;

typedef struct s_node
{
	struct s_node	*next;
	int				token;
	char			*data;
	char			*path;
	int				file_fd;
	int				cmd_flag;
	char			**cmd_split;
}	t_node;

typedef struct s_cmds
{
	int		token;
	char	*data;
	char	*path;
	int		cmd_flag;
	int		i;
	int		j;
	int		file_fd;
}	t_cmds;

typedef struct s_info
{
	char			*input;
	char			*input1;
	int				uncqu;
	int				i;
	t_node			*head;
	t_cmds			*cmds;
}	t_info;

typedef struct s_quote {
	int				i;
	int				on;
	int				class;
	struct s_quote	*next;
}	t_quote;

typedef struct d_data
{
	char		**path_split;
	char		*path;
	char		**cmd_split;
	char		*cmd;
	char		*final_path;
	int			i;
	int			check_access;
	char		*ptr;
}	t_data;

typedef struct s_glob_info
{
	int			exit;
	t_env_vars	**env_head;
}	t_glob_info;

t_glob_info	g_glob;

/* --------------------------------- PROTOTYPES ----------------------------- */
int			lexer_start(t_info *info);
int			parcer(t_info *info);

int			handle_execution(t_info *usr_input, t_env_vars **env_head);
void		handle_signals(void);
t_env_vars	*conv_env(char **envp);
int			process_env_var(t_env_vars **head, char *env_var);
void		hide_ctrl(void);
void		restore_ctrl(void);
char		*get_wildcard_data(void);
char		*get_env(const char *var, t_env_vars *env_head);
void		free_split(char **ptr);
void		free_env_linked_list(t_env_vars *head);
//void	handle_sig(int signum, siginfo_t *siginfo, void *sigcontext);

#endif
