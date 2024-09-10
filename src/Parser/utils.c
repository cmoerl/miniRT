/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:51:44 by marianfurni       #+#    #+#             */
/*   Updated: 2024/09/10 15:32:51 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

// Helper function to skip whitespace
void	skip_whitespace(char *line, int *i)
{
	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
		(*i)++;
}

// Helper function to parse a float with validation
float	parse_float_with_check(char **line, int *i, t_scene *scene)
{
    int		start;
    int		dot_count = 0;
    float	value;

    start = *i;
    while ((*line)[*i] && (ft_isdigit((*line)[*i])
        || (*line)[*i] == '.' || (*line)[*i] == '-' || (*line)[*i] == '+'))
    {
        if ((*line)[*i] == '.')
            dot_count++;
        (*i)++;
    }
    if (start == *i || dot_count > 1)
        error("Error: Invalid character in camera definition", scene, *line);
    value = ft_atof(&(*line)[start]);
    if ((*line)[*i] == ',')
        (*i)++;
    skip_whitespace(*line, i);
    return (value);
}

// Helper function to validate the end of line
void	validate_end_of_line(char *line, int i, t_scene *scene)
{
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
		i++;
	if (line[i] != '\0')
		error("Invalid character in camera definition", scene, line);
}

// Helper function to print the parsed camera values
// void	print_camera(t_camera *camera)
// {
// 	printf("Parsed Camera:\n");
// 	printf("  Position: x=%f, y=%f, z=%f\n",
// 		camera->center.x, camera->center.y, camera->center.z);
// 	printf("  Orientation: x=%f, y=%f, z=%f\n",
// 		camera->orientation.x, camera->orientation.y, camera->orientation.z);
// 	printf("  FOV: %f\n", camera->fov);
// }
