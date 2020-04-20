#include "lem_visual.h"

float	rand_minus_one_one(void)
{
	return ((float)rand() / (float)RAND_MAX * (rand() > RAND_MAX / 2 ? 1 : -1));
}

float	rand_zero_one(void)
{
	return ((float)rand() / (float)RAND_MAX);
}

void	swap_ar(int32_t *ar)
{
	int32_t	sw;

	sw = ar[0];
	ar[0] = ar[1];
	ar[1] = sw;
}

int8_t	check_loadfile(char **argv)
{
	int32_t		i;
	struct stat	st;

	i = 0;
	while (g_lem_loadfile[i][0])
	{
		if (stat(g_lem_loadfile[i], &st) == -1)
		{
			ft_printf(F_RED "%s: %s: %s\n" NONE, argv[0], g_lem_loadfile[i],
															strerror(errno));
			return (0);
		}
		i++;
	}
	return (1);
}
