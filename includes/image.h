#ifndef IMAGE_H
# define IMAGE_H

# include <stdint.h>

# define WHITE_SPACE "\t\n\v\f\r \0"

typedef struct s_image
{
	uint32_t	width;
	uint32_t	height;
	int			fd_image;
	uint8_t	max_color_value;
}				t_image;

void	init_image_info(char *file_path, t_image *image);

#endif