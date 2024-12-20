/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:37:17 by panger            #+#    #+#             */
/*   Updated: 2024/03/06 11:18:12 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	cross_close(t_mlx *mlx)
{
	if (mlx->img)
		mlx_destroy_image(mlx->mlx, mlx->img->addr);
	mlx_destroy_window(mlx->mlx, mlx->win);
	free_scene(mlx->scene);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	exit(EXIT_SUCCESS);
	return (0);
}

int	key_close(int keycode, t_mlx *mlx)
{
	if (keycode == 65307)
	{
		if (mlx->img)
			mlx_destroy_image(mlx->mlx, mlx->img->addr);
		mlx_destroy_window(mlx->mlx, mlx->win);
		free_scene(mlx->scene);
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

void	set_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->win, 17, 1L << 0, cross_close, mlx);
	mlx_hook(mlx->win, 2, 1L << 0, key_close, mlx);
}
