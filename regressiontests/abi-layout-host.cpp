#include <underc/ucdl.h>
#include <stddef.h>
#include <stdio.h>

struct HostLayout {
    char tag;
    int count;
    double value;
    void *pointer;
};

static int check_layout(HostLayout *value)
{
    return value && value->tag == 'Q' && value->count == 37 &&
           value->value == 2.5 && value->pointer == value;
}

int main()
{
    if (!uc_init(NULL,0)) return 1;
    int ok = 0;
    int host_size = static_cast<int>(sizeof(HostLayout));
    int count_offset = static_cast<int>(offsetof(HostLayout,count));
    int value_offset = static_cast<int>(offsetof(HostLayout,value));
    int pointer_offset = static_cast<int>(offsetof(HostLayout,pointer));
    if (uc_bind_variable("layout_ok",UC_TYPE_INT,&ok) != UC_STATUS_OK ||
        uc_bind_variable("host_size",UC_TYPE_INT,&host_size) != UC_STATUS_OK ||
        uc_bind_variable("count_offset",UC_TYPE_INT,&count_offset) != UC_STATUS_OK ||
        uc_bind_variable("value_offset",UC_TYPE_INT,&value_offset) != UC_STATUS_OK ||
        uc_bind_variable("pointer_offset",UC_TYPE_INT,&pointer_offset) != UC_STATUS_OK)
        return 2;
    if (!uc_exec("struct HostLayout { char tag; int count; double value; void *pointer; };")) return 3;
    char declaration[] = "int check_layout(HostLayout *value);";
    if (!uc_import(declaration,reinterpret_cast<void *>(&check_layout))) return 4;
    const char program[] =
      "HostLayout layout; layout.tag='Q'; layout.count=37; layout.value=2.5; layout.pointer=&layout;"
      "layout_ok=(sizeof(HostLayout)==host_size && "
      "((char*)&layout.count-(char*)&layout)==count_offset && "
      "((char*)&layout.value-(char*)&layout)==value_offset && "
      "((char*)&layout.pointer-(char*)&layout)==pointer_offset && check_layout(&layout));";
    if (!uc_exec(program)) return 5;
    uc_finis();
    if (!ok) return 6;
    puts("host layout passed");
    return 0;
}
