/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 12:18:53 by csturm            #+#    #+#             */
/*   Updated: 2024/08/21 18:49:03 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	parse_scene_line(char *line, t_scene *scene, int *ambient_found, int *camera_found, int *light_found)
{
	int	i;

	i = 0;
	skip_whitespace(line, &i);
	if (line[i] == '\0' || line[i] == '\n')
		return ;
	if (line[i] == 'A')
	{
		parse_ambient_line(&line[i], scene, ambient_found);
	}
	else if (line[i] == 'C')
	{
		parse_camera_line(&line[i], scene, camera_found);
	}
	else if (line[i] == 'L')
	{
		parse_light_line(&line[i], scene, light_found);
	}
	else
	{
		parse_object_line(&line[i], scene);
	}
}

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

t_scene	parse_scene(char *file, t_scene scene)
{
	int		fd;
	char	*line;
	int		ambient_found;
	int		camera_found;
	int		light_found;

	line = NULL;
	ambient_found = 0;
	camera_found = 0;
	light_found = 0;
	scene = init_scene(scene);
	check_file(file);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error("Could not open file", &scene);
	while ((line = get_next_line(fd)) != NULL)
	{
		parse_scene_line(line, &scene, &ambient_found,
			&camera_found, &light_found);
		free(line);
	}
	close(fd);
	check_essential_components(ambient_found,
		camera_found, light_found, &scene);
	return (scene);
}
