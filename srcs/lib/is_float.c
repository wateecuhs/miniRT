/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_float.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 13:04:59 by panger            #+#    #+#             */
/*   Updated: 2024/02/05 10:05:18 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	is_float(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-')
		i++;
	if (!is_digit(s[i]))
		return (0);
	while (s[i] && is_digit(s[i]))
		i++;
	if (!s[i])
		return (1);
	if (s[i] != '.')
		return (0);
	i++;
	if (s[i] && is_digit(s[i]) && s[i + 1] == '\0')
		return (1);
	return (0);
}
