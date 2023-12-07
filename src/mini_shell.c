/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcardina <jcardina@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:17:29 by jcardina          #+#    #+#             */
/*   Updated: 2023/11/27 17:18:10 by jcardina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	init(t_general *general, char **envp)
{
	general->lexer = NULL;
	general->envp2 = matrix_dup(envp);
	general->path = ft_split(getenv("PATH"), ':');
	printf(PINK"\n%s\n", INTRO);
	printf("\n%s\n"RESET, HELLO2);
}


int	main(int ac, char **av, char **envp)
{
	t_general	general;
	t_lex		*tmp;

	if (ac != 1)
	{
		printf(RED "error dumb input\n" RESET);
		return (0);
	}
	init(&general, envp);
	while (1)
	{
		general.args = readline("kitty shell>");
		parser(&general);
		/*while (general.lexer == NULL)
		{
			printf("ciao");
			general.args = readline("kitty shell>");
		}*/
		tmp = general.lexer;
		execute_external_command(tmp->command2);
		wait(NULL);
		while (tmp != NULL)
		{	
			printf("token %i\n", tmp->token);
			printf("pipe steatus %i\n", tmp->pipe_status);
			printf("command %s\n", tmp->command);
			
			print_matrix(tmp->command2);
			printf("\n");
			tmp = tmp->next;
		}
		
		afalcons(general.lexer);
		general.lexer = NULL;
	}
}
