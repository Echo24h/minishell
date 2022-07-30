/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 22:55:12 by mbastard          #+#    #+#             */
/*   Updated: 2022/07/30 20:42:08 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H
# include "../libft/inc/libft.h"
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "readline/readline.h"
# include "readline/history.h"
# include <sys/wait.h>

// Linux opendir()
# include <dirent.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define CYELLOW "\001\e[1;32m\002"
# define RESET   "\001\e[0m\002"

typedef struct s_data
{
	t_list	*cmds;
	t_list	*first_cmd;
	char	**export;
	char	**envp;
	char	*oldpwd_exp;
	char	*oldpwd_env;
	char	*pipeline_status;
}			t_data;

typedef struct s_cmd
{
	char	*cmd;
	char	**export;
	char	**arg;

	t_data	*data;
}			t_cmd;

//		init.c

//init essential data at start
void	init(t_data *data, char **envp);

//	free.c

// free char **
void	free_tab(char **tab);
// free t_list **cmds
void	free_cmds(t_data *data);
// free all of t_data *data
void	free_data(t_data *data);
// exec.c

//		history.c

// manage history and add (input) to the history file
void	manage_history(char *cmd);

//		parser.c

// Parse the (input) and build the command list in (data)
void	parse_cmds(const char *input, t_data *data);
// Read the cmd line and thransform them for the parsing
char	*lexique_var(t_data *data, const char *cmd_line);
int		id_var(t_data *data, const char *var);
// Read the input and parse arg (space, simple quote and double quotes)
char	**lexique_arg(const char *input);
// Read the input and parse quote
char	*subquote(char *str, char c);
char	get_revquote(const char quote);
// Add the string 'add' in existant **args or create this,
// and return the new '**args'
char	**add_arg(char **args, char *add);

// Read the input and parse pipe
char	**lexique_pipe(const char *input);

//	signals.c

// Manage CTRL + C, CTRL + Z, ...
void	signal_controller(int signal);

// exec.c

// While(t_list *cmds) in data, execute command
int		exec(t_data *data);
// Use execve() for execute bin command
void	bin(t_cmd *cmd);
// Return (1) if cmd->cmd is builtin, else return (0)
int		is_builtin(t_cmd *cmd);
// Execute buitin command
int		builtin(t_cmd *cmd);

// Builtin
void	ft_exit(void);
void	echo(t_cmd *cmd);
void	env(t_cmd *cmd);
char	*pwd(int ret);
void	export(t_cmd *cmd);
void	cd(t_cmd *cmd);
int		unset(t_cmd *cmd);

// Builtin function
int		do_not_replace(const char *s, const char *s2);
int		my_strcmp(char *s1, char *s2);
char	*insert_quotes_exp(const char *s1, char *s2);
void	handle_exp_cd(t_cmd *cmd);
char	*cd_pwd(int envp);
void	handle_env_cd(t_cmd *cmd);
int		arg_is_diff(const char *cpy, const char *arg);
int		check_if_equal(const char *s);

#endif
