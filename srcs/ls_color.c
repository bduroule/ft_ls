/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ls_color.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: beduroul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/29 20:40:52 by beduroul     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 20:40:54 by beduroul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void	put_name2(t_recu *tmp)
{
	if (tmp->perm[3] == 's')
		ft_putstr_color(tmp->name, "\e[30;41m");
	else if (tmp->perm[6] == 's')
		ft_putstr_color(tmp->name, "\e[30;46m");
	else if (tmp->perm[9] == 't')
		ft_putstr_color(tmp->name, "\e[31m");
}

void	put_name(t_recu *tmp, t_option op)
{
	if (!op.g_color)
	{
		ft_putstr(tmp->name);
		return ;
	}
	if (tmp->perm[0] == 'c')
		ft_putstr_color(tmp->name, "\e[34;43m");
	else if (tmp->perm[0] == 'b')
		ft_putstr_color(tmp->name, "\e[34;48;5;45m");
	else if (tmp->perm[0] == 'l')
		ft_putstr_color(tmp->name, "\e[35m");
	else if (ft_strchr(tmp->perm, '-') == NULL)
		ft_putstr_color(tmp->name, "\e[43;30m");
	else if (tmp->perm[0] == 'd')
		ft_putstr_color(tmp->name, "\e[96m");
	else if (tmp->perm[3] == 's' || tmp->perm[6] == 's' || tmp->perm[9] == 't')
		put_name2(tmp);
	else if (tmp->perm[3] == 'x' && tmp->perm[6] == 'x' && tmp->perm[9] == 'x')
		ft_putstr_color(tmp->name, "\e[31m");
	else
		ft_putstr(tmp->name);
	if (op.one)
		write(1, "\n", 1);
}

char	*color_name(t_recu *tmp, char *str, t_option op)
{
	if (!op.g_color)
		return (ft_strcat(str, tmp->name));
	else if (tmp->perm[0] == 'c')
		color_txt(str, tmp->name, "\e[34;43m");
	else if (tmp->perm[0] == 'b')
		color_txt(str, tmp->name, "\e[34;48;5;45m");
	else if (tmp->perm[0] == 'l')
		color_txt(str, tmp->name, "\e[35m");
	else if (ft_strchr(tmp->perm, '-') == NULL)
		color_txt(str, tmp->name, "\e[43;30m");
	else if (tmp->perm[0] == 'd')
		color_txt(str, tmp->name, "\e[96m");
	else if (tmp->perm[3] == 's')
		color_txt(str, tmp->name, "\e[30;41m");
	else if (tmp->perm[6] == 's')
		color_txt(str, tmp->name, "\e[30;46m");
	else if (tmp->perm[9] == 't')
		color_txt(str, tmp->name, "\e[31m");
	else if (tmp->perm[3] == 'x' && tmp->perm[6] == 'x' && tmp->perm[9] == 'x')
		color_txt(str, tmp->name, "\e[31m");
	else
		ft_strcat(str, tmp->name);
	return (str);
}
