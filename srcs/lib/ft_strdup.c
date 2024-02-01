/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 23:25:02 by waticouz          #+#    #+#             */
/*   Updated: 2024/02/01 12:35:43 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

char	*ft_strdup(char *s)
{
	size_t	srclen;
	size_t	i;
	char	*dest;

	srclen = 0;
	if (!s)
		return (NULL);
	while (s[srclen])
		srclen++;
	i = 0;
	dest = (char *)malloc((srclen + 1) * sizeof(char));
	if (!dest)
		return (perror_prefix("malloc"), NULL);
	while (i < srclen)
	{
		dest[i] = s[i];
		i ++;
	}
	dest[i] = '\0';
	return (dest);
}
