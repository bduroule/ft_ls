/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   option.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: beduroul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 19:00:30 by beduroul     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/09 20:52:42 by beduroul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

char	*option_i(char *itoatmp, t_recu *tmp, t_max max, char *str)
{
	itoatmp = ft_itoa(tmp->neod);
	ft_strcpy(str, itoatmp);
	rspace(max.i_max - ft_intsize(tmp->neod) + 1, str);
	ft_strcat(str, tmp->perm);
	return (str);
}

void	p_cat(t_recu *list, char *str, t_option op)
{
	(void)op;
	if (list->perm[0] == 'd')
		ft_strcat(str, "/");
	if (!op.p && list->perm[0] == 'l')
		ft_strcat(str, "@");
	if (!op.p && list->perm[0] == 'p')
		ft_strcat(str, "|");
	if (list->perm[0] == '-' && list->perm[3] == 'x' && list->perm[6] == 'x'
			&& list->perm[9] == 'x' && !op.p)
		ft_strcat(str, "*");
}

void	put_m(t_recu *list, t_max max, t_option op)
{
	int c;

	c = 0;
	while (list)
	{
		if (op.i)
		{
			ft_putnbr(list->neod);
			ft_putspace(1);
		}
		c += ft_strlen(list->name) + 2;
		if (list->next && (int)ft_strlen(list->next->name) + 3 + c >=
		max.te_max)
		{
			write(1, "\n", 1);
			c = 0;
		}
		ft_putstr(list->name);
		if (list->next)
			ft_putstr(", ");
		else
			putchar('\n');
		list = (op.r ? list->prev : list->next);
	}
}

void	put_one(t_recu *list, t_max max, t_option op)
{
	while (list)
	{
		if (op.i)
		{
			ft_putnbr(list->neod);
			ft_putspace(max.i_max - ft_intsize(list->neod) + 1);
		}
		op.g_color ? put_name(list, op) : ft_putendl(list->name);
		list = (op.r ? list->prev : list->next);
	}
}
