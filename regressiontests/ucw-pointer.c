int main()
{
    int value = 42;
    int *pointer = &value;
    printf("pointer-value=%d\n", *pointer);
    return *pointer == 42 ? 0 : 1;
}
