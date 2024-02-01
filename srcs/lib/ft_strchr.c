/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:08:28 by panger            #+#    #+#             */
/*   Updated: 2024/02/01 11:12:43 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	if (s == NULL)
		return (-1);
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return (i);
		i++;
	}
	if (s[i] == (unsigned char)c)
		return (i);
	return (-1);
}

int	ft_strchrstr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	if (s == NULL)
		return (-1);
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return (i);
		i++;
	}
	if (s[i] == (unsigned char)c)
		return (i);
	return (-1);
}

int	ft_strrchr(const char *s, int c)
{
	unsigned int	i;
	int				last;

	i = 0;
	last = -1;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			last = i;
		i++;
	}
	if (s[i] == (unsigned char)c)
		return (i);
	if (last == -1)
		return (-1);
	return (last);
}
