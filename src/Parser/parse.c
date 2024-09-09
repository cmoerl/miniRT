/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 12:18:53 by csturm            #+#    #+#             */
/*   Updated: 2024/09/09 11:02:38 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	parse_scene_line(char *line, t_scene *scene, t_flags *flags)
{
	int	i;

	i = 0;
	skip_whitespace(line, &i);
	if (line[i] == '\0' || line[i] == '\n')
		return ;
	if (line[i] == 'A')
	{
		parse_ambient_line(&line[i], scene, &flags->ambient_found);
	}
	else if (line[i] == 'C')
	{
		parse_camera_line(&line[i], scene, &flags->camera_found);
	}
	else if (line[i] == 'L')
	{
		parse_light_line(&line[i], scene, &flags->light_found);
	}
	else
	{
		parse_object_line(&line[i], scene);
	}
}

void	read_and_parse_lines(t_scene *scene, t_flags *flags)
{
	char	*line;

	line = get_next_line(scene->fd, 0);
	while (line != NULL)
	{
		parse_scene_line(line, scene, flags);
		free(line);
		line = get_next_line(scene->fd, 0);
	}
}

t_scene	parse_scene(char *file, t_scene scene)
{
	t_flags	flags;

	flags = (t_flags){0, 0, 0, 0, 0, 0};
	scene = init_scene(scene);
	scene.fd = open(file, O_RDONLY);
	if (scene.fd < 0)
		error("Could not open file", &scene, NULL);
	read_and_parse_lines(&scene, &flags);
	close(scene.fd);
	scene.fd = -1;
	check_essential_components(flags.ambient_found,
		flags.camera_found, flags.light_found, &scene);
	return (scene);
}
