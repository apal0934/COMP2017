#include <stdlib.h>


struct node {
	void* data;
	struct node *next;
	struct node *prev;
};

struct node* list_init(int value);

void list_add(struct node* head, int value);

void list_delete(struct node* head, struct node* n);

struct node* list_next(const struct node* n);
struct node* list_prev(const struct node* n);

void list_free(struct node* head);

struct node* list_init(int value) {
	struct node* head = malloc(sizeof(struct node));

	head->data = &value;
	head->next = NULL;
	
	return head;
}

void list_add(struct node* head, int value) {
	struct node *p;

	for (p = head; p->next != NULL; p = p->next) {
		continue;
	}

	p->next = malloc(sizeof(struct node));
	p->next->data = &value;
	p->next->prev = p;
	p->next->next = NULL;

}

void list_delete(struct node* head, struct node* n) {
	struct node *p;
	int found = 0;
	for (p = head; p->next != NULL; p = p->next) {
		if (p->next == n) {
			found = 1;
			break;
		}
	}

	if (found == 0) {
		return;
	}

	if (p->next->next == NULL) {
		p->next = NULL;
	} else {
		p->next->prev = p;
		p->next = p->next->next;
	}
	
	free(n);	
	
}

struct node* list_next(const struct node* n) {
	return n->next;
}

struct node* list_prev(const struct node* n) {
	return n->prev;
}

void list_free(struct node* head) {
	struct node *p;

	for (; head != NULL; head = p) {
		p = head->next;
		free(head->data);
		free(head);
	}
}

