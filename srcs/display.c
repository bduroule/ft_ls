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

void    put_name(t_recu *tmp)
{
    if (tmp->perm[0] == 'c')
        ft_putendl_color(tmp->name, "\e[34;43m");
    else if (tmp->perm[0] == 'b')
        ft_putendl_color(tmp->name, "\e[34;48;5;45m");
    else if (tmp->perm[0] == 'l')
        ft_putendl_color(tmp->name, "\e[35m");
    else if (ft_strchr(tmp->perm, '-') == NULL)
        ft_putendl_color(tmp->name, "\e[43;30m");
    else if (tmp->perm[0] == 'd')
        ft_putendl_color(tmp->name, "\e[96m");
    else if (tmp->perm[3] == 's')
        ft_putendl_color(tmp->name, "\e[30;41m");
    else if (tmp->perm[6] == 's')
        ft_putendl_color(tmp->name, "\e[30;46m");
    else if (tmp->perm[9] == 't')
        ft_putendl_color(tmp->name, "\e[31m");
    else if (tmp->perm[3] == 'x' && tmp->perm[6] == 'x' && tmp->perm[9] == 'x')
        ft_putendl_color(tmp->name, " \e[31m");
    else
        ft_putendl(tmp->name);
}

char *color_name(t_recu *tmp, char *str, t_option op)
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
        color_txt(str, tmp->name, " \e[31m");
    else
        ft_strcat(str, tmp->name);
        return (str);
}

void max_size(t_recu *recu, t_max *max, t_option op)
{
    t_recu *tmp;

    tmp = recu;
    *max = (t_max){.s_max = 1, .l_max = 1, .g_max = 1, .u_max = 1,
    .mi_max = -1, .ma_max = -1, .t_block = 0};
    while (tmp)
    {
        if ((tmp->perm[0] == 'b' || tmp->perm[0] == 'c') && (*max).ma_max == -1 && (*max).mi_max == -1)
        {
            (*max).mi_max = 1;
            (*max).ma_max = 1;
        }
        if (ft_intsize(tmp->size) > (*max).s_max)
            (*max).s_max = ft_intsize(tmp->size);
        if (ft_intsize(tmp->link) > (*max).l_max)
            (*max).l_max = ft_intsize(tmp->link);
        if ((int)ft_strlen(tmp->group) > (*max).g_max)
            (*max).g_max = ft_strlen(tmp->group);
        if ((int)ft_strlen(tmp->user) > (*max).u_max)
            (*max).u_max = ft_strlen(tmp->user);
        if ((tmp->perm[0] == 'b' || tmp->perm[0] == 'c') && ft_intsize(tmp->minor) > (*max).mi_max)
            (*max).mi_max = ft_intsize(tmp->minor);
        if ((tmp->perm[0] == 'b' || tmp->perm[0] == 'c') && ft_intsize(tmp->major) > (*max).ma_max)
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
            op.g_color ? put_name(tmp) : ft_putendl(tmp->name);
            tmp = (op.r ? tmp->prev : tmp->next);
        }
    if (op.r_rec == 1)
        recu_path(op, r);
}