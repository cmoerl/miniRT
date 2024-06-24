/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:42:57 by csturm            #+#    #+#             */
/*   Updated: 2024/06/21 13:16:13 by csturm           ###   ########.fr       */
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

typedef struct s_scene
{
    t_sphere *spheres;
    t_plane *planes;
    t_cylinder *cylinders;
    t_amblight amblight;
    t_light light;
    t_camera camera;
    int width;
    int height;
} t_scene;

t_scene parse_scene(char *filename, t_scene scene);
void render_scene(t_scene scene);
void    error(char *message, t_scene *scene);

#endif