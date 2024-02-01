/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:58:49 by panger            #+#    #+#             */
/*   Updated: 2024/02/01 12:49:30 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_coords
{
	float	x;
	float	y;
	float	z;
}	t_coords;

typedef struct s_vectors
{
	float	x;
	float	y;
	float	z;
}	t_vectors;

typedef struct s_ambient
{
	float		ratio;
	__uint32_t	color;
}	t_ambient;

typedef struct s_camera
{
	t_coords	coords;
	t_vectors	vectors;
}	t_camera;

typedef struct s_light
{
	t_coords	coords;
	float		brightness;
	__uint32_t	color;
}	t_light;

typedef struct s_sphere
{
	t_coords		coords;
	float			diameter;
	__uint32_t		color;
	struct s_sphere	*next;
}	t_sphere;

typedef struct s_plane
{
	t_coords		coords;
	t_vectors		vectors;
	__uint32_t		color;
	struct s_plane	*next;
}	t_plane;

typedef struct s_cylinder
{
	t_coords			coords;
	t_vectors			vectors;
	float				diameter;
	float				height;
	__uint32_t			color;
	struct s_cylinder	*next;
}	t_cylinder;

typedef struct s_scene
{
	t_ambient	ambient_light;
	t_camera	camera;
	t_light		light;
	t_sphere	sphere;
	t_cylinder	cylinder;
	t_plane		plane;
	
}	t_scene;

// lib
int		ft_strcmp(char *s1, char *s2);
int		ft_strchr(const char *s, int c);
int		ft_strrchr(const char *s, int c);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strdup(char *s);
size_t	ft_strlen(char *str);
void	perror_prefix(char *string);

// parsing
int		parsing_hub(int argc, char **argv);

// gnl
char	*get_next_line(int fd);
char	*ft_stradd(char *s1, char *s2, int size);
char	*ft_strdupset(char const *s, int start, int stop);

#endif