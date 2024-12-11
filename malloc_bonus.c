#include <stdlib.h>

void    *my_malloc(size_t size) 
{
    static int counter = 0;
    counter++;
    if (counter == 5) {
        return NULL;
    }
    return malloc(size);
}
# define malloc(size) my_malloc(size)