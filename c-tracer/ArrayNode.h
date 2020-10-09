#ifndef ARRAYNODE_H_
#define ARRAYNODE_H_ value


typedef struct {
    unsigned long value;
    unsigned long next;
    int has_next;
    int is_head;
} ArrayNode;


ArrayNode* array_node_create(unsigned long v);
ArrayNode* array_node_first();
void array_node_set_next(ArrayNode* a, ArrayNode* n);
int array_node_count(ArrayNode* head);


#endif
