#include "ArrayNode.h"
#include <stdlib.h>


ArrayNode* array_node_construct(unsigned long v) {
    ArrayNode* a = (ArrayNode*) malloc(sizeof(ArrayNode));
    a->value = v;
    a->has_next = 0;
    a->is_head = 0;
    return a;
}


ArrayNode* array_node_first() {
    ArrayNode* a = array_node_construct(0);
    a->is_head = 1;
    return a;
}


void array_node_set_next(ArrayNode* a, ArrayNode* n) {
    a->has_next = 1;
    a->next = (unsigned long) n;
}
