/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sort_param.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: beduroul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/06 20:38:20 by beduroul     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/09 20:51:07 by beduroul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static int	size_op(t_stat *f1, t_stat *f2, char *s1, char *s2)
{
	if (f1->st_size == f2->st_size)
		return (ft_strcmp(s1, s2));
	else if (f1->st_size > f2->st_size)
		return (-1);
	else
		return (1);
}

static int	time_sort(t_stat *f1, t_stat *f2, char *s1, char *s2)
{
	if (f1->st_mtime == f2->st_mtime)
		return (ft_strcmp(s1, s2));
	else if (f1->st_mtime > f2->st_mtime)
		return (-1);
	else
		return (1);
}

int			cmp_value(char *s1, char *s2, t_option op)
{
	t_stat *f1;
	t_stat *f2;

	if (!(f1 = (t_stat *)malloc(sizeof(t_stat))))
		return (0);
	if (!(f2 = (t_stat *)malloc(sizeof(t_stat))))
		return (0);
	if ((lstat(s1, f1) < 0))
		ls_error(s1, ERRNO);
	if ((lstat(s2, f2) < 0))
		ls_error(s2, ERRNO);
	if (op.s_size)
		return (size_op(f1, f2, s1, s2));
	else if (op.t)
		return (time_sort(f1, f2, s1, s2));
	return (ft_strcmp(s1, s2));
	free(f1);
	free(f2);
}
