/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:07:04 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/23 13:52:39 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	check_essential_components(int ambient_found,
			int camera_found, int light_found, t_scene *scene)
{
	if (!ambient_found)
		error("Missing ambient lighting definition", scene);
	if (!camera_found)
		error("Missing camera definition", scene);
	if (!light_found)
		error("Missing light definition", scene);
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
		error("Multiple light definitions found", scene);
	parse_light(line, &scene->light);
	*light_found = 1;
}
