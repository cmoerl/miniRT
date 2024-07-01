/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:42:57 by csturm            #+#    #+#             */
/*   Updated: 2024/07/01 11:28:35 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <mlx.h>
#include "mlx.h"

#define WIDTH 800
#define HEIGHT 600

typedef struct s_hooks
{
    int key_press;
    int key_release;
    int mouse_press;
    int mouse_release;
    int mouse_move;
} t_hooks;

typedef struct s_img
{
    void *img_ptr;
    char *pxl;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_img;

typedef enum e_object_type
{
    SPHERE,
    PLANE,
    CYLINDER
} t_object_type;

typedef struct s_color
{
    float r;
    float g;
    float b;
} t_color;

typedef struct s_vector
{
    float x;
    float y;
    float z;
    struct s_vector *dir;
} t_vector;

typedef struct s_sphere
{
    t_vector center;
    float radius;
    t_color color;
} t_sphere;

typedef struct s_plane
{
    t_vector center;
    t_vector normal;
    t_color color;
} t_plane;

typedef struct s_cylinder
{
    t_vector center;
    t_vector normal;
    float radius;
    float height;
    t_color color;
} t_cylinder;

typedef struct s_amblight
{
    float intensity;
    t_color color;
} t_amblight;

typedef struct s_light
{
    t_vector center;
    float intensity;
} t_light;

typedef struct s_camera
{
    t_vector center;
    t_vector normal;
    float fov;
} t_camera;

typedef struct s_object
{
    t_object_type type;
    t_color color;
    union {
        t_sphere sphere;
        t_plane plane;
        t_cylinder cylinder;
    };
} t_object;

typedef struct s_scene
{
    t_object *objects;
    t_amblight amblight;
    t_light light;
    t_camera camera;
    int width;
    int height;
    int objects_count;
    void *mlx_ptr;
    void *win_ptr;
    t_img *img;
    t_hooks *hooks;
} t_scene;

t_scene parse_scene(char *filename, t_scene scene);
void render_scene(t_scene scene);
void    error(char *message, t_scene *scene);
float   intersect_sphere(t_sphere sphere, t_vector ray);
float   intersect_plane(t_plane plane, t_vector ray);
float   intersect_cylinder(t_cylinder cylinder, t_vector ray);
t_color trace_ray(t_scene scene, t_vector ray);
t_vector    get_ray(t_scene scene, int x, int y);
float   dot_product(t_vector a, t_vector b);
void    event_loop(t_scene scene);

#endif