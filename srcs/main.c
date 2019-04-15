/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: beduroul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/29 18:46:34 by beduroul     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/29 18:46:37 by beduroul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static void init_option(t_option *op)
{
    (*op).a = 0;
    (*op).r = 0;
    (*op).r_rec = 0;
    (*op).l = 0;
    (*op).t = 0;
    (*op).s_size = 0;
}

void    ls_usage(void)
{
    write(1, "usage: ./ft_ls [-artRlS] [file ...]\n", 36);
    exit(0);
}

static void    parse_path(char **av, t_option op, int i, int n)
{
    t_recu  *list;
    struct stat *buff;

    list = NULL;
    if (!(buff = malloc(sizeof(*buff))))
        return ;
    if (n == 0)
            read_path(op, list, ".");
    if (check_sigle(av, i + 1, buff))
        sigle_file(av, i + 1, buff, op);
    while (av[++i])
    {
        lstat(av[i], buff);
        if (type_file(buff) == 'l' || type_file(buff) == '-')
            ;
        else
        {
            if (n > 1)
            {
                ft_putchar('\n');
                ft_putstr(av[i]);
                ft_putendl(":");
            }
            read_path(op, list, av[i]);
            if (av[i + 1])
                 write(1, "\n", 1);
        }
    }
    free(buff);
}

static int parse_option(char **av, t_option *op, int i)
{
    int j;
    int c;

    i = 0;
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
                    ls_usage();
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
            }
        }
    }
    return (c);
}

int main(int ac, char **av)
{
    t_option op;
    int i;
    (void)ac;
    
    i = -1;
    init_option(&op);
    i = parse_option(av, &op, i);
    parse_path(av, op, i, (ac - 1) - i);
    return 0;
}
