#include <underc/ucdl.h>
#include <stdio.h>

struct NativePair {
    int integer;
    int second;
};
static int seen_first, seen_second;

static NativePair make_pair(int integer, int second)
{
    seen_first = integer;
    seen_second = second;
    NativePair value = {integer,second};
    return value;
}

static int pair_total(NativePair value)
{
    return value.integer + value.second;
}

int main()
{
    if (!uc_init(NULL,0)) return 1;
    int ok = 0;
    if (!uc_exec("struct NativePair { int integer; int second; };")) return 2;
    char make_declaration[] = "NativePair make_pair(int integer,int second);";
    char total_declaration[] = "int pair_total(NativePair value);";
    if (!uc_import(make_declaration,reinterpret_cast<void *>(&make_pair))) return 3;
    if (!uc_import(total_declaration,reinterpret_cast<void *>(&pair_total))) return 4;
    if (uc_bind_variable("aggregate_ok",UC_TYPE_INT,&ok) != UC_STATUS_OK) return 5;
    if (!uc_exec("NativePair p; p.integer=7; p.second=5; aggregate_ok=(pair_total(p)==12);")) {
        char error[256] = {0}; uc_error(error,sizeof(error));
        fprintf(stderr,"aggregate argument: %s\n",error); return 8;
    }
    if (!ok) return 9;
    if (!uc_exec("make_pair(11,13);")) return 10;
    if (seen_first != 11 || seen_second != 13) return 11;
    uc_finis();
    if (!ok) return 7;
    puts("libffi aggregate passed");
    return 0;
}
