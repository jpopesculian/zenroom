#ifdef ARCH_CORTEX
extern unsigned int _start_heap;
#define NULL (((void *)0))

void abort(void)
{
    while(1) {
        /* Panic! */
    }
}

void exit(int val)
{

}

void * _sbrk(unsigned int incr)
{
    static unsigned char *heap = (unsigned char *)&_start_heap;
    void *old_heap = heap;
    if (((incr >> 2) << 2) != incr)
        incr = ((incr >> 2) + 1) << 2;

    if (heap == NULL)
		heap = (unsigned char *)&_start_heap;
	else
        heap += incr;
    return old_heap;
}

void * _sbrk_r(unsigned int incr)
{
    static unsigned char *heap = NULL;
    void *old_heap = heap;
    if (((incr >> 2) << 2) != incr)
        incr = ((incr >> 2) + 1) << 2;

    if (old_heap == NULL)
		old_heap = heap = (unsigned char *)&_start_heap;
    heap += incr;
    return old_heap;
}
#endif
