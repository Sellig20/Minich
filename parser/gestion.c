/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:42:07 by jecolmou          #+#    #+#             */
/*   Updated: 2022/11/16 01:42:40 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_status;

void	ft_check_ambi(t_list **tmp, t_data *x)
{
	t_list	*list;

	if (!tmp || x->flag_heredoc != 0)
		return ;
	list = *tmp;
	while (list)
	{
		if ((ft_strncmp(((t_words *)list->content)->word, "<", 1) == 0
				|| ft_strncmp(((t_words *)list->content)->word, ">", 1) == 0
				|| ft_strncmp(((t_words *)list->content)->word, ">>", 1) == 0)
			&& (((((t_words *)list->next->content)->token == TOK_SPAC)
					&& ft_strncmp(((t_words *)list->next->next->content)->word,
						"$", 1) == 0)
				|| (ft_strncmp(((t_words *)list->next->content)->word,
						"$", 1) == 0)))
			x->key = 2;
		list = list->next;
	}
}

char	*ft_check_exec(char *str, t_data *x, t_list **cpenv, char *final)
{
	DIR		*d;

	(void)x;
	if (!str)
		return (free(str), NULL);
	d = opendir(str);
	if (d == NULL && access(str, X_OK) == 0)
		x->flag_uxu = 88;
	else if (d == NULL && x->flag_uxu != 5)
	{
		ft_putstr_fd("Minimichel : ", 2);
		g_status = 1;
		perror(str);
		if (final)
			free(final);
		if (x->is_pi == 66)
		{
			ft_lstclear(cpenv, ft_free_words);
			ft_exit_bis("1", x);
		}
		else
			return (NULL);
	}
	else if (d == NULL && x->i_ex != -1)
		return (NULL);
	closedir(d);
	return (str);
}

int	ft_is_space(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == ' ' && cmd[i + 1] == '\0')
			return (false);
		i++;
	}
	return (true);
}

int	ft_is_null(char *cmd)
{
	if (ft_strlen(cmd) == 0)
	{
		printf("Minimichel: Error \n");
		return (false);
	}
	else if (ft_is_space(cmd) == 0)
	{
		ft_putstr_fd("Minimichel: Error\n", 2);
		return (false);
	}
	return (1);
}
