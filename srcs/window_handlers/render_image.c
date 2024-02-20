/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:34:27 by panger            #+#    #+#             */
/*   Updated: 2024/02/20 15:33:14 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	render_image(t_mlx *mlx)
{
	t_vectors	screen_center;
	int			i;
	int			j;
	int			screen_height;
	int			screen_width;

	screen_height = 2 * tan(mlx->scene->camera->fov / 180);
	screen_width = screen_height * (WIDTH / HEIGHT);
	screen_center = add_coords_vectors(mlx->scene->camera->coords, mlx->scene->camera->vectors, 1);
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			render_pixel(mlx, j, i);
			j++;
		}
		i++;
	}
	return (0);
}
