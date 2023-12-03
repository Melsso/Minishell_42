/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:53:13 by smallem           #+#    #+#             */
/*   Updated: 2023/12/03 12:15:07 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include "../../include/my_malloc.h"
# include <sys/types.h>

enum e_token
{
	TK_CMD,
	TK_PL,
};

typedef struct s_list	t_list;

typedef struct s_list
{
	void		*content;
	t_list		*next;
}				t_list;

typedef struct s_tree	t_tree;

typedef struct s_tree
{
	enum e_token	type;
	void			*content;
	int				err;
	t_tree			*r;
	t_tree			*l;
}	t_tree;

typedef struct s_term	t_term;

typedef struct s_term
{
	int		nb_pipes;
	char	*input;
	t_tree	*ast;
	char	**env;
	t_mem	*mem_lst;
	int		ex_stat;
}	t_term;

int			ft_isdigit(int c);
int			ft_isascii(int c);
int			ft_isalpha(int c);
int			ft_isprint(int c);
int			ft_tolower(int c);
int			ft_toupper(int c);
int			ft_isalnum(int c);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_calloc(size_t nmemb, size_t size, t_term *term);
void		*ft_memset(void *s, int c, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
char		*ft_strdup(const char *str, t_term *term);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
void		*ft_memchr(const void *s, int c, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
int			ft_atoi(const char *nptr);
char		*ft_strrchr(const char *s, int c);
char		*ft_strchr(const char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlen(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len,
				t_term *term);
char		*ft_strjoin(char const *s1, char const *s2, t_term *term);
char		*ft_strtrim(char const *s1, char const *set, t_term *term);
char		**ft_split(char const *s, char c, t_term *term);
char		*ft_itoa(int n, t_term *term);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
t_list		*ft_lstnew(void *content, t_term *term);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
