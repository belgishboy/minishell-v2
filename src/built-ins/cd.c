/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdahlhof <cdahlhof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:50:26 by hlehmann          #+#    #+#             */
/*   Updated: 2022/04/05 15:09:17 by hlehmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	updateold(t_shell *shell)
{
	t_list	*old;
	t_list	*new;

	old = finder(shell->env, "OLDPWD");
	new = finder(shell->env, "PWD");
	free(((t_cont *)old->content)->value);
	((t_cont *)old->content)->value = \
		ft_strdup(((t_cont *)new->content)->value);
}

void	updatenew(t_shell *shell, char *new_pwd)
{
	t_list	*new;

	new = finder(shell->env, "PWD");
	free(((t_cont *)new->content)->value);
	((t_cont *)new->content)->value = new_pwd;
}

void	cd(char **array, t_shell *shell)
{
	char	*oldpwd;
	char	*newpwd;
	char	*check;
	int		check_two;

	check_two = 0;
	check = NULL;
	check = getcwd(oldpwd, MAX_DIR);
	if (check != NULL)
		return ;
	updateold(shell);
	check = NULL;
	opendir(array[1]);
	if (check == NULL)
		return ;
	check = NULL;
	check = getcwd(newpwd, MAX_DIR);
	updatenew(shell, newpwd);
	if (check != NULL)
		return ;
}
