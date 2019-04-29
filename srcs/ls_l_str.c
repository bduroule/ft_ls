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

void	max_len(t_recu *tmp, t_max *max)
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
	(*max).t_block += tmp->block;
}

void	ls_l_str(t_recu *tmp, char *str, t_max max)
{
	char	*itoatmp;

	ft_strcpy(str, tmp->perm);
	rspace(max.l_max - ft_intsize(tmp->link) + 1, str);
	if (!(itoatmp = ft_itoa(tmp->link)))
		ls_error(tmp->path, MALLOC);
	ft_strcat(str, itoatmp);
	ft_strcat(str, " ");
	ft_strcat(str, tmp->user);
	rspace(max.u_max - ft_strlen(tmp->user) + 2, str);
	ft_strcat(str, tmp->group);
	rspace(max.g_max - ft_strlen(tmp->group) + 1, str);
	put_size(tmp, str, max);
	ft_strcat(str, tmp->date);
	ft_strcat(str, " ");
	free(itoatmp);
}
