/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_prg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:17:14 by cescanue          #+#    #+#             */
/*   Updated: 2023/05/03 14:21:48 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_clearmem(t_data *data)
{
	if (data->lsta)
	{
		ft_lstclear(data->lsta);
		free(data->lsta);
		data->lsta = 0;
	}
	if (data->lstb)
	{
		ft_lstclear(data->lstb);
		free(data->lstb);
		data->lstb = 0;
	}
}

void	ft_error(t_data *data, char *msg)
{
	ft_clearmem(data);
	ft_putstr_fd(msg, 2);
	exit (0);
}

void	ft_create_lst(t_data *data, int argc, char **argv)
{
	int		count;
	char	**ar;
	char	**delar;

	count = 1;
	data->lsta = ft_calloc(1, (sizeof(t_list *)));
	data->lstb = ft_calloc(1, (sizeof(t_list *)));
	if (!data->lsta || !data->lstb)
		ft_error(data, "Error\n");
	while (count < argc)
	{
		ar = ft_split(argv[count], ' ');
		delar = ar;
		while (*ar)
		{
			if (ft_isnbr(*ar))
				ft_lstadd_back(data->lsta, ft_lstnew(ft_atoi(*ar), -1));
			else
				ft_error(data, "Error\n");
			ar++;
		}
		count++;
		ft_freea(delar);
	}
}

void	ft_checkduplicateslsta(t_data *data)
{
	t_list	*t1lst;
	t_list	*t2lst;

	t1lst = *data->lsta;
	while (t1lst)
	{
		t2lst = *data->lsta;
		while (t2lst)
		{
			if (t1lst != t2lst && t1lst->nbr == t2lst->nbr)
				ft_error(data, "Error\n");
			t2lst = t2lst->next;
		}
		t1lst = t1lst->next;
	}
}
