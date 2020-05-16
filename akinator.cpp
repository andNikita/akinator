#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "tree.h"

#define SIZE_ANS 5
#define ASK 11
#define NEWF 22
#define LASTF 33

int open_file_for_ak(int mode);
void program(Node* n, int mode);
Node* akinator(Node* n);
Node* ret_n_depend_ans(Node* n, int* intAns, char* answer);
Node* create_akinator(Node* n);

int main(int atgc, char* argv[])
{
	int mode = open_file_for_ak(ASK);
	Node* n = (Node*) calloc(1, sizeof(Node));
	init_stack();
	program(n, mode);
	delete_node(n);
	destruct_stack();
	close_file();
	return 0;
}

Node* create_akinator(Node* n) {
	printf("create(enter ask and 2 answer): ");
	n = add_node(n, NULL, SELF);
	//printf("%s", n->data);
	n->left = add_node(n->left, NULL, SELF);
	//printf("%s", n->left->data);
	n->right = add_node(n->right, NULL, SELF);
	printf("end create\n");
	return n;
}

Node* ret_n_depend_ans(Node* n, int* intAns, char* answer) {
	assert(n);
	Node* last_node = n;
	if (!strcmp(answer, "yes")) {
		*intAns = 1;
		n =  n->left;
	} else if (!strcmp(answer, "no")) {
		*intAns = 0;
		n =  n->right;
	} else {
		printf("ответьте, блин, нормально\t");
		*intAns = -1;
	}
	if (*intAns == 0 && is_list(last_node)){
		printf("тогда меняем...\n");
		return last_node;
	}
	return n;
}

int open_file_for_ak(int mode) {
	char answer[SIZE_COMMAND];
	if (mode == ASK) {
		printf("create a new file or use the old one? <new\\old>:\t");
		get_string(answer, SIZE_COMMAND);
		if (!strcmp(answer, "new")) {
			init_file("ak", "w+");
			return LASTF;
		}
		else if (!strcmp(answer, "old")) {
			init_file("ak", "r+");
			return LASTF;
		}
	}
	else if (mode == NEWF) {
		close_file();
		init_file("ak", "w+");
		return NEWF;
	}
}

void program(Node* n, int mode) {
	
	char command[SIZE_COMMAND];
	printf("command:\n"
		"\tplay\n\tcreate\n"
		"\tusefile\n"
		"\texit\n"
		"\twrite (in file \"ak\")\n");
	printf("enter command: ");
	get_string(command, SIZE_COMMAND);
	while (strcmp(command, "exit") != 0) {
		if (!strcmp(command, "play"))
			n = akinator(n);
		if (!strcmp(command, "create")){
			n = create_akinator(n);
			assert(n);
		}
		if (!strcmp(command, "write")) {
			if (mode == LASTF)
				open_file_for_ak(NEWF);
			else
				open_file_for_ak(ASK);
			visit(n, Print_node);
			printf("writed\n");
		}
		if (!strcmp(command, "usefile")) {
			n = create_func(n);
			printf("used\n");
		}

		printf("enter command: ");
		get_string(command, SIZE_COMMAND);
	}
	printf("good bay\n");
}

Node* akinator(Node* n) {
	char answer[SIZE_ANS];//cnt
	int intAns = -1;
	Node* n_start = n;
	Node* n_last = n;
	int last_ans = 0;
	while(1) {
		if(n->left == NULL && n->right == NULL) {
			printf("is it you answer: %s?\t <yes\\no>\t", n->data);
			
			get_string(answer, SIZE_ANS);
			n = ret_n_depend_ans(n, &intAns, answer);
			if (intAns == -1)
				continue;
			if (intAns) {
				printf("eee boy\n");
				break;
			} else {
				n = add_change(n);
				if (last_ans)
					n_last->left = n;
				else 
					n_last->right = n;
			}
		} else {
			printf("%s? <yes\\no>:\t", n->data);
			get_string(answer, SIZE_ANS);
			printf("your answer is %s;\n", answer);
			n_last = n;
			n = ret_n_depend_ans(n, &intAns, answer);
			last_ans = intAns;
		}
	}
	return n_start;
}


