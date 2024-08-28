/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:42:55 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/28 15:40:52 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	check_file(char *file)
{
	char	*extension;

	if (!file || access(file, F_OK) == -1)
	{
		perror("Error accessing file");
		exit(EXIT_FAILURE);
	}
	extension = ft_strrchr(file, '.');
	if (!extension || ft_strcmp(extension, ".rt") != 0)
	{
		printf("Error: Incorrect file format. Expected .rt\n");
		exit(EXIT_FAILURE);
	}
}

t_scene	init_scene(t_scene scene)
{
	scene.objects = NULL;
	scene.hooks = NULL;
	scene.img = NULL;
	scene.mlx_ptr = NULL;
	scene.win_ptr = NULL;
	scene.objects = malloc(sizeof(t_object));
	if (!scene.objects)
		error("Memory allocation failed", &scene, NULL);
	scene.objects->spheres = NULL;
	scene.objects->planes = NULL;
	scene.objects->cylinders = NULL;
	return (scene);
}

void	parse_ambient_line(char *line, t_scene *scene, int *ambient_found)
{
	if (*ambient_found)
		error("Multiple ambient lighting definitions found", scene, line);
	parse_ambient(line, &scene->amblight, scene);
	*ambient_found = 1;
}

void	parse_camera_line(char *line, t_scene *scene, int *camera_found)
{
	if (*camera_found)
		error("Multiple camera definitions found", scene, line);
	parse_camera(line, &scene->camera, scene);
	*camera_found = 1;
}

void	parse_object_line(char *line, t_scene *scene)
{
	if (line[0] == 'p' && line[1] == 'l' && (line[2] == ' ' || line[2] == '\t'))
	{
		parse_plane(line, &scene->objects->planes, scene);
	}
	else if (line[0] == 'c' && line[1] == 'y'
		&& (line[2] == ' ' || line[2] == '\t'))
	{
		parse_cylinder(line, &scene->objects->cylinders, scene);
	}
	else if (line[0] == 's' && line[1] == 'p'
		&& (line[2] == ' ' || line[2] == '\t'))
	{
		parse_sphere(line, &scene->objects->spheres, scene);
	}
	else
	{
		error("Invalid scene description", scene,line);
	}
}
