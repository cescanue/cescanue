/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_std3_funtions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:37:23 by cescanue          #+#    #+#             */
/*   Updated: 2023/04/30 21:03:57 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	mem = (void *) malloc(count * size);
	if (!mem)
		return (0);
	ft_bzero(mem, count * size);
	return (mem);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	count;

	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	count = 0;
	while (s1[count] != 0
		&& s2[count] != 0
		&& (unsigned char) s1[count] == (unsigned char) s2[count])
		count++;
	if ((unsigned char) s1[count] - (unsigned char) s2[count] > 0)
		return (1);
	else if ((unsigned char) s1[count] - (unsigned char) s2[count] < 0)
		return (-1);
	else
		return (0);
}

void	ft_dupdataint(t_data *d, t_data *dup)
{
	dup->lstsize = d->lstsize;
	dup->split = d->split;
	dup->spsize = d->spsize;
	dup->spsizel = d->spsizel;
	dup->maxc = d->maxc;
	dup->maxlstsize = d->maxlstsize;
	dup->mov = d->mov;
	dup->print = d->print;
}

t_data	ft_dupdata(t_data *d)
{
	t_data	dup;
	t_list	*tlst;

	dup.lsta = ft_calloc(1, (sizeof(t_list *)));
	dup.lstb = ft_calloc(1, (sizeof(t_list *)));
	if (!dup.lsta || !dup.lstb)
		ft_error(&dup, "Error\n");
	tlst = *d->lsta;
	while (tlst)
	{	
		ft_lstadd_back(dup.lsta, ft_lstnew(tlst->nbr, tlst->index));
		tlst = tlst->next;
	}
	tlst = *d->lstb;
	while (tlst)
	{	
		ft_lstadd_back(dup.lstb, ft_lstnew(tlst->nbr, tlst->index));
		tlst = tlst->next;
	}
	ft_dupdataint(d, &dup);
	return (dup);
}
