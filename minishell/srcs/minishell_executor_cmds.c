/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_executor_cmds.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 20:59:17 by cescanue          #+#    #+#             */
/*   Updated: 2023/09/06 20:51:41 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_executor_cmds_init_exec(t_exec_data *d, t_token *t, t_global *gd)
{
	d->env = gd->env;
	d->int_error_code = 0;
	d->term_status = 0;
	d->fd_in = -1;
	d->fd_out = -1;
	d->pipe_current[0] = -1;
	d->pipe_current[1] = -1;
	d->pipe_last[0] = -1;
	d->pipe_last[1] = -1;
	d->n_in = t->n_in + t->n_heredoc + t->n_in_literal;
	d->n_out = t->n_out + t->n_out_add;
	d->redi_in = t->cmdin;
	d->redi_out = t->cmdout;
	d->fork_pid_status = 1;
	d->exec_args = ft_split_quotes(t->cmd, ' ');
	ft_strtrim_quotes(d->exec_args);
}

void	ft_executor_cmds_redi_pipe2(t_token *token, t_exec_data *d, int *p)
{
	if (token->type == T_PIPE)
	{
		pipe(p);
		d->fd_out = p[1];
		d->pipe_current[0] = p[0];
		d->pipe_current[1] = p[1];
	}
	else
	{
		p[0] = -1;
		p[1] = -1;
		d->pipe_current[0] = -1;
		d->pipe_current[1] = -1;
	}
}

void	ft_executor_cmds_redi_pipe(t_token *token, t_exec_data *d, int *p)
{
	if (p[0] > 2)
	{
		d->fd_in = p[0];
		d->pipe_last[0] = p[0];
		d->pipe_last[1] = p[1];
	}
	else
	{
		d->pipe_last[0] = -1;
		d->pipe_last[1] = -1;
	}
	if (token->cmdin > 2)
		d->fd_in = token->cmdin;
	if (token->cmdout > 2)
		d->fd_out = token->cmdout;
	ft_executor_cmds_redi_pipe2(token, d, p);
}

void	ft_executor_cmds_waitpid(t_list *lst, t_global *gd)
{
	t_token		*token;
	t_exec_data	*d;

	while (lst)
	{
		token = lst->content;
		d = token->d;
		if (ft_executor_check_built_in(d) || d->fork_pid == 0)
			gd->last_status = d->term_status;
		else
		{
			waitpid(d->fork_pid, &d->waitpid_status, 0);
			d->term_status = WEXITSTATUS(d->waitpid_status);
			gd->last_status = d->term_status;
			d->fork_pid_status = 0;
		}
		ft_executor_close_fds(token);
		free_split(d->exec_args, d->exec_path);
		free(d);
		lst = lst->next;
	}
}

void	ft_executor_cmds(t_list *lst, t_global *gd)
{
	t_token		*token;
	t_exec_data	*d;
	int			p[2];
	t_list		*lstcopy;

	lstcopy = lst;
	p[0] = -1;
	p[1] = -1;
	while (lst)
	{
		token = lst->content;
		d = ft_calloc(1, sizeof(t_exec_data));
		token->d = d;
		ft_executor_cmds_init_exec(d, token, gd);
		ft_executor_cmds_redi_pipe(token, d, p);
		if (ft_executor_check_built_in(d))
			ft_command_exec_built_in(d);
		else
			ft_command_exec_cmd(d);
		lst = lst->next;
	}
	ft_executor_cmds_waitpid(lstcopy, gd);
}
