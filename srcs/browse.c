/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   browse.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: beduroul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/16 17:05:53 by beduroul     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 18:48:53 by beduroul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void	rev_parth(t_index index, t_option op, char **av, t_stat *buff)
{
	t_recu *list;

	list = NULL;
	index.j = ft_avlen(av) - 1;
	while (index.i < index.j)
	{
		if (lstat(av[index.j], buff) < 0)
			;
		if ((type_file(buff) == 'l' && op.l) || type_file(buff) == '-')
			;
		else
		{
			if (index.n > 1)
			{
				ft_putchar('\n');
				ft_putstr(av[index.j]);
				ft_putendl(":");
			}
			read_path(op, list, av[index.j]);
		}
		index.j--;
	}
}

void	browse_path(t_index index, t_option op, char **av, t_stat *buff)
{
	t_recu *list;

	list = NULL;
	while (av[++(index).i])
	{
		if ((lstat(av[index.i], buff) < 0))
			;
		else if ((type_file(buff) == 'l' && op.l) || type_file(buff) == '-')
			;
		else
		{
			if (index.n > 1)
			{
				ft_putchar('\n');
				ft_putstr(av[index.i]);
				ft_putendl(":");
			}
			read_path(op, list, av[index.i]);
		}
	}
}

void	parse_path(char **av, t_option op, int i, int n)
{
	t_recu	*list;
	t_stat	*buff;
	t_index	index;

	index = (t_index){.i = i, .j = 0, .n = n};
	list = NULL;
	if (!(buff = malloc(sizeof(*buff))))
		return ;
	if (n == 0)
	{
		read_path(op, list, ".");
		free(buff);
		return ;
	}
	if (check_sigle(av, i + 1, buff))
		sigle_file(av, i + 1, buff, op);
	if (op.r)
		rev_parth(index, op, av, buff);
	else
		browse_path(index, op, av, buff);
	free(buff);
}
