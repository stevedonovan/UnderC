#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <stdio.h>

int main()
{
    std::vector<int> values;
    values.push_back(4);
    values.push_back(2);
    std::map<std::string,int> counts;
    counts["items"] = values.size();
    std::sort(values.begin(),values.end());
    printf("%s count=%d first=%d uclstl-search-ok\n",
           "items",counts["items"],values[0]);
    return 0;
}
