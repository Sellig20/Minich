/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:55:45 by evsuits           #+#    #+#             */
/*   Updated: 2022/11/15 22:48:00 by evsuits          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_env(char *before_eq, char *after_eq, t_list *cmdredir, t_data *x)
{
	if (x->outfile > 2)
	{
		ft_putstr_fd(before_eq, x->outfile);
		ft_putstr_fd("=", x->outfile);
		ft_putstr_fd(after_eq, x->outfile);
		ft_putstr_fd("\n", x->outfile);
	}
	else
	{
		ft_putstr_fd(before_eq, ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
		ft_putstr_fd("=", ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
		ft_putstr_fd(after_eq, ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
		ft_putstr_fd("\n", ((t_cmdredir *)cmdredir->content)->fd_cmd[1]);
	}
}

int	ft_env(t_list *cmdredir, t_list **cpenv, t_data *x)
{
	t_list	*tmp;
	t_words	*content;
	char	*before_eq;
	char	*after_eq;
	int		index_eq;

	if ((((t_cmdredir *)cmdredir->content)->cmd)
		&& (((t_cmdredir *)cmdredir->content)->cmd->next))
		return (write(2, "Minimichel: exit: too many arguments\n", 37));
	tmp = *cpenv;
	while (tmp)
	{
		content = (t_words *) tmp->content;
		if (content->token == TOK_ENV)
		{
			index_eq = check_if_equal(content->word);
			before_eq = ft_strndup(content->word, index_eq);
			after_eq = ft_substr(content->word,
					index_eq + 1, ft_strlen(content->word));
			write_env(before_eq, after_eq, cmdredir, x);
			free(before_eq);
			free(after_eq);
		}
		tmp = tmp->next;
	}
	return (0);
}
