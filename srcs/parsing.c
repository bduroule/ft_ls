/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parcing.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: beduroul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/02 17:27:13 by beduroul     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 19:24:54 by beduroul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void			pars_sigle(t_recu **rec, t_option op, char *file, t_stat *buff)
{
	t_recu *r;

	if (!(r = (t_recu *)malloc(sizeof(t_recu))))
		ls_error(file, MALLOC);
	ft_strcpy(r->name, file);
	ft_strcpy(r->path, file);
	r->right = NULL;
	r->next = NULL;
	r->prev = NULL;
	r->block = buff->st_blocks;
	r->single = 1;
	permision(r, buff);
	other(r, buff, op);
	ls_list_insert_sort(rec, r, op);
}

static t_recu	*file_init(t_dirent *rd, t_recu *rec, char *path, t_option op)
{
	t_stat *buff;

	if (!(buff = malloc(sizeof(*buff))))
		ls_error(path, MALLOC);
	ft_strcpy(rec->path, path);
	ft_strcat(rec->path, "/");
	ft_strcat(rec->path, rd->d_name);
	if ((lstat(rec->path, buff)) < 0)
		if ((stat(rec->path, buff) < 0))
			return (NULL);
	ft_strcpy(rec->name, rd->d_name);
	rec->block = buff->st_blocks;
	permision(rec, buff);
	other(rec, buff, op);
	free(buff);
	return (rec);
}

static int		parse_file(t_dirent *rd, t_recu **rec, char *path, t_option op)
{
	t_recu *r;
	t_recu *tmp;

	if (!(r = (t_recu *)malloc(sizeof(t_recu))))
		ls_error(path, MALLOC);
	r = file_init(rd, r, path, op);
	r->single = 0;
	r->right = NULL;
	r->next = NULL;
	r->prev = NULL;
	if (op.f)
	{
		tmp = *rec;
		if (*rec == NULL)
			*rec = r;
		else
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = r;
		}
	}
	else
		ls_list_insert_sort(rec, r, op);
	return (1);
}

void			read_path(t_option op, t_recu *list, char *path)
{
	int			i;
	DIR			*dir;
	t_dirent	*rd;

	i = 1;
	if (!(dir = opendir(path)))
	{
		ls_error(path, ERRNO);
		return ;
	}
	while ((rd = readdir(dir)))
	{
		if (op.a == 1 && rd->d_name[0] == '.')
			parse_file(rd, &list, path, op);
		else if (rd->d_name[0] != '.')
			parse_file(rd, &list, path, op);
		i++;
	}
	init_rev(&list);
	display(list, op);
	closedir(dir);
	free_list(&list);
}
