/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:56:02 by csturm            #+#    #+#             */
/*   Updated: 2024/09/04 10:17:58 by mafurnic         ###   ########.fr       */
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
	init_scene_mlx(&scene);
	render_scene(scene);
	event_loop(scene);
	free_scene(&scene);
	return (0);
}
