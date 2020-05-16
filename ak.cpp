#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
//#include "tree.h"
#include "st.h"

#define NBranch2 2
#define NBranch1 1
#define NBranch0 0
#define QBracket 5
#define LEFT 11
#define RIGHT 22
#define LIBERTY 33

void test();
typedef int data_t;


struct Node {
	data_t data;
	struct Node* left;
	struct Node* right;
};
typedef struct Node Node;


stack_t st_bracket;//
bool Flag_bracket;
//stack_t st_bracket;
data_t x_node = 0;
FILE* file = NULL;

void delete_node(Node* n);
Node* add_node(Node* n, data_t data, int side);
void visit(Node* n, bool(*func)(Node* n));
bool Print_node(Node* n);
void print_bracket(/*stack_t* st_bracket*/);
bool  Find_node(Node* n);
int def_side(data_t data);
void init_file(const char* file_name);
void close_file();
void init_stack();
Node* create_node(Node* n, data_t data);



int main(int atgc, char* argv[])
{
	if ((file = fopen("tree", "w")) == NULL) {
		printf("cannot open file.\n");
		exit(1);
	}
	//init_file("tree");
	test();
	//init_stack();

	//close_file();
	fclose(file);
	stack_destruct(&st_bracket);
	return 0;
}

void test() {
	//x_node = 100;
	data_t data = 1;
	stack_init(&st_bracket);
	Node* n = add_node(NULL, data, LIBERTY);
	n->left = add_node(n->left, 2, LIBERTY);
	n->right = add_node(n->right, 3, LIBERTY);
	n->left->left = add_node(n->left->left, 4, LIBERTY);
	n->left->right = add_node(n->left->right, 5, LIBERTY);
	n->left->left->right = add_node(n->left->left->right, 6, LIBERTY);
	n->left->left->right->left = add_node(n->left->left->right->left, 8, LIBERTY);
	n->left->left->right->right = add_node(n->left->left->right->right, 9, LIBERTY);
	n->right->left = add_node(n->right->left, 7, LIBERTY);
	n->right->left->right = add_node(n->right->left->right, 11, LIBERTY);

	visit(n, Print_node);

	delete_node(n);
}

bool  Find_node(Node* n) {
	if (x_node == n->data) {
		printf("find\n");
		return 0;
	}
	return 1;
}

void visit(Node* n, bool(*func)(Node* n)) {
	if (n) {
		printf("blyaaaa\n");
		assert((*func)(n));
		visit(n->left, func);
		visit(n->right, func);
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

Node* add_node(Node* n, data_t data, int side) {//сделать отдельную ф криеэтнод и вместо рекурсии
	if (n == NULL) {
		n = create_node(n, data);
	} else	if ((n->right == NULL && side == RIGHT) || (n->right == NULL && side == LIBERTY))
			n->right = create_node(n->right, data);
		else if ((n->left == NULL && side == LEFT) || (n->left == NULL && side == LIBERTY))
			n->left = create_node(n->left, data);
		else
			printf("error in add_node");

	return n;
}

Node* create_node(Node* n, data_t data) {
	//printf("sukya ");
	n = (Node*) calloc(1, sizeof(Node));
	n->data = data;
	n->left = NULL;
	n->right = NULL;
	return n;
}

bool Print_node(Node* n) {
	assert(n);
	printf("blyaaaaaaaaaaaaaaaaa\n");
		fprintf(file, " (%d", n->data);
		if (n->left == NULL && n->right == NULL) {
			push(&st_bracket, NBranch0);
		}
		else if (n->left == NULL && n->right != NULL) {
			fprintf(file, " []");
			push(&st_bracket, NBranch1);
			
		}
		else if (n->left != NULL && n->right == NULL) {
			push(&st_bracket, NBranch1);
			Flag_bracket = 1;
		} else
			push(&st_bracket, NBranch2);

	stack_dump(&st_bracket);

	print_bracket();
	if (Flag_bracket) {
		Flag_bracket = 0;
		push(&st_bracket, QBracket);
	}
	stack_dump(&st_bracket);

	return 1;
}

void print_bracket() {
	printf("printorebana ");
	elem_t ValBranch = pop(&st_bracket);
	if (ValBranch == NBranch0) {
		fprintf(file, ")");
		if (st_bracket.size) {
			push(&st_bracket,pop(&st_bracket) - 1 );
			print_bracket();
		} else 
			fprintf(file, "\n");
	} else if (ValBranch == QBracket || ValBranch == QBracket - 1) {
		fprintf(file, " []");
		if (st_bracket.size) {
			push(&st_bracket,pop(&st_bracket) - 1 );
			print_bracket();
		} else 
			fprintf(file, "\n");
	} else
		push(&st_bracket, ValBranch);
}