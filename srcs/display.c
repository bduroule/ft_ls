/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   display.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: beduroul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/01 20:31:14 by beduroul     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 18:51:06 by beduroul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

char	*iterate_line(t_recu *list, t_max max, int nb, t_option op)
{
	int i;
	int c;

	c = 1;
	i = 0;
	while (list)
	{
		if (i == nb)
		{	
			if (op.i)
			{
				ft_putnbr(list->neod);
				ft_putspace(max.i_max - ft_intsize(list->neod) + 1);
			}
			ft_putstr(list->name);
			if (c < max.t_max && list->next)
				ft_putspace(max.n_max - ft_strlen(list->name) + 1);
			c++;
			nb += max.c_max;
		}
		i++;
		list = list->next;
	}
	return (NULL);
}

void	put_column(t_recu *list, t_max max, t_option op)
{
	int		i;

	i = -1;
	while (++i < max.c_max)
	{
		iterate_line(list, max, i, op);
		ft_putchar('\n');
	}
}

void	put_column_x(t_recu *list, t_max max, t_option op)
{
	int i;
	t_recu *tmp;

	tmp = list;
	i = 0;
	while (tmp)
	{
		if (op.i)
		{
			ft_putnbr(tmp->neod);
			ft_putspace(max.i_max - ft_intsize(tmp->neod) + 1);
		}
		put_name(tmp, op);
		if (i + 1 < max.t_max && tmp->next != NULL)
			ft_putspace(max.n_max - ft_strlen(tmp->name) + 1);
		i++;
		if (i >= max.t_max)
		{
			write(1, "\n", 1);
			i = 0;
		}
		tmp = (op.r ? tmp->prev : tmp->next);
	}
	write(1, "\n", 1);
}

void	max_size(t_recu *recu, t_max *max, t_option op)
{
	t_recu *tmp;
	t_winsize term;
	int count;

	tmp = recu;
	count = 0;
	*max = (t_max){.s_max = 1, .l_max = 1, .g_max = 1, .u_max = 1, .c_max = 1,
	.mi_max = -1, .ma_max = -1, .t_block = 0, .n_max = 1, .t_max = 1, .i_max = 0};
	ioctl(0, TIOCGWINSZ, &term);
	(*max).te_max = term.ws_col;
	while (tmp)
	{
		if ((tmp->perm[0] == 'b' || tmp->perm[0] == 'c') && (*max).ma_max == -1
		&& (*max).mi_max == -1)
		{
			(*max).mi_max = 1;
			(*max).ma_max = 1;
		}
		max_len(tmp, max, op);
		count++;
		tmp = (op.r ? tmp->prev : tmp->next);
	}
	(*max).n_name = count;
	(*max).t_max = (*max).te_max / ((*max).n_max + (*max).i_max + 1);
	(*max).c_max = ft_up_rounded((double)(*max).n_name / (*max).t_max);
}

void	display(t_recu *r, t_option op)
{
	t_recu *tmp;
	t_max max;

	max_size(r, &max, op);
	tmp = op.r ? end_list(r) : r;
	if (op.one)
		put_one(tmp, max, op);
	else if (op.m)
		put_m(tmp, max, op);
	else if (op.x)
		put_column_x(tmp, max, op);
	else if (op.l || op.n || op.o)
		putls_l(tmp, op, max);
	else
		put_column(tmp, max, op);
	if (op.r_rec == 1)
		recu_path(op, r);
}
