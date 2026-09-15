int main()
{
    int *null_pointer = NULL;
    if (null_pointer != NULL) return 1;
    signed signed_value = -4;
    if (signed_value != -4) return 2;
    signed char signed_char_value = 5;
    if (signed_char_value != 5) return 3;
    return 0;
}
