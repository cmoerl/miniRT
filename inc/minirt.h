/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:42:57 by csturm            #+#    #+#             */
/*   Updated: 2024/08/21 13:44:18 by mafurnic         ###   ########.fr       */
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
// # include <mlx.h>
// # include "mlx.h"
# include "..//libft/libft.h"

# define WIDTH 800
# define HEIGHT 600

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
	CYLINDER
}	t_object_type;

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

typedef struct s_rgb
{
    int r;
    int g;
    int b;
} t_rgb;


void		skip_whitespace(char *line, int *i);
void		print_camera(t_camera *camera);
float		parse_float_with_check(char **line, int *i);
void		skip_whitespacess(char **line, int *i);
void		parse_sphere(char *line, t_sphere **spheres);
void		parse_plane(char *line, t_plane **planes);
void		parse_cylinder(char *line, t_cylinder **cylinders);
void		parse_sphere(char *line, t_sphere **spheres);
void		parse_plane(char *line, t_plane **planes);
void		parse_ambient(char *line, t_amblight *ambient);
void		error(char *message, t_scene *scene);
void		check_file(char *file);
void		parse_camera(char *line, t_camera *camera);
void		parse_light(char *line, t_light *light);
void		error(char *message, t_scene *scene);
t_scene		parse_scene(char *filename, t_scene scene);

#endif