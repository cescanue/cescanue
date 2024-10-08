/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:45:00 by cescanue          #+#    #+#             */
/*   Updated: 2023/06/28 11:53:08 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../ft_printf/libft/includes/libft.h"
# include "../ft_printf/includes/ft_printf.h"
# include <unistd.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>

int	exec(char *cmd, char **argv, char **envp);

#endif