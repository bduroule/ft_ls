/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   list_sort.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: beduroul <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/13 12:31:49 by beduroul     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/29 19:07:10 by beduroul    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ls_sort_swap(t_recu **prev, t_recu **curr)
{
	*prev = (*curr);
	*curr = (*curr)->next;
}

static t_recu	*ls_sort_asci(t_recu **prev, t_recu **head, t_recu *newl)
{
	t_recu		*curr;

	curr = *head;
	while (curr != NULL && (ft_strcmp(curr->name, newl->name) < 0))
		ls_sort_swap(prev, &curr);
	return (curr);
}

static t_recu	*ls_sort_size(t_recu **prev, t_recu **head, t_recu *newl)
{
	t_recu		*curr;

	curr = *head;
	while (curr != NULL && curr->size > newl->size)
		ls_sort_swap(prev, &curr);
	return (curr);
}

static t_recu	*ls_sort_time(t_recu **prev, t_recu **head, t_recu *newl)
{
	t_recu		*curr;

	curr = *head;
	while (curr != NULL && curr->time > newl->time)
		ls_sort_swap(prev, &curr);
	return (curr);
}

void			ls_list_insert_sort(t_recu **head, t_recu *newl, t_option op)
{
	t_recu	*curr;
	t_recu	*prev;

	prev = NULL;
	if (op.s_size)
		curr = ls_sort_size(&prev, head, newl);
	else if (op.t)
		curr = ls_sort_time(&prev, head, newl);
	else
		curr = ls_sort_asci(&prev, head, newl);
	newl->next = curr;
	if (prev == NULL)
		*head = newl;
	else
		prev->next = newl;
}
