/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:19:26 by panger            #+#    #+#             */
/*   Updated: 2024/02/05 11:33:27 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_sphere_addback(t_sphere **head, t_sphere *new)
{
	t_sphere	*tmp;

	if (!(*head))
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	ft_plane_addback(t_plane **head, t_plane *new)
{
	t_plane	*tmp;

	if (!(*head))
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	ft_cylinder_addback(t_cylinder **head, t_cylinder *new)
{
	t_cylinder	*tmp;

	if (!(*head))
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
