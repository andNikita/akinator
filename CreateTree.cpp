#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "st.h"
#include "tree.h"
#include "libstr.h"


//void create_tree(Node* n, int counter);

int main(int atgc, char* argv[])
{
	init_file("treebasic", "r");

	init_stack();
	Node* n;
	test(n);
	delete_node(n);
	destruct_stack();
	
	return 0;
}


// (1 (2 (4 [] (6 (8) (9))) (5)) (3 (7 [] (11)) []))