#include "list.h"
void list_add(struct List *dst, struct List *node)
{
	node->next = dst->next;
	(dst->next)->pre = node;
	dst->next = node;
	node->pre = dst;
}
void list_del(struct List *node)
{
	struct List *ret = node->pre;
	(node->next)->pre = ret;
	ret->next = node->next;
}
