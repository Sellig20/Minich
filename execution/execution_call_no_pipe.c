/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_call_no_pipe.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:45:51 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/12 17:46:38 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	call_no_pipe(t_list *cmd, t_list *redir, t_list **cpenv, t_data *x)
{
	signal(SIGQUIT, handle_sig_child);
	signal(SIGINT, handle_sig_child);
	ft_proc_no_pipe(&cmd, &redir, x, cpenv);
}
