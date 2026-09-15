int main()
{
    int value = 7;
    int *p1 = &value;
    int **p2 = &p1;
    int ***p3 = &p2;
    int ****p4 = &p3;
    int *****p5 = &p4;
    int ******p6 = &p5;
    return ******p6 == 7 ? 0 : 1;
}
