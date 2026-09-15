int main()
{
    if (_ffi_sum8(1, 2, 3, 4, 5, 6, 7, 8) != 36) return 1;
    return _ffi_order8(1, 2, 3, 4, 5, 6, 7, 8) == 1793 ? 0 : 2;
}
