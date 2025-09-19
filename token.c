/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:53:16 by mehdi             #+#    #+#             */
/*   Updated: 2025/09/19 17:34:20 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_token_error(char **res, t_token **token)
{
	free_split(res);
	free_tokens(*token);
	return (1);
}

static t_token	*create_token(char *word, char **env, char **res, t_token **token)
{
	t_token_word	*new_word;
	t_token			*new;

	if (word[0] == '<' || word[0] == '>' || word[0] == '|')
		new = new_node_operator(word);
	else
	{
		new_word = split_node_word(word, env);
		if (!new_word)
		{
			handle_token_error(res, token);
			return (NULL);
		}
		new = new_node(new_word);
	}
	if (!new)
	{
		handle_token_error(res, token);
		return (NULL);
	}
	return (new);
}

int	tokenize_line(t_token **token, char *str, char **env)
{
	char	**res;
	int		i;
	t_token	*new;

	res = ft_split_token(str);
	if (!res)
		return (1);
	i = 0;
	while (res[i])
	{
		new = create_token(res[i], env, res, token);
		if (!new)
			return (1);
		add_back(token, new);
		i++;
	}
	free_split(res);
	return (0);
}


// int	tokenize_line(t_token **token, char *str, char **env)
// {
// 	char			**res;
// 	int				i;
// 	t_token			*new;
// 	t_token_word	*new_word;

// 	res = ft_split_token(str);
// 	if (!res)
// 		return (1);
// 	i = 0;
// 	while (res[i])
// 	{
// 		if (res[i][0] == '<' || res[i][0] == '>' || res[i][0] == '|')
// 			new = new_node_operator(res[i]);
// 		else
// 		{
// 			new_word = split_node_word(res[i], env);
// 			if (!new_word)
// 				return (handle_token_error(res, token));
// 			new = new_node(new_word);
// 		}
// 		if (!new)
// 			return (handle_token_error(res, token));
// 		add_back(token, new);
// 		i++;
// 	}
// 	free_split(res);
// 	return (0);
// }

t_token	*new_node_operator(char *word)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = operator(word);
	new->word = NULL;
	// new->word.expendable = 0;
	// new->word.next = NULL;
	new->next = NULL;
	return (new);
}

int	operator(char *word)
{
	if (word[0] == '<' && !word[1])
		return (TOK_REDIR_IN);
	else if (word[0] == '>' && !word[1])
		return (TOK_REDIR_OUT);
	else if (word[0] == '|' && !word[1])
		return (TOK_PIPE);
	else if (word[0] == '<' && word[1] == '<')
		return (TOK_HEREDOC);
	else if (word[0] == '>' && word[1] == '>')
		return (TOK_REDIR_APPEND);
	return (-1);
}

void	add_back(t_token **token, t_token *new)
{
	t_token	*tmp;

	if (!*token)
	{
		*token = new;
		return ;
	}
	tmp = *token;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	add_back_word(t_token_word **token, t_token_word *new)
{
	t_token_word	*tmp;

	if (!*token)
	{
		*token = new;
		return ;
	}
	tmp = *token;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
