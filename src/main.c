/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:56:02 by csturm            #+#    #+#             */
/*   Updated: 2024/09/02 16:33:33 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int	main(int argc, char **argv)
{
	t_scene	scene;

	scene = (t_scene){0};
	if (argc != 2)
	{
		printf("Usage: %s <scene.rt>\n", argv[0]);
		return (1);
	}
	check_file(argv[1]);
	scene = parse_scene(argv[1], scene);
	if (scene.objects == NULL)
	{
		error("No objects found in scene", &scene, NULL);
		return (1);
	}
    

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

	// init_scene_mlx(&scene);
	// render_scene(scene);
	// event_loop(scene);
	free_scene(&scene);
	return (0);
}
