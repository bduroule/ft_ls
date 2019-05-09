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

void	recu_path(t_option op, t_recu *r)
{
	t_recu		*tmp;

	tmp = (op.r ? end_list(r) : r);
	while (tmp)
	{
		if (tmp->perm[0] == 'd' &&
			(tmp->name[0] != '.' && tmp->name[1] != '.'))
		{
			ft_putchar('\n');
			ft_putstr(tmp->path);
			ft_putendl(":");
			read_path(op, tmp->right, tmp->path);
		}
		tmp = (op.r ? tmp->prev : tmp->next);
	}
}

char	*iterate_line(t_recu *list, t_max cmax, int nb, t_option op)
{
	int		i;
	int		c;

	c = 1;
	i = 0;
	while (list)
	{
		if (i == nb)
		{
			if (op.i)
			{
				ft_putnbr(list->neod);
				ft_putspace(cmax.i_max - ft_intsize(list->neod) + 1);
			}
			put_name(list, op);
			if (c < (cmax.th_max) && list->next)
				ft_putspace(cmax.n_max - ft_strlen(list->name) + 1);
			c++;
			nb += cmax.c_max;
		}
		i++;
		list = list->next;
	}
	return (NULL);
}

void	put_column(t_recu *list, t_max cmax, t_option op)
{
	int		i;

	i = -1;
	while (++i < cmax.c_max)
	{
		iterate_line(list, cmax, i, op);
		ft_putchar('\n');
	}
}

void	put_column_x(t_recu *list, t_max cmax, t_option op)
{
	int		i;
	t_recu	*tmp;

	tmp = list;
	i = 0;
	while (tmp)
	{
		if (op.i)
		{
			ft_putnbr(tmp->neod);
			ft_putspace(cmax.i_max - ft_intsize(tmp->neod) + 1);
		}
		put_name(tmp, op);
		if (i + 1 < cmax.th_max && tmp->next != NULL)
			ft_putspace(cmax.n_max - ft_strlen(tmp->name) + 1);
		i++;
		if (i >= cmax.th_max)
		{
			write(1, "\n", 1);
			i = 0;
		}
		tmp = (op.r ? tmp->prev : tmp->next);
	}
	write(1, "\n", 1);
}

void	display(t_recu *r, t_option op)
{
	t_recu	*tmp;
	t_max	cmax;

	max_size(r, &cmax, op);
	tmp = op.r ? end_list(r) : r;
	if (op.one)
		put_one(tmp, cmax, op);
	else if (op.m)
		put_m(tmp, cmax, op);
	else if (op.x)
		put_column_x(tmp, cmax, op);
	else if (op.l || op.n || op.o)
		putls_l(tmp, op, cmax);
	else
		put_column(tmp, cmax, op);
	if (op.r_rec == 1)
		recu_path(op, r);
}
