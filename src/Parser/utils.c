/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:51:44 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/20 12:41:40 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	skip_whitespace(char *line, int *i)
{
	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
		(*i)++;
}

// Helper function to skip whitespace
void skip_whitespacess(char **line, int *i)
{
    while ((*line)[*i] && ((*line)[*i] == ' ' || (*line)[*i] == '\t'))
        (*i)++;
}

// Helper function to parse a float with validation
float parse_float_with_check(char **line, int *i)
{
    int start = *i;
    float value;

    while ((*line)[*i] && (ft_isdigit((*line)[*i]) || (*line)[*i] == '.' || (*line)[*i] == '-' || (*line)[*i] == '+'))
        (*i)++;

    if (start == *i)
        error("Error: Invalid character in camera definition", NULL);

    value = ft_atof(&(*line)[start]);

    if ((*line)[*i] == ',')
        (*i)++;

    skip_whitespacess(line, i);

    return value;
}

// Helper function to print the parsed camera values
void	print_camera(t_camera *camera)
{
	printf("Parsed Camera:\n");
	printf("  Position: x=%f, y=%f, z=%f\n",
		camera->center.x, camera->center.y, camera->center.z);
	printf("  Orientation: x=%f, y=%f, z=%f\n",
		camera->orientation.x, camera->orientation.y, camera->orientation.z);
	printf("  FOV: %f\n", camera->fov);
}

