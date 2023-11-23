/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:05:52 by smallem           #+#    #+#             */
/*   Updated: 2023/11/23 17:14:43 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libs/libft/libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include <signal.h>
#include <termios.h>
#include <sys/wait.h>

#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

enum e_op
{
	TK_DOLLAR	= '$',
	TK_SQUOTE	= '\'',
	TK_DQUOTE	= '"',
	TK_LESS		= '<',
	TK_GREATER	= '>',
	TK_PIPE		= '|',
	TK_QST		= '?',
	TK_SPACE	= ' ',
	TK_NL		= '\n',
	TK_TAB		= '\t',
	TK_EQ		= '=',
};

typedef struct	s_fetch	t_fetch;
typedef struct	s_fetch
{
	char	*name;
	char	*val;
	int		start;
	int		end;
	int		valid_name;
}	t_fetch;

typedef struct s_cmd t_cmd;
typedef struct s_cmd
{
	int		fd_in;
	int		fd_out;
	int		*red;
	char	**args;
	int		index;
	char	*path;
}	t_cmd;

int ex_stat;

char	**copy_env(char **env, t_term *term);
int		init_s(t_term *term, char *input);
t_tree	*create_node(enum e_token type, void *content, t_term *term);
void	create_tree(ssize_t nb_pipes, t_tree **root, t_term *term);
void	populate_tree(t_tree **root, t_term *term);
void	update_tree(t_term *term, t_tree **root, int *i);
t_cmd	*build_cmd(t_term *term, t_tree **node, int *ind);

int 	check_input(char *input, t_term *term);
int		count_pipes(t_term *term);
int		check_quotes(char *str);
int		check_flag(t_term *term);
int		skip_spaces(char *str, int i);
int		skip_quote(char *str, int i, char c);
int		is_space(char c);

char	**my_split(char *str, t_term *term);
char	**splt(char *input, t_term *term);
char	**splt_space(t_cmd *cmd, char *str, char *str_tok, t_term *term);

int		expand(t_term *term, t_cmd *cmd, char *str);
char	*fetch_line(char *to_find, t_term *term);
t_fetch	*fill_fetch(char *str, t_term *term, int len);
char	**create_lines(char *str, t_fetch *to_fetch, int len, t_term *term);
void	fill_lines(char *str, char **mat, t_fetch *to_fetch);

int		redirect(t_cmd *cmd, char **mat, t_term *term);
char	*create_name(char *str, int j, int len, t_term *term);
int		get_name(char *str, t_term *term, char **name);
int		get_fname(char *str, t_term *term, int flag, t_cmd *cmd);
int		test(int *i, char **m, t_term *term, t_cmd *cmd);

int		open_outfiles(int flag, char *name, t_cmd *cmd);
int		open_infiles(int flag, char *name, t_cmd *cmd);

void	clean(t_term *term, t_cmd *cmd, char **mat);

int 	execution(t_term *term);
int		is_builtin(t_cmd *cmd);
void	exe_builtins(t_cmd *cmd, t_term *term, int flag);
char	*get_path(t_term *term, char *cmd);
int		exec_cmd(t_cmd *cmd, int tmp, t_term *term);

// void	sigquit_handler(int signo, t_term *term);
// void	sigint_handler(int signo, t_term *term);
// void	sigstp_handler(int signo, t_term *term);

void	ft_export(t_term *term, t_cmd *cmd);
void	ft_unset(t_term *term, t_cmd *cmd);
void	ft_env(t_term *term, t_cmd *cmd);
void	ft_pwd(t_term *term, t_cmd *cmd);
void	ft_cd(t_term *term, t_cmd *cmd);
void	ft_echo(t_term *term, t_cmd *cmd);
void	ft_exit(t_term *term, t_cmd *cmd);

#endif