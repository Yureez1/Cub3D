/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:05:36 by leaugust          #+#    #+#             */
/*   Updated: 2025/07/17 14:08:14 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	handle_texture_line(t_texpath *texpath, char *line)
{
	if (!ft_strncmp(line, "NO", 2))
	{
		if (texpath->no)
			return (printf("Error: Duplicate NO\n"), 1);
		texpath->no = ft_strtrim(line + 2, " \t\n");
	}
	else if (!ft_strncmp(line, "SO", 2))
	{
		if (texpath->so)
			return (printf("Error: Duplicate SO\n"), 1);
		texpath->so = ft_strtrim(line + 2, " \t\n");
	}
	else if (!ft_strncmp(line, "WE", 2))
	{
		if (texpath->we)
			return (printf("Error: Duplicate WE\n"), 1);
		texpath->we = ft_strtrim(line + 2, " \t\n");
	}
	else if (!ft_strncmp(line, "EA", 2))
	{
		if (texpath->ea)
			return (printf("Error: Duplicate EA\n"), 1);
		texpath->ea = ft_strtrim(line + 2, " \t\n");
	}
	return (0);
}

int	handle_color_line(t_texpath *texpath, char *line)
{
	if (!ft_strncmp(line, "F ", 2))
		return (handle_floor(texpath, line));
	if (!ft_strncmp(line, "C ", 2))
		return (handle_ceiling(texpath, line));
	return (0);
}
