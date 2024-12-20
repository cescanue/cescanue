/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 13:57:52 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/08 10:45:13 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	***parser(char *line, t_global *gd)
{
	char	*tline;
	char	**cmds;
	char	**tcmds;
	t_list	**lst_cmds;

	if (!p_common_errors(line))
	{
		tline = p_identify_blocks(line);
		tline = p_replace_env(tline, gd);
		cmds = ft_split_quotes(tline, ',');
		tcmds = cmds;
		lst_cmds = ft_calloc(1, sizeof(t_list *));
		if (!lst_cmds)
			ft_error("Unable to allocate memory in parser");
		while (tcmds && *tcmds)
		{
			ft_lstadd_back(lst_cmds, ft_lstnew(p_t_s(*tcmds)));
			tcmds++;
		}
		free_split(cmds, tline);
		*gd->cmds = lst_cmds;
		return (gd->cmds);
	}
	g_info->last_status = 2;
	return (0);
}
