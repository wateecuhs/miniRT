/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:58:49 by panger            #+#    #+#             */
/*   Updated: 2024/02/02 14:10:37 by panger           ###   ########.fr       */
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
# include <math.h>

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

typedef struct s_colors
{
	__uint8_t	r;
	__uint8_t	g;
	__uint8_t	b;
}	t_colors;

typedef struct s_ambient
{
	float		ratio;
	t_colors	color;
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
	t_colors	color;
}	t_light;

typedef struct s_sphere
{
	t_coords		coords;
	float			diameter;
	t_colors		color;
	struct s_sphere	*next;
}	t_sphere;

typedef struct s_plane
{
	t_coords		coords;
	t_vectors		vectors;
	t_colors		color;
	struct s_plane	*next;
}	t_plane;

typedef struct s_cylinder
{
	t_coords			coords;
	t_vectors			vectors;
	float				diameter;
	float				height;
	t_colors			color;
	struct s_cylinder	*next;
}	t_cylinder;

typedef struct s_scene
{
	t_ambient	*ambient_light;
	t_camera	*camera;
	t_light		*light;
	t_sphere	*sphere;
	t_cylinder	*cylinder;
	t_plane		*plane;
}	t_scene;

// lib
int			ft_strcmp(char *s1, char *s2);
int			ft_strchr(const char *s, int c);
int			ft_strrchr(const char *s, int c);
int			ft_strncmp(char *s1, char *s2, size_t n);
char		*ft_strdup(char *s);
size_t		ft_strlen(char *str);
void		perror_prefix(char *string);
t_scene		*init_scene(void);
void		free_arr(char **arr);
char		**ft_split(char *s, char *c);
size_t		ft_arrlen(char **arr);
int			is_digit(char c);
float		ft_atof(char *str);
int			is_float(char *s);
int			get_rgb(char *str, t_colors *ret);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		free_scene(t_scene *scene);

// parsing
int			parsing_hub(int argc, char **argv);
t_ambient	*ambient_identifier(char **line);
t_light		*light_identifier(char **line);

// gnl
char		*get_next_line(int fd);
char		*ft_stradd(char *s1, char *s2, int size);
char		*ft_strdupset(char const *s, int start, int stop);

#endif