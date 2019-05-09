/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: beduroul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/29 18:46:34 by beduroul     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 19:19:27 by beduroul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void		ls_error(char *s, int n)
{
	if (n == USAGE)
	{
		ft_putstr_fd("ft_ls: illegal option -- ", 2);
		ft_putstr_fd(s, 2);
		write(2, "\n", 1);
		write(2, "usage: ./ft_ls [-artRlSG1xnoimfFp] [file ...]\n", 46);
	}
	if (n == ERRNO || n == MALLOC)
	{
		ft_putstr_fd("ft_ls: ", 2);
		perror(s);
	}
	if (n == USAGE || n == MALLOC)
		exit(EXIT_FAILURE);
}

static void	option2(t_option *op, char **av, int i, int j)
{
	if (av[i][j] == '1')
		(*op).one = 1;
	if (av[i][j] == 'x')
		(*op).x = 1;
	if (av[i][j] == 'n')
		(*op).n = 1;
	if (av[i][j] == 'o')
		(*op).o = 1;
	if (av[i][j] == 'i')
		(*op).i = 1;
	if (av[i][j] == 'm')
		(*op).m = 1;
	if (av[i][j] == 'f')
	{
		(*op).a = 1;
		(*op).f = 1;
	}
	if (av[i][j] == 'F')
		(*op).f_f = 1;
	if (av[i][j] == 'p')
		(*op).p = 1;
}

static void	option(t_option *op, char **av, int i, int j)
{
	if (av[i][j] == 'l')
		(*op).l = 1;
	if (av[i][j] == 'a')
		(*op).a = 1;
	if (av[i][j] == 'R')
		(*op).r_rec = 1;
	if (av[i][j] == 'r')
		(*op).r = 1;
	if (av[i][j] == 't')
		(*op).t = 1;
	if (av[i][j] == 'S')
		(*op).s_size = 1;
	if (av[i][j] == 'G')
		(*op).g_color = 1;
	option2(op, av, i, j);
}

static int	parse_option(char **av, t_option *op, int i)
{
	int j;
	int c;

	i = 0;
	c = 0;
	while (av[++i])
	{
		j = 0;
		if (av[i][0] == '-' && av[i][1] == '-')
			return (i);
		if (av[i][0] == '-')
		{
			c = i;
			while (av[i][++j])
			{
				if (!(ft_strchr(OPTION, av[i][j])))
					ls_error(&av[i][j], USAGE);
				option(op, av, i, j);
			}
		}
	}
	return (c);
}

int			main(int ac, char **av)
{
	t_option	op;
	int			i;

	op = (t_option){.a = 0, .r = 0, .t = 0, .r_rec = 0, .l = 0, .s_size = 0,
	.g_color = 0, .one = 0, .x = 0, .n = 0, .o = 0, .i = 0, .m = 0, .f = 0,
	.f_f = 0, .p = 0};
	i = -1;
	i = parse_option(av, &op, i);
	if (!op.f)
		av = sort_av(ac, av, i, op);
	parse_path(av, op, i, (ac - 1) - i);
	return (0);
}
