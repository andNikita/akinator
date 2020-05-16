#include "st.h"

#define NBranch2 2
#define NBranch1 1
#define NBranch0 0
#define QBracket 5

typedef int data_t;



struct Node {
	data_t data;
	struct Node* left;
	struct Node* right;
};
typedef struct Node Node;

void delete_node(Node* n);
Node* add_node(Node* n, data_t data);
void visit(Node* n, bool(*func)(Node* n));
bool Print_node(Node* n);
void print_bracket(stack_t* st_bracket);
bool  Find_node(Node* n);

bool  Find_node(Node* n) {
	if (x_node == n->data) {
		printf("find\n");
		return 0;
	}
	return 1;
}

void visit(Node* n, bool(*func)(Node* n)) {
	//if (!func(n))
	//	return;
	if (n) {
		if ((*func)(n)){
			visit(n->left, func);
			visit(n->right, func);
		}
	}
	return;
}

void delete_node(Node* n)
{
	if (n != NULL) {
		delete_node(n->right);
		delete_node(n->left);
		n->left = NULL;
		n->right = NULL;
		free(n);
	}
}

Node* add_node(Node* n, data_t data) {
	if (n == NULL) {
		n = (Node*) calloc(1, sizeof(Node));
		n->data = data;
		n->left = NULL;
		n->right = NULL;
		return n;
	}
	else if (n->right == NULL)
		n->right = add_node(n->right, data);
	else if (n->left == NULL)
		n->left = add_node(n->left, data);
	else
		printf("error in add_node");

	return n;
}

bool Print_node(Node* n) {
	assert(n);

		printf(" (%d", n->data);
		if (n->left == NULL && n->right == NULL) {
			push(&st_bracket, NBranch0);
		}
		else if (n->left == NULL && n->right != NULL) {
			printf(" []");
			push(&st_bracket, NBranch1);
			
		}
		else if (n->left != NULL && n->right == NULL) {
			push(&st_bracket, NBranch1);
			Flag_bracket = 1;
		} else
			push(&st_bracket, NBranch2);

	//stack_dump(&st_bracket);

	print_bracket(&st_bracket);
	if (Flag_bracket) {
		Flag_bracket = 0;
		push(&st_bracket, QBracket);
	}
	stack_dump(&st_bracket);

	return 1;
}

void print_bracket(stack_t* st_bracket) {
	elem_t ValBranch = pop(st_bracket);
	if (ValBranch == NBranch0) {
		printf(")");
		if (st_bracket->size) {
			push(st_bracket,pop(st_bracket) - 1 );
			print_bracket(st_bracket);
		} else 
			printf("\n");
	} else if (ValBranch == QBracket || ValBranch == QBracket - 1) {
		printf(" []");
		if (st_bracket->size) {
			push(st_bracket,pop(st_bracket) - 1 );
			print_bracket(st_bracket);
		} else 
			printf("\n");
	} else
		push(st_bracket, ValBranch);
}





