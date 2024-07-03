/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:56:02 by csturm            #+#    #+#             */
/*   Updated: 2024/07/03 12:58:55 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void init_img(t_scene *scene)
{
    scene->img = malloc(sizeof(t_img));
    if (!scene->img)
        error("Error: Failed to allocate memory for image\n", scene);
    scene->img->img_ptr = mlx_new_image(scene->mlx_ptr, WIDTH, HEIGHT);
    scene->img->pxl = mlx_get_data_addr(scene->img->img_ptr, &scene->img->bits_per_pixel, &scene->img->line_length, &scene->img->endian);
}

void init_objects(t_scene *scene)
{
    scene->objects = malloc(sizeof(t_object));
    if (!scene->objects)
        error("Error: Failed to allocate memory for objects\n", scene);
    scene->objects->type = SPHERE;
    scene->objects->color.r = 255;
    scene->objects->color.g = 0;
    scene->objects->color.b = 0;
    scene->objects->position.x = 0;
    scene->objects->position.y = 0;
    scene->objects->position.z = 0;
    scene->objects->size = 1;
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
    scene->amblight = malloc(sizeof(t_amblight));
    if (!scene->amblight)
        error("Error: Failed to allocate memory for ambient light\n", scene);
    scene->amblight->intensity = 0.1;
    scene->amblight->color.r = 255;
    scene->amblight->color.g = 255;
    scene->amblight->color.b = 255;
}

void init_light(t_scene *scene)
{
    scene->light = malloc(sizeof(t_light));
    if (!scene->light)
        error("Error: Failed to allocate memory for light\n", scene);
    scene->light->position.x = 0;
    scene->light->position.y = 0;
    scene->light->position.z = 0;
    scene->light->intensity = 0.5;
    scene->light->color.r = 255;
    scene->light->color.g = 255;
    scene->light->color.b = 255;
}

void init_camera(t_scene *scene)
{
    scene->camera = malloc(sizeof(t_camera));
    if (!scene->camera)
        error("Error: Failed to allocate memory for camera\n", scene);
    scene->camera->position.x = 0;
    scene->camera->position.y = 0;
    scene->camera->position.z = 0;
    scene->camera->direction.x = 0;
    scene->camera->direction.y = 0;
    scene->camera->direction.z = 0;
    scene->camera->fov = 60;
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

t_scene parse_scene(char *file, t_scene scene)
{
    init_scene(&scene);
    return (scene);
}

int main(int argc, char **argv)
{
    t_scene scene;

    if (argc != 2)
    {
        printf(stderr, "Error: Wrong number of arguments\n");
        return (1);
    }
    scene = parse_scene(argv[1], scene);
    render_scene(scene);
    event_loop(scene);
    return (0);
}