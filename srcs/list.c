/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   list.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: beduroul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/15 14:48:02 by beduroul     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/15 14:48:03 by beduroul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

# include "ft_ls.h"

t_recu  *end_list(t_recu *list)
{
    while (list->next)
        list = list->next;
    return (list);
}

void    free_list(t_recu **list)
{
    t_recu *tmp;

    while ((*list))
    {
        free((*list)->date);
        tmp = (*list)->next;
        free((*list));
        *list = tmp;
    }
}

void    init_rev(t_recu **rec)
{
    t_recu *tmp;
    t_recu *prev;

    tmp = *rec;
    while (tmp->next)
    {
        prev = tmp;
        tmp = tmp->next;
        tmp->prev = prev;
    }
}

int   check_sigle(char **av, int i, struct stat *buff)
{
    while (av[i])
    {
        lstat(av[i], buff);
        if (type_file(buff) == 'l' || type_file(buff) == '-')
            return (1);
        i++;
    }
    return (1);
}

void    sigle_file(char **av, int i, struct stat *buff, t_option op)
{
    while (av[i])
    {
        lstat(av[i], buff);
        if (type_file(buff) == 'l' || type_file(buff) == '-')
            pars_sigle(op, av[i], buff);
        i++;
    }
}
