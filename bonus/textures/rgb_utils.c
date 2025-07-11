/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:12:10 by leaugust          #+#    #+#             */
/*   Updated: 2025/07/11 17:42:32 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int	convert_rgb(unsigned int r, unsigned int g, unsigned int b)
{
	if (r > 255 || g > 255 || b > 255)
		return (perror("RGB values must be between 0 and 255"), -1);
	return ((r << 16) | (g << 8) | b);
}

static void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

int	parse_rgb(const char *str, int *res)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (free_split(rgb), perror("Invalid RGB format"), 1);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (free_split(rgb), perror("RGB values must be between 0 and 255"),
			1);
	*res = convert_rgb(r, g, b);
	return (free_split(rgb), 0);
}

int	check_exist_textures(t_texpath *texpath)
{
	int	fd;

	fd = open(texpath->no, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening NO texture file"), 1);
	close(fd);
	fd = open(texpath->so, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening SO texture file"), 1);
	close(fd);
	fd = open(texpath->we, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening WE texture file"), 1);
	close(fd);
	fd = open(texpath->ea, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening EA texture file"), 1);
	close(fd);
	return (0);
}

int	check_xpm_file(const char *file_path)
{
	size_t		len;
	const char	*ext;

	len = ft_strlen(file_path);
	ext = file_path + len - 4;
	if (!file_path || ft_strlen(file_path) < 4)
		return (perror("Invalid file path"), 1);
	if (ft_strncmp(ext, ".xpm", 4) != 0 && ft_strncmp(ext, ".XPM", 4) != 0)
		return (perror("File is not a valid XPM file"), 1);
	return (0);
}
