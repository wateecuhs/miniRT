/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 12:58:57 by panger            #+#    #+#             */
/*   Updated: 2024/02/01 12:47:57 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	error_msg(char *string)
{
	if (!string)
		perror("minishell");
	else
		perror(string);
	exit(EXIT_FAILURE);
}

void	perror_prefix(char *string)
{
	write(2, "minishell: ", 11);
	if (!string || ft_strcmp(string, "") == 0)
		perror(" ");
	else
		perror(string);
}
