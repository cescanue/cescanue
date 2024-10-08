/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:18:11 by cescanue          #+#    #+#             */
/*   Updated: 2023/05/09 09:58:55 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

void	ft_decode_cmd1(t_data *data, char *str)
{
	if (!ft_strcmp("sa\n", str))
		ft_sa(data);
	else if (!ft_strcmp("sb\n", str))
		ft_sb(data);
	else if (!ft_strcmp("ss\n", str))
		ft_ss(data);
	else if (!ft_strcmp("pa\n", str))
		ft_pa(data);
	else if (!ft_strcmp("pb\n", str))
		ft_pb(data);
	else if (!ft_strcmp("ra\n", str))
		ft_ra(data);
	else if (!ft_strcmp("rb\n", str))
		ft_rb(data);
	else if (!ft_strcmp("rr\n", str))
		ft_rr(data);
	else if (!ft_strcmp("rra\n", str))
		ft_rra(data);
	else if (!ft_strcmp("rrb\n", str))
		ft_rrb(data);
	else if (!ft_strcmp("rrr\n", str))
		ft_rrr(data);
	else
		ft_error(data, "Error\n");
}

void	ft_decode_cmd(t_data *data)
{
	char	*tmp;

	tmp = get_next_line(0);
	while (tmp)
	{
		ft_decode_cmd1(data, tmp);
		free (tmp);
		tmp = get_next_line(0);
	}
	free (tmp);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data.lsta = 0;
	data.lstb = 0;
	data.mov = 0;
	data.print = 0;
	if (argc == 1)
		ft_error(&data, "");
	ft_create_lst(&data, argc, argv);
	ft_generateindex(&data);
	ft_checkduplicateslsta(&data);
	ft_decode_cmd(&data);
	if (ft_risordered(*data.lsta) && !*data.lstb)
		ft_putstr_fd("OK\n", 1);
	else
		ft_putstr_fd("KO\n", 1);
	ft_clearmem(&data);
	return (0);
}
