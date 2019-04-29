/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   list.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: beduroul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/15 14:48:02 by beduroul     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 19:05:21 by beduroul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

t_recu		*end_list(t_recu *list)
{
	while (list->next)
		list = list->next;
	return (list);
}

void		free_list(t_recu **list)
{
	t_recu *tmp;

	while ((*list))
	{
		free((*list)->group);
		free((*list)->user);
		free((*list)->date);
		tmp = (*list)->next;
		free((*list));
		*list = tmp;
	}
}

void		init_rev(t_recu **rec)
{
	t_recu *tmp;
	t_recu *prev;

	if (!*rec)
		return ;
	tmp = *rec;
	while (tmp->next)
	{
		prev = tmp;
		tmp = tmp->next;
		tmp->prev = prev;
	}
}

int			check_sigle(char **av, int i, struct stat *buff)
{
	int c;

	c = 0;
	while (av[i])
	{
		if (lstat(av[i], buff) < 0)
			ls_error(av[i], ERRNO);
		if (type_file(buff) == 'l' || type_file(buff) == '-')
			c = 1;
		i++;
	}
	return (c);
}

void		sigle_file(char **av, int i, struct stat *buff, t_option op)
{
	t_recu *list;

	list = NULL;
	while (av[i])
	{
		if (lstat(av[i], buff) < 0)
			;
		else if ((type_file(buff) == 'l') || type_file(buff) == '-')
			pars_sigle(&list, op, av[i], buff);
		i++;
	}
	init_rev(&list);
	display(list, op);
	free_list(&list);
}
