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

void    ls_error(char *s, int n)
{
    if (n == 0)
    {
        ft_putstr_fd("ft_ls: illegal option -- ", 2);
        ft_putchar_fd(s[1], 2);
        write(2, "\n", 1);
        write(1, "usage: ./ft_ls [-artRlSG] [file ...]\n", 37);
        exit(0);
    }
    if (n == -1)
    {
        ft_putstr_fd("ft_ls: ", 2);
        perror(s);
    }
    //exit(EXIT_FAILURE);
}

void    ls_usage(void)
{
    write(1, "usage: ./ft_ls [-artRlS] [file ...]\n", 36);
    exit(0);
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
                    ls_error(av[i], 0);
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
                if (av[i][j] == 'G')
                    (*op).g_color = 1;
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