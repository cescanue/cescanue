/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:54:17 by cescanue          #+#    #+#             */
/*   Updated: 2023/05/19 15:41:43 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_dellsti(void *img)
{
	if (((t_img *)img)->img)
		mlx_destroy_image(((t_img *)img)->mlx, ((t_img *)img)->img);
	if (((t_img *)img))
		free(((t_img *)img));
}

void	ft_dellstg(void *img)
{
	if (((t_gimg *)img))
		free(((t_gimg *)img));
}

void	ft_clearlsti(t_list **lst)
{
	ft_lstclear(lst, ft_dellsti);
	free(lst);
}

void	ft_clearlstg(t_list **lst)
{
	ft_lstclear(lst, ft_dellstg);
	free(lst);
}

void	ft_lstdelonem(t_list **head, t_list *lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*tmp1;

	tmp = *head;
	if (tmp == lst)
	{
		*head = ((t_list *)*head)->next;
		del(tmp->content);
		free(tmp);
	}
	else
	{
		while (tmp && tmp != lst)
		{
			tmp1 = tmp;
			tmp = tmp->next;
		}
		tmp1->next = tmp->next;
		del(tmp->content);
		free(tmp);
	}
}
