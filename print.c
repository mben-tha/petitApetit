/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 16:47:25 by mehdi             #+#    #+#             */
/*   Updated: 2025/09/19 16:47:39 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_tokens(t_token *token)
{
	while (token)
	{
		printf("Token type: %d\n", token->type);
		t_token_word *word = token->word;
		while (word)
		{
			printf("  Word: [%s] (expendable: %d)\n", word->word, word->expendable);
			word = word->next;
		}
		token = token->next;
	}
}
