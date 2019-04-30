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

t_recu	*sort_column(t_recu *list, t_max max)
{
	int i;
	int j;
	t_recu *tmp;
	t_recu *dest;

	i = 0;
	j = 0;
	tmp = list;
	dprintf(1, "%d || %d\n", i, max.c_max);
	while (i < max.c_max)
	{
		
		if (tmp == NULL)
		{
			tmp = list;
			tmp = n_next(&tmp, ++i);
		}
		dest = tmp;
		dest->next = NULL;

		tmp = n_next(&tmp, max.c_max);
		dest = dest->next;
	}
	return (dest);
}

void	put_column(t_recu *list, t_max max, t_option op)
{
	int i;
	t_recu *tmp;

	tmp = sort_column(list, max);
	i = 0;
	while (tmp)
	{
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
	.mi_max = -1, .ma_max = -1, .t_block = 0, .n_max = 1, .t_max = 1, .n_name = 1};
	ioctl(0, TIOCGWINSZ, &term);
	(*max).t_max = term.ws_col;
	while (tmp)
	{
		if ((tmp->perm[0] == 'b' || tmp->perm[0] == 'c') && (*max).ma_max == -1
		&& (*max).mi_max == -1)
		{
			(*max).mi_max = 1;
			(*max).ma_max = 1;
		}
		max_len(tmp, max);
		count++;
		tmp = (op.r ? tmp->prev : tmp->next);
	}
	(*max).n_name = count;
	(*max).t_max /= (*max).n_max;
	(*max).c_max = ft_up_rounded((double)(*max).n_name / (*max).t_max);
}

void	display(t_recu *r, t_option op)
{
	t_recu *tmp;
	t_max max;

	max_size(r, &max, op);
	tmp = op.r ? end_list(r) : r;
	if (op.one)
		while (tmp)
		{
			op.g_color ? put_name(tmp, op) : ft_putendl(tmp->name);
			tmp = (op.r ? tmp->prev : tmp->next);
		}
	else if (op.l == 1)
		putls_l(tmp, op, max);
	else
		put_column(tmp, max, op);
	if (op.r_rec == 1)
		recu_path(op, r);
}
