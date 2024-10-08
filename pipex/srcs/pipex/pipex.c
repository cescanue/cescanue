/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:27:48 by cescanue          #+#    #+#             */
/*   Updated: 2023/06/28 16:55:29 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	(void) argc;	
	(void) argv;
	(void) envp;
	ft_printf("exce:%d\n", exec(argv[1], &argv[1], envp));
	ft_printf("principal");
	return (0);
}
