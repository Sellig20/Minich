/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 18:41:45 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/15 01:45:32 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ftclosep(t_data *x)
{
	close(x->fd_pipe[0]);
	close(x->fd_pipe[1]);
}

void	ft_close_files(t_data *x)
{
	if (x->infile)
		close(x->infile);
	if (x->outfile)
		close(x->outfile);
}

int	ft_nb_cmd(t_list **lst)
{
	int			count;
	t_list		*buffer;

	count = 0;
	buffer = *lst;
	while (buffer)
	{
		buffer = buffer->next;
		count++;
	}
	return (count);
}

void	ft_set_fdcmd(t_list **after_doll, t_data *x)
{
	t_list	*tmp;
	int		j;

	tmp = *after_doll;
	x->nb_cmd = ft_nb_cmd(&tmp);
	while (tmp)
	{
		j = 0;
		while (j < x->nb_cmd)
		{
			((t_cmdredir *)tmp->content)->fd_cmd[0] = STDIN_FILENO;
			((t_cmdredir *)tmp->content)->fd_cmd[1] = STDOUT_FILENO;
			j++;
		}
		tmp = tmp->next;
	}
}

void	ft_loop_redirections_prot(t_list **redir, t_data *x)
{
	t_list	*tmp_redir;

	tmp_redir = *redir;
	if (ft_is_redirection_in(&tmp_redir) == 1)
	{
		if (x->count_files > 0)
			ft_close_files(x);
		ft_no_pipe_redirection_in(&tmp_redir, x);
	}
	if (ft_is_redirection_out(&tmp_redir) == 1)
	{
		if (x->count_files > 0)
			ft_close_files(x);
		ft_no_pipe_redirection_out(&tmp_redir, x);
	}
}