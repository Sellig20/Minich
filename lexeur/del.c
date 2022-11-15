/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecolmou <jecolmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:42:12 by evsuits           #+#    #+#             */
/*   Updated: 2022/11/12 18:11:14 by jecolmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_expand_one_btw_quot(t_list **tmp, t_list **envcp, t_data *x)
{
	int		res;
	char	*new_echo;

	res = 0;
	new_echo = NULL;
	if (*tmp && (((t_words *)(*tmp)->content)->token != TOK_QUOT))
	{
		if (((t_words *)(*tmp)->content)->token == TOK_DOLL && (*tmp)->next)
		{
			res = ft_check_after_d(((t_words *)(*tmp)->next->content)->word);
			new_echo = ft_result(envcp, res,
					((t_words *)(*tmp)->next->content)->word, x);
			if (ft_strlen(new_echo) == 0)
			{
				return (new_echo);
			}
		}
		else
			new_echo = ft_strdup(((t_words *)(*tmp)->content)->word);
	}
	if (x->check == D_QUOTE_STATE || x->file == 42)
		protect_space(new_echo, 1);
	return (new_echo);
}

char	**doll(char **btw, t_list **tmp, t_list **envcp, t_data *x)
{
	char	*word;
	char	*word2;
	char	**words;
	int		i;
	int		j;

	i = 0;
	j = 0;
	words = NULL;
	word2 = NULL;
	word = ft_expand_one_btw_quot(tmp, envcp, x);
	if (!word)
	{
		*tmp = (*tmp)->next;
		return (btw);
	}
	if (x->check != D_QUOTE_STATE)
	{
		dprintf(2, "doll: word=%s,\n", word);
		words = ft_split(word, ' ');
		unprotect_space(words);
		while (btw && btw[i])
			i++;
		while (words && words[j])
			btw[i++] = ft_strdup(words[j++]);
	}
	else
	{
		protect_space(word, -1);
		while (btw && btw[i])
			i++;
		if (i == 0)
			btw[0] = ft_strdup(word);
		else
		{
			word2 = ft_strjoin(btw[i - 1], word);
			free(btw[i - 1]); 
			btw[i - 1] = ft_strdup(word2);
			free(word2);
		}
	}
	*tmp = (*tmp)->next;
	return (ft_free_w(words), free(word), btw);
}

static char	**doll_btw_del(t_list **tmp, char **btw, t_list **envcp, t_data *x)
{
	char	*word;
	int		i;

	i = 0;
	if (((t_words *)(*tmp)->next->content)->token != TOK_QUOT)
	{
		btw = doll(btw, tmp, envcp, x);
		return (btw);
	}
	while (btw[i] && btw[i + 1])
		i++;
	word = btw[i];
	free(btw[i]);
	btw[i] = ft_strjoin(word, "$\0");
	(*tmp) = (*tmp)->next;
	return (free(word), btw);
}

char	**until_next_del(t_list *tmp, t_list *end, t_list **envcp, t_data *x)
{
	char	**btw_del;
	int		i;

	x->check = DEFAULT_STATE;
	x->check_to = DEFAULT_STATE;
	i = get_len_words(tmp, end);
	btw_del = calloc(sizeof(char *), (i + 1));
	while (tmp && tmp->content && tmp != end)
	{
		i = 0;
		quotes(x, tmp);
		if (((t_words *) tmp->content)->token == TOK_DOLL
			&& x->flag_heredoc <= 0)
			btw_del = doll_btw_del(&tmp, btw_del, envcp, x);
		else if (((t_words *)tmp->content)->token != TOK_QUOT
			|| (x->flag_heredoc != 0 && x->flag_heredoc != 168))
			append_last_word(tmp, btw_del);
		tmp = tmp->next;
	}
	if (!(btw_del[0]) && x->check_to > DEFAULT_STATE)
		btw_del[0] = ft_strdup("fake2\0");
	return (btw_del);
}

t_list	*find_end_del(t_list *af_del)
{
	t_list	*end;

	if (af_del)
		end = af_del;
	else
		return (NULL);
	while (end && check_del(end) == 0)
		end = end->next;
	return (end);
}
