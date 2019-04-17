/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   display_ls_l.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: beduroul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/16 21:22:41 by beduroul     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 21:22:43 by beduroul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

# include "ft_ls.h"

static void    put_min_maj(t_recu *rec, t_max max)
{
    if (rec->perm[0] == 'b' || rec->perm[0] == 'c')
    {
        ft_putnbr(rec->major);
        ft_putchar(',');
        ft_putspace(max.mi_max - ft_intsize(rec->minor) + 1);
        ft_putnbr(rec->minor);
    }
}

static void    put_size(t_recu *tmp, t_option op, t_max max)
{
    (void)op;
    if (tmp->perm[0] != 'b' && tmp->perm[0] != 'c')
    {
        if (max.s_max < (max.mi_max + max.ma_max))
            ft_putspace(((max.mi_max + max.ma_max) + 2)- ft_intsize(tmp->size) + 1);
        else
            ft_putspace(max.s_max - ft_intsize(tmp->size) + 1);
        ft_putnbr(tmp->size);
    }
    else
    {
        if (max.s_max < (max.mi_max + max.ma_max))
            ft_putspace(max.ma_max - ft_intsize(tmp->major) + 1);
        put_min_maj(tmp, max);
    }
}

static void    put_link(t_recu *tmp)
{
    char *buff;

    buff = ft_strnew(PATH_MAX);
    readlink(tmp->path, buff, PATH_MAX);
    ft_putstr(" -> ");
    ft_putstr(buff);
    free(buff);

}

static void     put_total(t_max max)
{
    ft_putstr("total ");
    ft_putnbr(max.t_block);
    write(1, "\n", 1);
}

void    putls_l(t_recu *tmp, t_option op)
{
    t_max max;

    max_size(tmp, &max, op);
    if (!tmp)
        return;
    if (!tmp->single)
      put_total(max);
    while (tmp)
    {
        ft_putstr(tmp->perm);
        ft_putspace(max.l_max - ft_intsize(tmp->link) + 2);
        ft_putnbr(tmp->link);
        write(1, " ", 1);
        ft_putstr(tmp->user);
        ft_putspace(max.u_max - ft_strlen(tmp->user) + 2);
        ft_putstr(tmp->group);
        ft_putspace(max.g_max - ft_strlen(tmp->group) + 1);
        put_size(tmp, op, max);
        write(1, " ", 1);
        ft_putstr(tmp->date);
        write(1, " ", 1);
        ft_putstr(tmp->name);
        if (tmp->perm[0] == 'l')
            put_link(tmp);
        write(1, "\n", 1);
        tmp = (op.r ? tmp->prev : tmp->next);

    }
}
