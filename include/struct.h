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

#ifndef STRUCT_H
# define STRUCT_H

# include <limits.h>

typedef struct stat		t_stat;
typedef struct dirent	t_dirent;
typedef struct winsize	t_winsize;

typedef struct			s_option
{
	short int			a;
	short int			r;
	short int			r_rec;
	short int			l;
	short int			t;
	short int			s_size;
	short int			g_color;
	short int			one;
	short int			x;
	short int			n;
	short int			o;
	short int			i;
	short int			m;
	short int			f;
	short int			f_f;
	short int			p;
	short int			u;
	short int			c;
	char				*path;
}						t_option;

typedef struct			s_recu
{
	int					id;
	char				path[PATH_MAX];
	char				perm[12];
	int					link;
	char				*user;
	char				*group;
	long int			size;
	char				*date;
	time_t				time;
	char				test;
	char				name[NAME_MAX];
	int					block;
	int					minor;
	int					major;
	short int			single;
	int					neod;
	struct s_recu		*next;
	struct s_recu		*prev;
	struct s_recu		*right;
}						t_recu;

typedef struct			s_max
{
	short int			l_max;
	short int			s_max;
	short int			g_max;
	short int			u_max;
	short int			mi_max;
	short int			ma_max;
	short int			n_max;
	short int			th_max;
	short int			t_block;
	short int			c_max;
	short int			i_max;
	int					te_max;
	int					n_name;
}						t_max;

typedef struct			s_index
{
	int					i;
	int					j;
	int					n;
}						t_index;

#endif
