/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:58:49 by mehdi             #+#    #+#             */
/*   Updated: 2025/09/21 13:23:05 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum	e_token_type
{
	TOK_WORD,			// 0
	TOK_PIPE,			// | = 1
	TOK_REDIR_IN,		// < = 2
	TOK_REDIR_OUT,		// > = 3
	TOK_REDIR_APPEND,	// >> = 4
	TOK_HEREDOC			// << = 5
}	t_token_type;

typedef struct s_token_word
{
	char	*word;
	int		expendable;
	struct s_token_word	*next;
}	t_token_word;

typedef struct s_token
{
	t_token_word	*word;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

char			*ft_strjoin(char *s1, char const *s2);
char			*ft_strdup(const char *s1);
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				ft_isalnum(int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strlen(const char *str);

char			**ft_split_token(char const *s);
char			**ft_split_word(char const *s);
int				fr(char **result, int i);

void			sig_handler(int sig);

int				unclosed_quote(char *str);
char			**ft_cpy_envp(char **envp);
void			free_envp(char **envp);
void			free_token_words(t_token_word *head);
void			free_tokens(t_token *head);
void			free_split(char **split);

char			*clean_space(char *str);
int				is_double_operator(char *str);
int				is_operator(char c);

t_token_word	*split_node_word(char *str, char **env);
t_token_word	*new_node_word(char *str);
t_token			*new_node(t_token_word *word);
int				fill_expandable(t_token_word *token);
char			*delete_quote(char *str);

int				tokenize_line(t_token **token, char *str, char **env);
t_token			*new_node_operator(char *word);
int				operator(char *word);
void			add_back(t_token **token, t_token *new);
void			add_back_word(t_token_word **token, t_token_word *new);

void 			print_tokens(t_token *token);

#endif