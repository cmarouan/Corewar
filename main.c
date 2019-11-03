#include "libft.h"

int main()
{
	char *line;

	line = NULL;
	if (get_next_line(0, &line) > 0)
	{
		ft_putstr(line);
		ft_strdel(&line);
	}
	return (0);
}
