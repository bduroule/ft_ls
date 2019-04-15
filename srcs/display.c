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

static void max_size(t_recu *recu, t_max *max)
{
    t_recu *tmp;

    tmp = recu;
    (*max).s_max = 1;
    (*max).l_max = 1;
    (*max).g_max = 1;
    (*max).u_max = 1;
    (*max).mi_max = 1;
    (*max).t_block = 0;
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
        (*max).t_block += tmp->block;
        tmp = tmp->next;
    }
}

static void    put_min_maj(t_recu *rec, t_max max)
{
    if (rec->perm[0] == 'b' || rec->perm[0] == 'c')
    {
        ft_putnbr(rec->major);
        ft_putspace(max.mi_max - ft_intsize(rec->major) + 2);
        ft_putchar(',');
        ft_putnbr(rec->minor);
    }

}

static void    putls_l(t_recu *tmp, t_option op)
{
    t_max max;

    max_size(tmp, &max);
    if (!tmp->single)
    {
        ft_putstr("total ");
        ft_putnbr(max.t_block);
        write(1, "\n", 1);
    }
    while (tmp)
    {
        ft_putstr(tmp->perm);
        ft_putspace(max.l_max - ft_intsize(tmp->link) + 2);
        ft_putnbr(tmp->link);
        write(1, " ", 1);
        ft_putstr(tmp->user);
        ft_putspace(max.u_max - ft_strlen(tmp->user) + 2);
        ft_putstr(tmp->group);
        ft_putspace(max.s_max - ft_intsize(tmp->size) + 2);
        if (tmp->perm[0] != 'b' && tmp->perm[0] != 'c')
            ft_putnbr(tmp->size);
        else
            put_min_maj(tmp, max);
        write(1, " ", 1);
        ft_putstr(tmp->date);
        write(1, " ", 1);
        ft_putendl(tmp->name);
        if (op.r == 1)
            tmp = tmp->prev;
        else
            tmp = tmp->next;
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
            if (op.r == 1)
                tmp = tmp->prev;
            else
                tmp = tmp->next;
        }
    if (op.r_rec == 1)
        recu_path(op, r);
}
