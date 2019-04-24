/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ls.h                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: beduroul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/29 18:46:18 by beduroul     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/29 18:46:20 by beduroul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

# ifndef FT_LS_H
#define FT_LS_H

# include <dirent.h>
# include <sys/types.h> 
# include <sys/stat.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <errno.h>
# include "../libft/include/libft.h"
# include "struct.h"
# include <limits.h>

/**/
#include <stdio.h>
/**/

# define OPTION "artRlSG"

/*
**  Display
*/
char    *color_name(t_recu *tmp, char *str, t_option op);
void    putls_l(t_recu *tmp, t_option op);
void    display(t_recu *r, t_option op);

/*
**  Parcing ls -l
*/

void    other(t_recu *rec, struct stat *buff);
void    permision(t_recu *rec, struct stat *buff);
void    max_size(t_recu *recu, t_max *max, t_option op);
char    type_file(struct stat *buff);

/*
**  Parcing single
*/

void    sigle_file(char **av, int i, struct stat *buff, t_option op);
void    pars_sigle(t_recu **list, t_option op, char *file, struct stat *buff);
int     check_sigle(char **av, int i, struct stat *buff);

/*
**  Parcing path
*/
void    read_path(t_option op, t_recu *list, char *path);
void    parse_path(char **av, t_option op, int i, int n);

/*
**  Sort
*/
t_recu  *asci_list(t_recu *rec, t_recu *new);
void	ls_list_insert_sort( t_recu **head, t_recu *newl, t_option op);
void    init_rev(t_recu **rec);

/*
**  Other
*/
void    recu_path(t_option op, t_recu *r);
void    free_list(t_recu **list);
t_recu  *end_list(t_recu *list);
void    ls_error(char *s, int n);


# endif
