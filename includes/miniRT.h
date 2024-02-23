/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: panger <panger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:58:49 by panger            #+#    #+#             */
/*   Updated: 2024/02/23 18:53:34 by panger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define HEIGHT 800
# define WIDTH 800
# define M_PI 3.14159265358979323846
# define EPSILON 0.00001

# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <mlx.h>

typedef struct s_matrix
{
	double	m[3][3];
}	t_matrix;

typedef struct s_pair
{
	double	x;
	double	y;
}	t_pair;

typedef struct s_vectors
{
	double	x;
	double	y;
	double	z;
}	t_vectors;

typedef struct s_ray
{
	t_vectors	origin;
	t_vectors	vector;
}	t_ray;

typedef struct s_colors
{
	__uint8_t	a;
	__uint8_t	r;
	__uint8_t	g;
	__uint8_t	b;
}	t_colors;

typedef struct s_ambient
{
	double		ratio;
	t_colors	color;
}	t_ambient;

typedef struct s_camera
{
	t_vectors	coords;
	t_vectors	vectors;
	__uint8_t	fov;
}	t_camera;

typedef struct s_light
{
	t_vectors	coords;
	double		brightness;
	t_colors	color;
}	t_light;

typedef struct s_sphere
{
	t_vectors		coords;
	double			diameter;
	t_colors		color;
	struct s_sphere	*next;
}	t_sphere;

typedef struct s_plane
{
	t_vectors		coords;
	t_vectors		vectors;
	t_colors		color;
	struct s_plane	*next;
}	t_plane;

typedef struct s_cylinder
{
	t_vectors			coords;
	t_vectors			vectors;
	double				diameter;
	double				height;
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

typedef struct s_img
{
	void	*addr;
	int		pixel_bits;
	int		line_bytes;
	int		endian;
	char	*buffer;
}			t_img;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	t_img		*img;
	t_scene		*scene;
}	t_mlx;

// rendering
int			render_image(t_mlx *mlx);
int			render_pixel(t_mlx *mlx, int x, int y);
int			init(t_scene *scene);
int			calc_pixel(int x, int y, t_img *img);
void		draw_pixel(char *buffer, int pixel, t_colors color, int endian);

// vectors
void		normalize_vector(t_vectors *vector);
t_vectors	add_coords_vectors(t_vectors coords, t_vectors vectors, double factor);
t_vectors	multiply_vec_matrix(t_vectors p, t_matrix m);
t_vectors	create_vector(double x, double y, double z);
t_vectors	cross_product(t_vectors vec1, t_vectors vec2);
t_vectors	substract(t_vectors vec1, t_vectors vec2);
t_matrix	look_at(t_vectors origin, t_vectors cam_vector);
double		vec_dot(t_vectors vec1, t_vectors vec2);
t_ray		create_ray(t_vectors origin, t_vectors direction);
t_vectors	multiply_vector(t_vectors vec1, double factor);
int			color_to_int(t_colors color);

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
double		ft_atof(char *str);
int			is_float(char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		free_scene(t_scene *scene);
void		ft_cylinder_addback(t_cylinder **head, t_cylinder *new);
void		ft_plane_addback(t_plane **head, t_plane *new);
void		ft_sphere_addback(t_sphere **head, t_sphere *new);
void		error_parsing(int error_status, size_t line, char *type);
t_pair		assign_pair(double x, double y);
void		set_hooks(t_mlx *mlx);
t_ray		ray_to_pixel(int x, int y, t_scene *scene);
int			ft_atoi(const char *nptr);
t_colors	multiply_colors(t_colors color, t_colors new, double ratio);
t_colors	add_ambient(t_colors color, t_ambient *ambient);
t_colors	create_color(__uint8_t a, __uint8_t r, __uint8_t g, __uint8_t b);

// parsing
t_scene		*parsing_hub(int argc, char **argv);
t_ambient	*ambient_identifier(char **line, int *error_status);
t_light		*light_identifier(char **line, int *error_status);
t_camera	*camera_identifier(char **line, int *error_status);
t_cylinder	*cylinder_identifier(char **line, int *error_status);
t_plane		*plane_identifier(char **line, int *error_status);
t_sphere	*sphere_identifier(char **line, int *error_status);
int			get_vector(char *str, t_vectors *ret);
int			get_rgb(char *str, t_colors *ret);
int			get_coords(char *str, t_vectors *ret);

// gnl
char		*get_next_line(int fd);
char		*ft_stradd(char *s1, char *s2, int size);
char		*ft_strdupset(char const *s, int start, int stop);

// tmp
void		print_scene(t_scene *scene);

#endif