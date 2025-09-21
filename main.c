/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:53:09 by mehdi             #+#    #+#             */
/*   Updated: 2025/09/21 13:12:06 by mehdi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
}

static int	exit_shell(char **env)
{
	printf("exit\n");
	free_envp(env);
	clear_history();
	exit(0);
}

static void	handle_unclosed_quote(char *input)
{
	printf("unclosed quote\n");
	free(input);
}

static void	process_input(char *input, char **env)
{
	char	*str;
	t_token	*head;

	head = NULL;
	str = clean_space(input);
	free(input);
	if (!str)
	{
		perror("malloc_error");
		return ;
	}
	if (tokenize_line(&head, str, env))
	{
		fprintf(stderr, "minishell: tokenize failed\n");
		free(str);
		return ;
	}
	printf("%s\n", str);
	free(str);
	// ici tu peux debug afficher les tokens
	print_tokens(head);
	free_tokens(head);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	**cpy_env;

	(void)ac;
	(void)av;
	if (!envp)
		return (0);
	cpy_env = ft_cpy_envp(envp);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			return (exit_shell(cpy_env));
		if (*input)
			add_history(input);
		if (unclosed_quote(input))
			handle_unclosed_quote(input);
		else
			process_input(input, cpy_env);
	}
	return (0);
}
