/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 21:16:40 by smallem           #+#    #+#             */
/*   Updated: 2023/12/03 17:59:09 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_MALLOC_H
# define MY_MALLOC_H

# include <stdlib.h>

typedef struct s_mem	t_mem;

typedef struct s_mem
{
	void	*ptr;
	size_t	size;
	t_mem	*next;
}	t_mem;
void	free_lst(t_mem **lst);
void	*my_malloc(t_mem **lst, size_t size);

#endif