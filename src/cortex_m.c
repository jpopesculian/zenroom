#ifdef ARCH_CORTEX
void abort(void)
{
    while(1) {
        /* Panic! */
    }
}

void exit(int val)
{

}
#endif
