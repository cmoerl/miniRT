/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:56:02 by csturm            #+#    #+#             */
/*   Updated: 2024/08/26 11:32:52 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"


int main(int argc, char **argv)
{
    t_scene scene = {0};

    if (argc != 2)
    {
        printf("Usage: %s <scene.rt>\n", argv[0]);
        return 1;
    }

    // Test check_file function
    check_file(argv[1]);

    // If the file is valid, proceed with parsing
    scene = parse_scene(argv[1], scene);
    if(scene.objects == NULL)
    {
        error("No objects found in scene", &scene);
        return 1;
    }

    // // Print parsed ambient lighting for testing
    // printf("Ambient lighting intensity: %f\n", scene.amblight.intensity);
    // printf("Ambient lighting color: %f, %f, %f\n", scene.amblight.color.r, scene.amblight.color.g, scene.amblight.color.b);

    // // Print parsed camera for testing
    // printf("Camera position: %f, %f, %f\n", scene.camera.center.x, scene.camera.center.y, scene.camera.center.z);
    // printf("Camera orientation: %f, %f, %f\n", scene.camera.orientation.x, scene.camera.orientation.y, scene.camera.orientation.z);
    // printf("Camera FOV: %f\n", scene.camera.fov);

    // // Print parsed light for testing
    // printf("Light position: %f, %f, %f\n", scene.light.position.x, scene.light.position.y, scene.light.position.z);
    // printf("Light intensity: %f\n", scene.light.intensity);

    // Print parsed planes for testing
    t_plane *plane = scene.objects->planes;
    while (plane)
    {
        printf("Plane point: %f, %f, %f\n", plane->point.x, plane->point.y, plane->point.z);
        printf("Plane axis: %f, %f, %f\n", plane->axis.x, plane->axis.y, plane->axis.z);
        printf("Plane color: %f, %f, %f\n", plane->color.r, plane->color.g, plane->color.b);
        plane = plane->next;
    }

    // Print parsed cylinders for testing
    t_cylinder *cylinder = scene.objects->cylinders;
    while (cylinder)
    {
        printf("Cylinder center: %f, %f, %f\n", cylinder->center.x, cylinder->center.y, cylinder->center.z);
        printf("Cylinder axis: %f, %f, %f\n", cylinder->axis.x, cylinder->axis.y, cylinder->axis.z);
        printf("Cylinder radius: %f\n", cylinder->radius);
        printf("Cylinder height: %f\n", cylinder->height);
        printf("Cylinder color: %f, %f, %f\n", cylinder->color.r, cylinder->color.g, cylinder->color.b);
        cylinder = cylinder->next;
    }

    // Print parsed spheres for testing
    t_sphere *sphere = scene.objects->spheres;
    while (sphere)
    {
        printf("Sphere center: %f, %f, %f\n", sphere->center.x, sphere->center.y, sphere->center.z);
        printf("Sphere radius: %f\n", sphere->radius);
        printf("Sphere color: %f, %f, %f\n", sphere->color.r, sphere->color.g, sphere->color.b);
        sphere = sphere->next;
    }

    // scene.mlx_ptr = mlx_init();
    // scene.hooks = malloc(sizeof(t_hooks));
    // // if (!scene.hooks)
    // //     error("Error: Failed to allocate memory for hooks\n", scene);
    // scene.hooks->key_press = 0;
    // scene.hooks->key_release = 0;
    // scene.hooks->mouse_press = 0;
    // scene.hooks->mouse_release = 0;
    // scene.hooks->mouse_move = 0;

    // scene.img = malloc(sizeof(t_img));
    // // if (!scene.img)
    // //     error("Error: Failed to allocate memory for image\n", scene);
    // scene.img->bits_per_pixel = 32;
    // scene.img->line_length = WIDTH * 4;
    // scene.img->endian = 0;
    // scene.img->img_ptr = mlx_new_image(scene.mlx_ptr, WIDTH, HEIGHT);
    // scene.img->pxl = mlx_get_data_addr(scene.img->img_ptr, &scene.img->bits_per_pixel, &scene.img->line_length, &scene.img->endian);

    // scene.win_ptr = mlx_new_window(scene.mlx_ptr, WIDTH, HEIGHT, "MiniRT");
    
    // scene = parse_scene(argv[1], scene);
    // render_scene(scene);
    // event_loop(scene);

       // Free the allocated scene memory before exiting
    free_scene(&scene);
    return 0;
}