/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:05:52 by smallem           #+#    #+#             */
/*   Updated: 2023/09/07 17:55:37 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libs/libft/libft.h"
#include "my_malloc.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include <signal.h>
#include <termios.h>

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
enum e_token
{
	TK_CMD,
	TK_PL,
	TK_RED,
	TK_ARGS,
};

typedef struct s_cmd t_cmd;
typedef struct s_cmd
{
	int		fd_in;
	int		fd_out;
	int		fd[2];
	char	**args;
	char	*path;
}	t_cmd;

typedef struct s_tree t_tree;
typedef struct s_tree
{
	enum e_token	type;
	void			*content;
	t_tree			*r;
	t_tree			*l;
}	t_tree;

typedef struct s_term
{
	int		nb_pipes;
	t_tree	*ast;
	char	**env;
	pid_t	*pids;
	t_mem	*mem_lst;
}	t_term;
typedef struct s_term t_term;

int	ex_stat;


void 	print_tree(t_tree* root);
void	init_s(t_term *term, char *input);
char	**copy_env(char **env);
char	**splt(char *input);

#endif