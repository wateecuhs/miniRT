/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:28:46 by panger            #+#    #+#             */
/*   Updated: 2024/02/12 15:25:45 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	init(t_scene *scene)
{
	t_mlx	mlx;

	mlx.mlx = mlx_init();
	if (!mlx.mlx)
		return (perror_prefix("minilibx"), 1);
	mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "miniRT");
	if (!mlx.win)
		return (perror_prefix("minilibx"), 1);
	mlx.scene = scene;
	mlx.img = NULL;
	mlx.img = (t_img *)malloc(sizeof(t_img) * 1);
	set_hooks(&mlx);
	mlx.img->addr = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
	mlx.img->buffer = mlx_get_data_addr(mlx.img->addr,
			&(mlx.img->pixel_bits),
			&(mlx.img->line_bytes),
			&(mlx.img->endian));
	render_image(&mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img->addr, 0, 0);
	mlx_loop(mlx.mlx);
	return (0);
}
