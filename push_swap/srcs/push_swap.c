/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:45:12 by cescanue          #+#    #+#             */
/*   Updated: 2023/05/03 18:29:14 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		interactive;

	data.lsta = 0;
	data.lstb = 0;
	data.print = 1;
	interactive = 0;
	if (argc == 1)
		ft_error(&data, "");
	if (*argv[1] == 'i')
	{
			argc--;
			argv++;
			interactive++;
			data.print = 0;
	}
	ft_create_lst(&data, argc, argv);
	ft_generateindex(&data);
	ft_checkduplicateslsta(&data);
	if (interactive)
		ft_interactive(&data);
	else
		ft_morder(&data);
	ft_clearmem(&data);
	return (0);
}
