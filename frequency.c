#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_LETTERS 26
typedef enum {FALSE = 0, TRUE = 1} boolean;

typedef struct node
{
	char letter;
	long unsigned int count;
	boolean end_of_word;
	char* word;
	struct node* children[NUM_LETTERS];
} node;

//a function that gets a letter, creats and returns a node with a dynamic memory
//if the allocation of the memory didn't succeed returns NULL
node* create_node(char c)
{
	node* new_node = (node*)calloc(1,sizeof(node));
	if(new_node == NULL)
		return NULL;
	
	new_node -> end_of_word = FALSE;
	new_node -> count = 0;
	new_node -> letter = c;
	new_node -> word = NULL;
	for(int i = 0; i < NUM_LETTERS; i++)
	{
		new_node -> children[i] = NULL;
	}
	return new_node;
}

//a function that gets a node pointer and a letter ,it adds a child in the right place with the input letter
//if there is a child with the specific letter the function returns it  
node* insert(node* root, char c)
{
	node* temp;
	if(root -> children[c - 'a'] == NULL)
	{
		temp = create_node(c);
		if(temp == NULL)
			return NULL;
		root -> children[c - 'a'] = temp;
		if(root -> word ==NULL)
		{
			temp -> word = (char*)calloc(2,sizeof(char));
			if(temp -> word == NULL)
				return NULL;
			temp -> word[0] = c;
			temp -> word[1] = '\0';
		}
		else
		{
			int len = strlen(root -> word);
			temp -> word = (char*)calloc(len+2,sizeof(char));
			if(temp -> word == NULL)
				return NULL;
			int i;
			for(i = 0; i < len; i++)
			{
				temp -> word[i] = root -> word[i];
			}
			temp -> word[i++] = c;
			temp -> word[i] = '\0';
		}
	}
	else
		temp = root -> children[c - 'a'];
	return temp;
}

//check if a char is a letter or not
int is_a_letter(char c)
{
	if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return TRUE;
	else
		return FALSE;
}


//this fucntion builts a tree from the standart input, every node has its uniqe letter and every path represents a word
//not all nodes represent a word, but only the nodes that are an end of one.
node* trei(node* root)
{
	char c = getchar();
	node* temp_root = root;
	while(c != -1)
	{	
		while(c != '\n' && c != '\t' && c != '\r' && c != '\0' && c != ' ' && c != -1)
		{
			if(is_a_letter(c))
			{
				if(c >= 'A' && c <= 'Z')
					c = c + ('a' - 'A');
				temp_root = insert(temp_root, c);			
			}
			c = getchar();
		}
		if(temp_root -> end_of_word == FALSE)
		{
			temp_root -> end_of_word = TRUE;
			temp_root -> count++;
		}
		else
			temp_root -> count++;
		while(c == '\n' || c == '\t' || c == '\r' || c == '\0' || c == ' ')
			c = getchar();
		temp_root = root;
	}
	return root;
}

//printing the trei in a lexicographic
void up_order_lexicographic_print(node* root)
{
	if(root -> end_of_word == TRUE)
		printf("%s %ld\n", root -> word, root ->count);
	for(int i = 0; i < NUM_LETTERS; i++)
	{
		if(root -> children[i] != NULL)
		{
			up_order_lexicographic_print(root -> children[i]);
		}
	}
}

//reverse lexicographic printing the trei 
void down_order_lexicographic_print(node* root)
{
	if(root -> end_of_word == TRUE)
		printf("%s %ld\n", root -> word, root -> count);
	for(int i = NUM_LETTERS - 1; i >= 0; i--)
	{
		if(root -> children[i] != NULL)
			down_order_lexicographic_print(root -> children[i]);
	}
}

//this fucntion frees the dynamic memory alocated in this project at the end of the main
void free_memory(node* root)
{
	for(int i = 0; i < NUM_LETTERS; i++)
	{
		if(root -> children[i] != NULL)
			free_memory(root -> children[i]);
	}	
	free(root -> word);
	free(root);
}


//in this main function we are bulding a trei of nodes and prints the words in it
//if reversed wanted enter the input r, other wise for default
int main(int argc, char* argv[])
{
	node* trei_root = create_node(0);
	if(trei_root == NULL)
		return 0;
		
	trei_root = trei(trei_root);	
	
	if(argc > 1 && *argv[1] == 'r')
			down_order_lexicographic_print(trei_root);
	else
	{
		if(argc == 1)
			up_order_lexicographic_print(trei_root);
	}
	free_memory(trei_root);
	
	return 0;
}

