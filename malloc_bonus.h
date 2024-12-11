
#ifndef MALLOC_H
# define MALLOC_H
void    *my_malloc(size_t size);

# define malloc(size) my_malloc(size)
#endif