#include "ft_nm.h"

static char	*set_get_error_string(const char *error)
{
	static char	*err_str = NULL;

	if (error)
	{	free(err_str);
		err_str = ft_strdup(error);
	}
	return (err_str);
}

int	set_error(const char *error_str, int error_code)
{
	set_get_error_string(error_str);
	return (error_code);
}

char	*get_error(void)
{
	return (set_get_error_string(NULL));
}
