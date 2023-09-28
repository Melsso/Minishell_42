/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:05:52 by smallem           #+#    #+#             */
/*   Updated: 2023/09/28 15:54:09 by smallem          ###   ########.fr       */
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

typedef struct s_cmd t_cmd;
typedef struct s_cmd
{
	int		fd_in;
	int		fd_out;
	int		fd[2];
	char	**args;
	char	*path;
}	t_cmd;

int	ex_stat;


void 	print_tree(t_tree* root);
void	init_s(t_term *term, char *input);
char	**copy_env(char **env, t_term *term);
char	**splt(char *input, t_term *term);
int 	check_input(char *input, t_term *term);
int		count_pipes(t_term *term);
int		check_charset(char c);
char	*get_path(t_term *term, char *cmd);
t_cmd	*build_cmd(t_term *term, t_tree **node);

void	init_cmd(t_term *term);
void	execute(t_tree *node, char **env);


#endif