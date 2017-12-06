#ifndef __LIST__
#define __LIST__
#define LIST_INIT(x) {x->pre = x; x->next = x;}
struct List{
	struct List *pre;
	struct List *next;
};

void list_add(struct List *dst, struct List *node);
void list_del(struct List *node);

#endif
