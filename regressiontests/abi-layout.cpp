enum AbiEnum { ABI_ZERO };
int main()
{
  printf("abi-sizes=%d,%d,%d,%d\n",
         sizeof(int), sizeof(long), sizeof(AbiEnum), sizeof(void *));
  return 0;
}
