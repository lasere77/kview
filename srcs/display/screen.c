#include "screen.h"

static inline uint32_t	get_pixel_addr(const t_screen *screen, const uint32_t h, const uint32_t w)
{
	return (w * screen->var_info.xres + h);
}

void	rectangle_display(const t_screen *screen, const uint32_t x, const uint32_t y, const uint32_t w, const uint32_t h, const uint32_t color)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			screen->display[get_pixel_addr(screen, x + j, y + i)] = color;
			j++;
		}
		i++;
	}
}

void	get_device(t_screen *screen)
{
	int	fd_device;

	fd_device = open("/dev/fb0", O_RDWR);
	if (fd_device == -1)
	{
		write(2, "OPEN error\n", 11);
		exit(1);
	}
	// get variable info from the file(/dev/fb0)
	ioctl(fd_device, FBIOGET_VSCREENINFO, &screen->var_info);
	// set resolution/dpi/color depth/.. in varInfo, then write it back
	ioctl(fd_device, FBIOPUT_VSCREENINFO, &screen->var_info);
	screen->screen_size = screen->var_info.xres * screen->var_info.yres * screen->var_info.bits_per_pixel / 8;
	screen->display = mmap(0, screen->screen_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_device, 0);
	close(fd_device);
	if (!screen->display)
		exit(1);
}
