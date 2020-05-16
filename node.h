#define NBranch2 2
#define NBranch1 1
#define NBranch0 0

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
bool Print_node(Node* n);
void print_bracket(stack_t* st_bracket);

bool Flag_bracket;
stack_t st_bracket;



