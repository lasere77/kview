#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>

#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>

#define ALF		4278190080
#define RED		16711680
#define GREEN	65280 
#define BLUE	255
#define WHITE	-1

//get writable screen memory; uint32_t here for 32bit color
// A(alpha)	R(rouge) G(vers)  B(blue)
// 00000000 00000000 00000000 00000000
typedef struct	s_screen
{
	struct fb_var_screeninfo	var_info;			/*variable info device form ioctl*/
	uint32_t					*display;			/*shared memory mapped with the device*/
	size_t						screen_size;		/*sizeof mapped-memory*/
}								t_screen;

static inline uint32_t	get_pixel_addr(const t_screen *screen, const uint32_t h, const uint32_t w)
{
	return (w * screen->var_info.xres + h);
}

static void	rectangle_display(const t_screen *screen, const uint32_t x, const uint32_t y, const uint32_t w, const uint32_t h, const uint32_t color)
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

static void	get_device(t_screen *screen)
{
	int	fd_device;

	fd_device = open("/dev/fb0", O_RDWR);
	if (fd_device == -1)
	{
		write(2, "OPEN error\n", 12);
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

int	main(void)
{
	t_screen	screen;

	get_device(&screen);
	rectangle_display(&screen, 100, 100, 100, 100, RED);
	munmap(screen.display, screen.screen_size);
	return (0);
}
