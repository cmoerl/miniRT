/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:03:05 by csturm            #+#    #+#             */
/*   Updated: 2024/08/23 14:36:35 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// putting the pixel on the screen
void	put_pixel(int x, int y, t_color color, t_scene scene)
{
	int	position;

	position = y * scene.img->line_length + x * (scene.img->bits_per_pixel / 8);
	*(unsigned int *)(scene.img->pxl + position)
		= (int)(color.r) << 16 | (int)(color.g) << 8 | (int)(color.b);
}

void	print_input(t_scene scene)
{
	printf("Ambient light: %f\n", scene.amblight.intensity);
	printf("Camera position: %f, %f, %f\n", scene.camera.center.x, scene.camera.center.y, scene.camera.center.z);
	printf("Camera orientation: %f, %f, %f\n", scene.camera.orientation.x, scene.camera.orientation.y, scene.camera.orientation.z);
	printf("Camera FOV: %f\n", scene.camera.fov);
	printf("Light position: %f, %f, %f\n", scene.light.position.x, scene.light.position.y, scene.light.position.z);
	printf("Light intensity: %f\n", scene.light.intensity);
	printf("Sphere position: %f, %f, %f\n", scene.objects->spheres->center.x, scene.objects->spheres->center.y, scene.objects->spheres->center.z);
	printf("Sphere radius: %f\n", scene.objects->spheres->radius);
	printf("Sphere color: %f, %f, %f\n", scene.objects->spheres->color.r, scene.objects->spheres->color.g, scene.objects->spheres->color.b);
}

// initialising the ray
// interating over each pixel
// getting the ray for each pixel
// tracing the ray
// putting the color on the screen
// showing the image
void	render_scene(t_scene scene)
{
	t_ray	ray;
	t_color	color;
	int		x;
	int		y;

	x = 0;
	y = 0;
	ray = (t_ray){(t_vector){0, 0, 0}, (t_vector){0, 0, 0}};
	print_input(scene);
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = get_ray(scene, x, y);
			color = trace_ray(scene, ray);
			put_pixel(x, y, color, scene);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(scene.mlx_ptr,
		scene.win_ptr, scene.img->img_ptr, 0, 0);
}
