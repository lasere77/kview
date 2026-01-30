#ifndef IMAGE_H
# define IMAGE_H

# include <stdint.h>

typedef struct s_image
{
	uint32_t	width;
	uint32_t	height;
	uint32_t	max_color_value;
	int			fd_image;
}				t_image;

void	init_image_info(char *file_path, t_image *image);

#endif