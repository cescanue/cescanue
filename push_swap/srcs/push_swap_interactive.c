/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_interactive.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 20:14:50 by cescanue          #+#    #+#             */
/*   Updated: 2023/05/03 18:42:27 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_printlst(t_data	*data)
{
	t_list	*lsta;
	t_list	*lstb;

	lsta = *data->lsta;
	lstb = *data->lstb;
	printf("        Stack A         |        Stack B         \n");
	printf(" Value     |  Index     | Value     |  Index     \n");
	printf("-------------------------------------------------\n");
	while (lsta || lstb)
	{
		if (lsta && lstb)
			printf("%-11d %-11d |%-11d %-11d\n",
				lsta->nbr, lsta->index, lstb->nbr, lstb->index);
		else if (lsta)
			printf("%-11d %-11d |                      \n",
				lsta->nbr, lsta->index);
		else
			printf("                        |%-11d %-11d\n",
				lstb->nbr, lstb->index);
		if (lsta)
			lsta = lsta->next;
		if (lstb)
			lstb = lstb->next;
	}
}

void	ft_interactive_help(void)
{
	printf("Push_Swap cescanue\n");
	printf("You are in interactive mode, you have the following functions:\n");
	printf("sa (swap a): Swap the first 2 elements at the top of stack a.\n");
	printf("sb (swap b): Swap the first 2 elements at the top of stack b.\n");
	printf("ss : sa and sb at the same time.\n");
	printf("pa (push a): Take the first element at the");
	printf(" top of b and put it at the top of a,\n");
	printf("pb (push b): Take the first element at the");
	printf(" top of a and put it at the top of b.\n");
	printf("ra (rotate a): Shift up all elements of stack a by 1.\n");
	printf("rb (rotate b): Shift up all elements of stack b by 1.\n");
	printf("rr : ra and rb at the same time.\n");
	printf("rra (reverse rotate a): Shift down all elements of stack a by 1.\n");
	printf("rrb (reverse rotate b): Shift down all elements of stack b by 1.\n");
	printf("rrr : rra and rrb at the same time.\n");
	printf("print : print stack a and stack b.\n");
	printf("help : show this message.\n");
	printf("exit : exit the push swap return the control to the OS.\n");
}

void	ft_interactive(t_data *data)
{
	char	str[10];

	ft_interactive_help();
	while (ft_strcmp("exit", str))
	{
		scanf("%s", str);
		if (!ft_strcmp("print", str))
			ft_printlst(data);
		else if (!ft_strcmp("help", str))
			ft_interactive_help();
		else if (!ft_strcmp("sa", str))
			ft_sa(data);
		else if (!ft_strcmp("sb", str))
			ft_sb(data);
		else if (!ft_strcmp("ss", str))
			ft_ss(data);
		else if (!ft_strcmp("pa", str))
			ft_pa(data);
		else
			ft_interactive_choice(str, data);
	}
}

void	ft_interactive_choice(char *str, t_data *data)
{
	if (!ft_strcmp("pb", str))
		ft_pb(data);
	else if (!ft_strcmp("ra", str))
		ft_ra(data);
	else if (!ft_strcmp("rb", str))
		ft_rb(data);
	else if (!ft_strcmp("rr", str))
		ft_rr(data);
	else if (!ft_strcmp("rra", str))
		ft_rra(data);
	else if (!ft_strcmp("rrb", str))
		ft_rrb(data);
	else if (!ft_strcmp("rrr", str))
		ft_rrr(data);
}
