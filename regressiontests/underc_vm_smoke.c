int main()
{
    int value = 40;
    int *pointer = &value;
    *pointer = *pointer + 2;
    printf("vm-value=%d\n", value);
    return value == 42 ? 0 : 1;
}
