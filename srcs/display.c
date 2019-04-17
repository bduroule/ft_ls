/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   display.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: beduroul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/01 20:31:14 by beduroul     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/01 20:31:17 by beduroul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

# include "ft_ls.h"

void max_size(t_recu *recu, t_max *max, t_option op)
{
    t_recu *tmp;

    tmp = recu;
    *max = (t_max){.s_max = 1, .l_max = 1, .g_max = 1, .u_max = 1,
    .mi_max = 1, .ma_max = 1, .t_block = 0};
    while (tmp)
    {
        if (ft_intsize(tmp->size) > (*max).s_max)
            (*max).s_max = ft_intsize(tmp->size);
        if (ft_intsize(tmp->link) > (*max).l_max)
            (*max).l_max = ft_intsize(tmp->link);
        if ((int)ft_strlen(tmp->group) > (*max).g_max)
            (*max).g_max = ft_strlen(tmp->group);
        if ((int)ft_strlen(tmp->user) > (*max).u_max)
            (*max).u_max = ft_strlen(tmp->user);
        if (ft_intsize(tmp->minor) > (*max).mi_max)
            (*max).mi_max = ft_intsize(tmp->minor);
        if (ft_intsize(tmp->major) > (*max).ma_max)
            (*max).ma_max = ft_intsize(tmp->major);
        if ((int)ft_strlen(tmp->group) > (*max).g_max)
            (*max).g_max = ft_strlen(tmp->group);
        (*max).t_block += tmp->block;
        tmp = (op.r ? tmp->prev : tmp->next);
    }
}


void    display(t_recu *r, t_option op)
{
    t_recu *tmp;
    
    if (op.r == 1)
        tmp = end_list(r);
    else
        tmp = r;
    if (op.l == 1)
        putls_l(tmp, op);
    else
        while (tmp)
        {
            ft_putendl(tmp->name);
            tmp = (op.r ? tmp->prev : tmp->next);

        }
    if (op.r_rec == 1)
        recu_path(op, r);
}
