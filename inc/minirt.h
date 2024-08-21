/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:42:57 by csturm            #+#    #+#             */
/*   Updated: 2024/08/21 13:02:05 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <mlx.h>
# include "mlx.h"

# define WIDTH 1000
# define HEIGHT 700
# define PI 3.14159265359
# define DIFFUSE 0.8

typedef struct s_coefficients
{
	float	a;
	float	b;
	float	c;
}	t_coefficients;

typedef struct s_hooks
{
	int	key_press;
	int	key_release;
	int	mouse_press;
	int	mouse_release;
	int	mouse_move;
}	t_hooks;

typedef struct s_img
{
	void	*img_ptr;
	char	*pxl;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	NONE
}	t_object_type;

typedef struct s_intersect_info
{
	t_object_type	type;
	void			*object;
	int				index;
}	t_intersect_info;

typedef struct s_color
{
	float	r;
	float	g;
	float	b;
}	t_color;

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}	t_ray;

typedef struct s_shade
{
	t_vector	ip;
	t_vector	normal;
	t_color		object_color;
}	t_shade;

typedef struct s_light_ray
{
	t_vector	direction;
	float		distance;
}	t_light_ray;

typedef struct s_sphere
{
	t_vector		center;
	float			radius;
	t_color			color;
	struct s_sphere	*next;
}	t_sphere;

typedef struct s_plane
{
	t_vector		point;
	t_vector		axis;
	t_color			color;
	struct s_plane	*next;
}	t_plane;

typedef struct s_cylinder
{
	t_vector			center;
	t_vector			axis;
	float				radius;
	float				height;
	t_color				color;
	struct s_cylinder	*next;
}	t_cylinder;

typedef struct s_amblight
{
	float	intensity;
	t_color	color;
}	t_amblight;

typedef struct s_light
{
	t_vector	position;
	float		intensity;
}	t_light;

typedef struct s_camera
{
	t_vector	center;
	t_vector	orientation;
	float		fov;
}	t_camera;

typedef struct s_object
{
	t_sphere	*spheres;
	t_plane		*planes;
	t_cylinder	*cylinders;
}	t_object;

typedef struct s_hit
{
	t_object_type	type;
	void			*object;
	float			t;
	int				index;
}	t_hit;

typedef struct s_scene
{
	t_object	*objects;
	t_amblight	amblight;
	t_light		light;
	t_camera	camera;
	int			width;
	int			height;
	int			objects_count;
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		*img;
	t_hooks		*hooks;
}	t_scene;

// error.c
void		error(char *message, t_scene *scene);

// events.c
void		event_loop(t_scene scene);

// find_object.c
t_hit		find_closest_object(t_scene scene, t_ray ray);

// intersect.c
float		intersect_sphere(t_sphere *sphere, t_ray ray);
float		intersect_plane(t_plane *plane, t_ray ray);
float		intersect_cylinder(t_cylinder *cylinder, t_ray ray);

// parse.c
t_scene		parse_scene(char *filename, t_scene scene);

// ray_utils.c
t_vector	normalise_vector(t_vector v);
t_vector	get_intersection_point(t_ray ray, float t);
t_vector	get_normal(t_vector v, t_hit hit);
t_vector	rotate_vector(t_vector v, t_vector orientation);

// ray_utils2.c
float		dot_product(t_vector a, t_vector b);
t_vector	cross_product(t_vector a, t_vector b);

// ray.c
t_color		trace_ray(t_scene scene, t_ray ray);
t_ray		get_ray(t_scene scene, int x, int y);

// render.c
void		render_scene(t_scene scene);

// shade.c
t_color		calc_shade(t_scene scene, t_shade shade, t_hit object_hit);

#endif