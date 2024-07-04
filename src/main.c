/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:56:02 by csturm            #+#    #+#             */
/*   Updated: 2024/07/04 12:51:36 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void init_img(t_scene *scene)
{
    scene->img = malloc(sizeof(t_img));
    if (!scene->img)
        error("Error: Failed to allocate memory for image\n", scene);
    scene->img->bits_per_pixel = 32;
    scene->img->line_length = WIDTH * 4;
    scene->img->endian = 0;
    scene->img->img_ptr = mlx_new_image(scene->mlx_ptr, WIDTH, HEIGHT);
    scene->img->pxl = mlx_get_data_addr(scene->img->img_ptr, &scene->img->bits_per_pixel, &scene->img->line_length, &scene->img->endian);
}

t_sphere    *init_sphere(void)
{
    t_sphere *sphere;

    sphere = malloc(sizeof(t_sphere));
    if (!sphere)
        error("Error: Failed to allocate memory for sphere\n", NULL);
    sphere->center.x = 0;
    sphere->center.y = 0;
    sphere->center.z = 0;
    sphere->radius = 1;
    sphere->color.r = 255;
    sphere->color.g = 0;
    sphere->color.b = 0;
    sphere->next = NULL;
    return (sphere);
}

t_plane    *init_plane(void)
{
    t_plane *plane;

    plane = malloc(sizeof(t_plane));
    if (!plane)
        error("Error: Failed to allocate memory for plane\n", NULL);
    plane->point.x = 0;
    plane->point.y = 0;
    plane->point.z = 0;
    plane->axis.x = 0;
    plane->axis.y = 1;
    plane->axis.z = 0;
    plane->color.r = 0;
    plane->color.g = 255;
    plane->color.b = 0;
    plane->next = NULL;
    return (plane);
}

t_cylinder    *init_cylinder(void)
{
    t_cylinder *cylinder;

    cylinder = malloc(sizeof(t_cylinder));
    if (!cylinder)
        error("Error: Failed to allocate memory for cylinder\n", NULL);
    cylinder->center.x = 0;
    cylinder->center.y = 0;
    cylinder->center.z = 0;
    cylinder->axis.x = 0;
    cylinder->axis.y = 1;
    cylinder->axis.z = 0;
    cylinder->radius = 1;
    cylinder->height = 1;
    cylinder->color.r = 0;
    cylinder->color.g = 0;
    cylinder->color.b = 255;
    cylinder->next = NULL;
    return (cylinder);
}

void init_objects(t_scene *scene)
{
    scene->objects = malloc(sizeof(t_object));
    if (!scene->objects)
        error("Error: Failed to allocate memory for objects\n", scene);
    scene->objects->spheres = init_sphere();
    scene->objects->planes = init_plane();
    scene->objects->cylinders = init_cylinder();
}

void init_hooks(t_scene *scene)
{
    scene->hooks = malloc(sizeof(t_hooks));
    if (!scene->hooks)
        error("Error: Failed to allocate memory for hooks\n", scene);
    scene->hooks->key_press = 0;
    scene->hooks->key_release = 0;
    scene->hooks->mouse_press = 0;
    scene->hooks->mouse_release = 0;
    scene->hooks->mouse_move = 0;
}

void init_amblight(t_scene *scene)
{
    scene->amblight.intensity = 0.1;
    scene->amblight.color.r = 255;
    scene->amblight.color.g = 255;
    scene->amblight.color.b = 255;
}

void init_light(t_scene *scene)
{
    scene->light.position.x = 0;
    scene->light.position.y = 0;
    scene->light.position.z = 0;
    scene->light.intensity = 0.5;
}

void init_camera(t_scene *scene)
{
    scene->camera.center.x = 0;
    scene->camera.center.y = 0;
    scene->camera.center.z = 0;
    scene->camera.orientation.x = 0;
    scene->camera.orientation.y = 0;
    scene->camera.orientation.z = 0;
    scene->camera.fov = 60;
}

void init_scene(t_scene *scene)
{
    init_objects(scene);
    init_img(scene);
    init_hooks(scene);
    init_amblight(scene);
    init_light(scene);
    init_camera(scene);
    scene->width = WIDTH;
    scene->height = HEIGHT;
    scene->mlx_ptr = mlx_init();
    scene->win_ptr = mlx_new_window(scene->mlx_ptr, WIDTH, HEIGHT, "MiniRT");
}

// t_scene parse_scene(char *file, t_scene scene)
// {
//     char    *file_name;

//     file_name = file;
//     init_scene(&scene);
//     return (scene);
// }

int main(int argc, char **argv)
{
    t_scene scene;

    if (argc != 2)
    {
        write(1, "Error: Invalid number of arguments\n", 36);
        return (1);
    }
    // scene = parse_scene(argv[1], scene);
    if (argv[0] != 0)
        printf("Hello, World!\n");
    init_scene(&scene);
    render_scene(scene);
    event_loop(scene);
    return (0);
}