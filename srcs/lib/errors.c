/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 12:58:57 by panger            #+#    #+#             */
/*   Updated: 2024/02/20 12:56:49 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	perror_prefix(char *string)
{
	write(2, "miniRT: ", 8);
	if (!string || ft_strcmp(string, "") == 0)
		perror(" ");
	else
		perror(string);
}

void	ft_putchar(char c)
{
	write(2, &c, 1);
}

void	ft_putnbr(unsigned int nb)
{
	if (nb > 9)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
		ft_putchar(nb + 48);
}

void	error_parsing(int error_status, size_t line, char *type)
{
	if (error_status == 1)
	{
		write(2, "Line ", 5);
		ft_putnbr(line + 1);
		write(2, ": identifier '", 14);
		write(2, type, ft_strlen(type));
		write(2, "' is invalid.\n", 14);
	}
}