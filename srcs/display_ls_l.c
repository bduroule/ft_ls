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

void    rspace(int nb, char *str)
{
    int i;

    i = -1;
    while (++i < nb)
        ft_strcat(str, " ");
}
static char    *put_min_maj(t_recu *rec, t_max max, char *str)
{
    char    *itoatmp;

    if (rec->perm[0] == 'b' || rec->perm[0] == 'c')
    {
        itoatmp = ft_itoa(rec->major);
        ft_strcat(str, itoatmp);
        free(itoatmp);
        ft_strcat(str, ",");
        rspace(max.mi_max - ft_intsize(rec->minor) + 1, str);
        itoatmp = ft_itoa(rec->minor);
        ft_strcat(str, itoatmp);
        free(itoatmp);
    }
    return (str);
}

static char    *put_size(t_recu *tmp, char *str, t_max max)
{
    char    *itoatmp;

    if (tmp->perm[0] != 'b' && tmp->perm[0] != 'c')
    {
        if (max.s_max < (max.mi_max + max.ma_max))
            rspace(((max.mi_max + max.ma_max) + 2) - ft_intsize(tmp->size) + 1, str);
        else
            rspace(max.s_max - ft_intsize(tmp->size) + 1, str);
        itoatmp = ft_itoa(tmp->size);
        ft_strcat(str, itoatmp);
        free(itoatmp);
    }
    else
    {
        if (max.s_max < (max.mi_max + max.ma_max))
            rspace(max.ma_max - ft_intsize(tmp->major) + 1, str);
        put_min_maj(tmp, max, str);
    }
    ft_strcat(str, " ");
    return (str);
}

static char    *put_link(t_recu *tmp, char *str)
{
    char *buff;

    buff = ft_strnew(PATH_MAX);
    readlink(tmp->path, buff, PATH_MAX);
    ft_strcat(str, " -> ");
    ft_strcat(str, buff);
    free(buff);
    return (str);
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
    
    if (!tmp)
        return;
    max_size(tmp, &max, op);    
    if (!tmp->single)
      put_total(max);

    char    wow[2048];
    char    *itoatmp;
    while (tmp)
    {
        ft_strcpy(wow, tmp->perm);
        rspace(max.l_max - ft_intsize(tmp->link) + 2, wow);
        itoatmp = ft_itoa(tmp->link);
        ft_strcat(wow, itoatmp);
        ft_strcat(wow, " ");
        ft_strcat(wow, tmp->user);
        rspace(max.u_max - ft_strlen(tmp->user) + 2, wow);
        ft_strcat(wow, tmp->group);
        rspace(max.g_max - ft_strlen(tmp->group) + 1, wow);
        put_size(tmp, wow, max);
        ft_strcat(wow, tmp->date);
        ft_strcat(wow, " ");
        color_name(tmp, wow, op);
        if (tmp->perm[0] == 'l')
            put_link(tmp, wow);
        ft_strcat(wow, "\n");;
        ft_putstr(wow);
        free(itoatmp);
        tmp = (op.r ? tmp->prev : tmp->next);

    }
}
