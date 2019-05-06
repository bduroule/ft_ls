/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ls_permission.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: beduroul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/01 20:25:50 by beduroul     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 19:09:07 by beduroul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static char	get_acl(t_recu *r)
{
	if (listxattr(r->path, NULL, 0, XATTR_NOFOLLOW) > 0)
		return ('@');
	if (acl_get_link_np(r->path, ACL_TYPE_EXTENDED))
		return ('+');
	return (' ');
}

void		recu_path(t_option op, t_recu *r)
{
	t_recu *tmp;

	tmp = (op.r ? end_list(r) : r);
	while (tmp)
	{
		if (tmp->perm[0] == 'd')
		{
			ft_putchar('\n');
			ft_putstr(tmp->path);
			ft_putendl(":");
			read_path(op, tmp->right, tmp->path);
		}
		tmp = (op.r ? tmp->prev : tmp->next);
	}
}

char		type_file(struct stat *buff)
{
	if (S_ISREG(buff->st_mode))
		return ('-');
	else if (S_ISDIR(buff->st_mode))
		return ('d');
	else if (S_ISCHR(buff->st_mode))
		return ('c');
	else if (S_ISBLK(buff->st_mode))
		return ('b');
	else if (S_ISSOCK(buff->st_mode))
		return ('s');
	else if (S_ISFIFO(buff->st_mode))
		return ('p');
	else if (S_ISLNK(buff->st_mode))
		return ('l');
	else
		return ('-');
}

void		other(t_recu *rec, t_stat *buff, t_option op)
{
	if (!buff)
		exit(EXIT_FAILURE);
	rec->link = buff->st_nlink;
	rec->neod =  buff->st_ino;
	rec->size = buff->st_size;
	rec->time = buff->st_mtime;
	rec->minor = minor(buff->st_rdev);
	rec->major = major(buff->st_rdev);
	if (getpwuid(buff->st_uid) && !op.n)
	{
		if (!(rec->user = ft_strdup(getpwuid(buff->st_uid)->pw_name)))
			ls_error(rec->path, MALLOC);
	}
	else if (!(rec->user = ft_itoa(buff->st_uid)))
		ls_error(rec->path, MALLOC);
	if (getgrgid(buff->st_gid) && !op.n)
	{
		if (!(rec->group = ft_strdup(getgrgid(buff->st_gid)->gr_name)))
			ls_error(rec->path, MALLOC);
	}
	else if (!(rec->group = ft_itoa(buff->st_gid)))
		ls_error(rec->path, MALLOC);
	if (!(rec->date = ft_strsub(ctime(&buff->st_mtime), 4, 12)))
		ls_error(rec->path, MALLOC);
}

void		permision(t_recu *rec, struct stat *buff)
{
	rec->perm[0] = type_file(buff);
	rec->perm[1] = (buff->st_mode & S_IRUSR) ? 'r' : '-';
	rec->perm[2] = (buff->st_mode & S_IWUSR) ? 'w' : '-';
	rec->perm[3] = (buff->st_mode & S_IXUSR) ? 'x' : '-';
	rec->perm[4] = (buff->st_mode & S_IRGRP) ? 'r' : '-';
	rec->perm[5] = (buff->st_mode & S_IWGRP) ? 'w' : '-';
	rec->perm[6] = (buff->st_mode & S_IXGRP) ? 'x' : '-';
	rec->perm[7] = (buff->st_mode & S_IROTH) ? 'r' : '-';
	rec->perm[8] = (buff->st_mode & S_IWOTH) ? 'w' : '-';
	rec->perm[9] = (buff->st_mode & S_IXOTH) ? 'x' : '-';
	rec->perm[10] = get_acl(rec);
	if (buff->st_mode & S_ISGID)
		rec->perm[6] = (buff->st_mode & S_IXGRP) ? 's' : 'S';
	if (buff->st_mode & S_ISUID)
		rec->perm[3] = ((buff->st_mode & S_IXUSR) ? 's' : 'S');
	if (buff->st_mode & S_ISVTX)
		rec->perm[9] = (buff->st_mode & S_IXGRP) ? 't' : 'T';
	rec->perm[11] = '\0';
}
