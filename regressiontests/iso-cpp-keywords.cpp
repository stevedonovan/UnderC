int main()
{
    signed signed_value = -4;
    if (signed_value != -4) return 1;
    signed int signed_int_value = -5;
    if (signed_int_value != -5) return 2;
    signed char signed_char_value = 6;
    if (signed_char_value != 6) return 3;
    signed short signed_short_value = 7;
    if (signed_short_value != 7) return 4;
    signed long signed_long_value = 8;
    if (signed_long_value != 8) return 5;
    wchar_t wide_value = 65;
    if (wide_value != 65) return 6;
    int bits = 3;
    int *null_pointer = NULL;
    if (null_pointer != NULL) return 7;
    bool alternatives = true and not false;

    bits and_eq 1;
    bits or_eq 2;
    bits xor_eq 1;
    int operator_values = (bits bitand 3) + (bits bitor 1) + (compl 0) +
                          (true or false) + (true xor false) + (true not_eq false);
    if (!alternatives) return 8;
    if (operator_values != 7) return 9;
    return 0;
}
