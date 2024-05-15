#define GARBAGE_COL_SIZE 100
#define GARBAGE_ERROR_EXPAND -2
#define GARBAGE_ERROR_CREATE -1
#define GARBAGE_SUCCESS 0

static int	*garbage_col_count(void)
{
	static int	count = 0;

	return (&count);
}

static int	*garbage_col_size(void)
{
	static int	count = GARBAGE_COL_SIZE;

	return (&count);
}

static void	***garbage_col_get(void)
{
	static void	**garbage = NULL;

	return (&garbage);
}

static int	ft_garbage_col_create(void)
{
	void	***garbage;

	garbage = garbage_col_get();
	if (*garbage)
		return (1);
	*garbage_col_count() = 0;
	*garbage = malloc(sizeof(void *) * GARBAGE_COL_SIZE);
	if (!*(garbage))
		return (0);
	return (1);
}

// returns 0 on success and otherwise the number of elements that were able to be added
// returns -1 when the garbage collector has not been created
// retuen -2 when the garbage collector is full and could not be realloced
static void	***ft_garbage_col_add(void *ptr)
{
	void	***garbage;
	void	**new_garbage;
	int		*count;

	garbage = garbage_col_get();
	if (!*garbage && !ft_garbage_col_create())
		return (garbage);
	count = garbage_col_count();
	if (*count >= *garbage_col_size())
	{
		new_garbage = realloc(*garbage, sizeof(void *)
				* (*garbage_col_size() * 2));
		if (!new_garbage)
			return (garbage);
		*garbage = new_garbage;
		*garbage_col_size() *= 2;
	}
	(*garbage)[(*count)++] = ptr;
	return (garbage);
}

static void	ft_garbage_col_clear(void)
{
	void	***garbage;
	int		*count;
	int		i;

	garbage = garbage_col_get();
	if (!*garbage)
		return ;
	count = garbage_col_count();
	i = 0;
	while (i < *count)
	{
		free((*garbage)[i]);
		i++;
	}
	free(*garbage);
	*garbage = NULL;
	*count = 0;
}

void	*ft_malloc(size_t size)
{
	void	*ptr;
	// int		err;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	ft_garbage_col_add(ptr);
	// err = ft_garbage_col_add(ptr);
	// if (err == GARBAGE_ERROR_EXPAND)
	// {
	// 	ft_garbage_col_clear();
	// 	free(ptr);
	// 	return (NULL);
	// }
	// else if (err == GARBAGE_ERROR_CREATE)
	// {
	// 	free(ptr);
	// 	return (NULL);
	// }
	return (ptr);
}

void	free_all(void)
{
	ft_garbage_col_clear();
}

void	set_ptr_to_nil(void *ptr)
{
	void	***garbage;
	int		i;

	i = 0;
	garbage = ft_garbage_col_add(NULL);
	while (1)
	{
		if ((*garbage)[i] == ptr)
		{
			(*garbage)[i] = NULL;
			return ;
		}
		i++;
	}
}

void	ft_free(void **ptr)
{
	if (ptr == NULL)
		return ;
	free(*ptr);
	set_ptr_to_nil(*ptr);
}

int main()
{
	char *str = ft_malloc(10);
	char *wow = ft_malloc(1);
	char *el = ft_malloc(1);
	str[0] = 'h';
	str[1] = '\0';
	// ft_free((void **) &(str));
	// ft_free((void **) &(wow));
	// ft_free((void **) &(el));
	free_all();
}