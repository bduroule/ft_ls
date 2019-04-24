/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   struct.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: beduroul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/02 19:07:22 by beduroul     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/02 19:07:23 by beduroul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

# ifndef STRUCT_H
#define STRUCT_H

# include <limits.h>

typedef struct	s_option
{
	short int	a;
	short int	r;
	short int	r_rec;
	short int	l;
	short int	t;
	short int	s_size;
	short int	g_color;
	char		*path;
}            	t_option;

typedef struct	s_recu
{
	int			id;
	char		path[PATH_MAX];
	char		perm[11];
	int 		link;
	char		*user;
	char		*group;
	long int 	size;
	char		*date;
	time_t		time;
    char         test;
	char		name[NAME_MAX];
	int			block;
	int			minor;
	int			major;
	short int	single;
	struct		s_recu *next;
	struct		s_recu *prev;
	struct		s_recu *right;
}				t_recu;

typedef struct s_max
{
	short int	l_max;
	short int	s_max;
	short int	g_max;
	short int	u_max;
	short int	mi_max;
	short int	ma_max;
	short int	t_block;
}				t_max;

typedef struct s_index
{
	int			i;
	int			j;
	int			n;
}				t_index;

# endif
