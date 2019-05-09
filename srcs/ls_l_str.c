/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ls_l_str.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: beduroul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/29 19:39:49 by beduroul     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 19:39:55 by beduroul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void		term_size(t_max *max, int count)
{
	(*max).n_name = count;
	(*max).th_max = (*max).te_max / ((*max).n_max + (*max).i_max + 1);
	(*max).c_max = ft_up_rounded((double)(*max).n_name / (*max).th_max);
}

char		**sort_av(int ac, char **av, int index, t_option op)
{
	int i;
	int j;
	int d;

	i = index;
	d = ac - 1;
	while (++i < ac - 1)
	{
		j = i;
		while (++j < ac)
			if (cmp_value(av[i], av[j], op) < 0)
				ft_avswap(&av[i], &av[j]);
	}
	i = index + 1;
	while (d > i)
	{
		ft_avswap(&av[i], &av[d]);
		i++;
		d--;
	}
	return (av);
}

void		max_len(t_recu *tmp, t_max *max, t_option op)
{
	if (ft_intsize(tmp->size) > (*max).s_max)
		(*max).s_max = ft_intsize(tmp->size);
	if (ft_intsize(tmp->link) > (*max).l_max)
		(*max).l_max = ft_intsize(tmp->link);
	if ((int)ft_strlen(tmp->group) > (*max).g_max)
		(*max).g_max = ft_strlen(tmp->group);
	if ((int)ft_strlen(tmp->user) > (*max).u_max)
		(*max).u_max = ft_strlen(tmp->user);
	if ((tmp->perm[0] == 'b' || tmp->perm[0] == 'c') &&
	ft_intsize(tmp->minor) > (*max).mi_max)
		(*max).mi_max = ft_intsize(tmp->minor);
	if ((tmp->perm[0] == 'b' || tmp->perm[0] == 'c') &&
	ft_intsize(tmp->major) > (*max).ma_max)
		(*max).ma_max = ft_intsize(tmp->major);
	if ((int)ft_strlen(tmp->group) > (*max).g_max)
		(*max).g_max = ft_strlen(tmp->group);
	if ((int)ft_strlen(tmp->name) > (*max).n_max)
		(*max).n_max = ft_strlen(tmp->name);
	if (op.i && ft_intsize(tmp->neod) > (*max).i_max)
		(*max).i_max = ft_intsize(tmp->neod);
	(*max).t_block += tmp->block;
}

void		max_size(t_recu *recu, t_max *max, t_option op)
{
	t_recu		*tmp;
	t_winsize	term;
	int			count;

	tmp = recu;
	count = 0;
	*max = (t_max){.s_max = 1, .l_max = 1, .g_max = 1, .u_max = 1, .c_max = 1,
	.mi_max = -1, .ma_max = -1, .t_block = 0, .n_max = 1, .th_max = 1,
	.i_max = 0, .te_max = 0, .n_name = 0};
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
	term_size(max, count);
}

void		ls_l_str(t_recu *tmp, char *str, t_max max, t_option op)
{
	char	*itoatmp;

	itoatmp = NULL;
	if (op.i)
		option_i(itoatmp, tmp, max, str);
	else
		ft_strcpy(str, tmp->perm);
	rspace(max.l_max - ft_intsize(tmp->link) + 1, str);
	if (!(itoatmp = ft_itoa(tmp->link)))
		ls_error(tmp->path, MALLOC);
	ft_strcat(str, itoatmp);
	ft_strcat(str, " ");
	ft_strcat(str, tmp->user);
	rspace(max.u_max - ft_strlen(tmp->user) + 1, str);
	if (!op.o)
	{
		ft_strcat(str, " ");
		ft_strcat(str, tmp->group);
		rspace(max.g_max - ft_strlen(tmp->group) + 1, str);
	}
	put_size(tmp, str, max);
	ft_strcat(str, tmp->date);
	ft_strcat(str, " ");
	free(itoatmp);
}
