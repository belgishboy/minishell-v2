/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheymans <vheymans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:15:24 by vheymans          #+#    #+#             */
/*   Updated: 2022/03/22 15:27:33 by vheymans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Main Shell Function
 * 
*/
int		shell(char **env)
{
	
}

/**
 * Main Function
 * runs the shell function if # of args is 1 and that it is "./minishell".
 * Else returns error
 * @param argc	[int] number of arguments
 * @param argv	[char **] arguments
 * @param env	[char **] enviroment
 * @return 0 if succesfull, non-zero if error
*/
int	main(int argc, char **argv, char **env)
{
	if (argc != 1 && strncmp(argv[0], "./minishell", strlen(argv[0])))
		ft_error("fuck", 2);
	shell(env);
	return (0);
}