/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   display_ls_l.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: beduroul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/16 21:22:41 by beduroul     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 18:55:43 by beduroul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static char		*put_min_maj(t_recu *rec, t_max max, char *str)
{
	char	*itoatmp;

	if (rec->perm[0] == 'b' || rec->perm[0] == 'c')
	{
		if (!(itoatmp = ft_itoa(rec->major)))
			ls_error(rec->path, MALLOC);
		ft_strcat(str, itoatmp);
		free(itoatmp);
		ft_strcat(str, ",");
		rspace(max.mi_max - ft_intsize(rec->minor) + 1, str);
		itoatmp = ft_itoa(rec->minor);
		ft_strcat(str, itoatmp);
		free(itoatmp);
	}
	return (str);
}

char			*put_size(t_recu *tmp, char *s, t_max m)
{
	char	*itoatmp;

	if (tmp->perm[0] != 'b' && tmp->perm[0] != 'c')
	{
		if (m.s_max < (m.mi_max + m.ma_max))
			rspace(((m.mi_max + m.ma_max) + 2) - ft_intsize(tmp->size) + 1, s);
		else
			rspace(m.s_max - ft_intsize(tmp->size) + 1, s);
		if (!(itoatmp = ft_itoa(tmp->size)))
			ls_error(tmp->path, MALLOC);
		ft_strcat(s, itoatmp);
		free(itoatmp);
	}
	else
	{
		if (m.s_max < (m.mi_max + m.ma_max))
			rspace(m.ma_max - ft_intsize(tmp->major) + 1, s);
		put_min_maj(tmp, m, s);
	}
	ft_strcat(s, " ");
	return (s);
}

static char		*put_link(t_recu *tmp, char *str)
{
	char *buff;

	buff = ft_strnew(PATH_MAX);
	readlink(tmp->path, buff, PATH_MAX);
	ft_strcat(str, " -> ");
	ft_strcat(str, buff);
	free(buff);
	return (str);
}

static void		put_total(t_max max)
{
	ft_putstr("total ");
	ft_putnbr(max.t_block);
	write(1, "\n", 1);
}

void			putls_l(t_recu *tmp, t_option op, t_max max)
{
	char	wow[2048];

	if (!tmp)
		return ;
	if (!tmp->single)
		put_total(max);
	while (tmp)
	{
		ls_l_str(tmp, wow, max, op);
		color_name(tmp, wow, op);
		if (op.f_f || op.p)
		p_cat(tmp, wow, op);
		if (tmp->perm[0] == 'l')
			put_link(tmp, wow);
		ft_strcat(wow, "\n");
		ft_putstr(wow);
		tmp = (op.r ? tmp->prev : tmp->next);
	}
}
