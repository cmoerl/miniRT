/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 23:32:14 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/21 13:41:23 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void parse_single_position(char *line, int *i, float *position_component)
{
    int start = *i;
    while (line[*i] && (ft_isdigit(line[*i]) || line[*i] == '.' || line[*i] == '-' || line[*i] == '+'))
        (*i)++;
    if (start == *i)
        error("Invalid character in light definition", NULL);
    *position_component = ft_atof(&line[start]);
    if (line[*i] == ',')
        (*i)++;
}

void parse_position(char *line, int *i, t_light *light)
{
    parse_single_position(line, i, &light->position.x);
    parse_single_position(line, i, &light->position.y);
    parse_single_position(line, i, &light->position.z);
}

void parse_intensity_light(char *line, int *i, t_light *light)
{
    int start = *i;
    while (line[*i] && (ft_isdigit(line[*i]) || line[*i] == '.' || line[*i] == '-' || line[*i] == '+'))
        (*i)++;
    if (start == *i)
        error("Invalid character in light definition", NULL);
    light->intensity = ft_atof(&line[start]);
    if (light->intensity < 0.0 || light->intensity > 1.0)
        error("Light intensity out of range [0.0, 1.0]", NULL);
}

void parse_single_color_component(char *line, int *i, int *color_component)
{
    int start = *i;
    while (line[*i] && ft_isdigit(line[*i]))
        (*i)++;
    if (start == *i)
        error("Invalid character in light definition", NULL);
    *color_component = ft_atoi(&line[start]);
    if (line[*i] == ',')
        (*i)++;
}

void parse_rgb(char *line, int *i, int *r, int *g, int *b)
{
    parse_single_color_component(line, i, r);
    parse_single_color_component(line, i, g);
    parse_single_color_component(line, i, b);

    if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
        error("Light color values out of range [0, 255]", NULL);
}

void parse_light_properties(char *line, int *i, t_light *light, int *r, int *g, int *b)
{
    skip_whitespace(line, i);
    parse_position(line, i, light);
    skip_whitespace(line, i);
    parse_intensity_light(line, i, light);
    skip_whitespace(line, i);
    if (line[*i])
        parse_rgb(line, i, r, g, b);
    else
    {
        *r = 255;
        *g = 255;
        *b = 255;
    }
}

void parse_light(char *line, t_light *light)
{
    int i = 0;
    int r, g, b;

    skip_whitespace(line, &i);
    if (line[i] != 'L')
        error("Missing 'L' identifier for light", NULL);
    i++;
    parse_light_properties(line, &i, light, &r, &g, &b);
    while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
        i++;
    if (line[i] != '\0')
        error("Invalid character in light definition", NULL);

    printf("Parsed Light:\n");
    printf("  Position: x=%f, y=%f, z=%f\n", light->position.x, light->position.y, light->position.z);
    printf("  Intensity: %f\n", light->intensity);
    printf("  Color: r=%d, g=%d, b=%d\n", r, g, b);
}