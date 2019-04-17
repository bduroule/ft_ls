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

# define OPTION "artRlS"

void    read_path(t_option op, t_recu *list, char *path);
void    permision(t_recu *rec, struct stat *buff);
void    other(t_recu *rec, struct stat *buff);
void    display(t_recu *r, t_option op);
void    recu_path(t_option op, t_recu *r);
void    free_list(t_recu **list);
t_recu  *asci_list(t_recu *rec, t_recu *new);
void	ls_list_insert_sort( t_recu **head, t_recu *newl, t_option op);
void    init_rev(t_recu **rec);
t_recu  *end_list(t_recu *list);
char    type_file(struct stat *buff);
void    pars_sigle(t_recu **list, t_option op, char *file, struct stat *buff);
int   check_sigle(char **av, int i, struct stat *buff);
void    sigle_file(char **av, int i, struct stat *buff, t_option op);
void    parse_path(char **av, t_option op, int i, int n);
void    putls_l(t_recu *tmp, t_option op);
void max_size(t_recu *recu, t_max *max, t_option op);
void    ls_error(char *s, int n);


# endif
