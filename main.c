#include "map.h"
#include <stdio.h>

int main() {
    map m;
    map_new(&m);

    map_set(&m, "key", &(int){1});
    map_set(&m, "key2", "l");

    printf("%d\n", *(int*)map_get(&m, "key"));
    printf("%s\n", (char*)map_get(&m, "key2"));

    map_free(&m);
}
