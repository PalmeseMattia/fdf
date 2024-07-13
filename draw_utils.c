typedef struct s_pixel
{
	char	*r;
	char	*g;
	char	*b;
	char	*a;
}	t_pixel;

t_pixel	get_pixel(char *p_pixel)
{
	t_pixel	result;

	result.r = p_pixel;
	result.g = p_pixel + 1;
	result.b = p_pixel + 2;
	result.a = p_pixel + 3;
	return (result);
}


