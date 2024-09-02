/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:07:04 by marianfurni       #+#    #+#             */
/*   Updated: 2024/09/02 16:25:19 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	check_essential_components(int ambient_found,
			int camera_found, int light_found, t_scene *scene)
{
	if (!ambient_found)
		error("Missing ambient lighting definition", scene, NULL);
	if (!camera_found)
		error("Missing camera definition", scene, NULL);
	if (!light_found)
		error("Missing light definition", scene, NULL);
}

t_scene	init_and_check_file(char *file, t_scene scene)
{
	scene = init_scene(scene);
	check_file(file);
	return (scene);
}

void	parse_light_line(char *line, t_scene *scene, int *light_found)
{
	if (*light_found)
		error("Multiple light definitions found", scene, line);
	parse_light(line, scene);
	*light_found = 1;
}

// void	init_scene_mlx(t_scene *scene)
// {
// 	scene->mlx_ptr = mlx_init();
// 	if (!scene->mlx_ptr)
// 		error("Failed to initialize mlx", scene, NULL);
// 	scene->hooks = malloc(sizeof(t_hooks));
// 	if (!scene->hooks)
// 		error("Memory allocation failed", scene, NULL);
// 	scene->hooks->key_press = 0;
// 	scene->img = malloc(sizeof(t_img));
// 	if (!scene->img)
// 		error("Memory allocation failed", scene, NULL);
// 	scene->img->bits_per_pixel = 32;
// 	scene->img->line_length = WIDTH * 4;
// 	scene->img->endian = 0;
// 	scene->win_ptr = mlx_new_window(scene->mlx_ptr, WIDTH, HEIGHT, "MiniRT");
// 	if (!scene->win_ptr)
// 		error("Failed to create window", scene, NULL);
// 	scene->img->img_ptr = mlx_new_image(scene->mlx_ptr, WIDTH, HEIGHT);
// 	if (!scene->img->img_ptr)
// 		error("Failed to create image", scene, NULL);
// 	scene->img->pxl = mlx_get_data_addr(scene->img->img_ptr,
// 			&scene->img->bits_per_pixel, &scene->img->line_length,
// 			&scene->img->endian);
// 	if (!scene->img->pxl)
// 		error("Failed to get image data", scene, NULL);
// }
