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



node* create_node(char c)
{
	node* new_node = (node*)malloc(sizeof(node));
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

int is_a_letter(char c)
{
	if(c >= 'a' || c <= 'z')
		return TRUE;
	else
		return FALSE;
}

node* insert(node* root, char c)
{
	node* temp = create_node(c);
	if(root -> children[c - 'a'] == NULL)
	{
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
	return temp;
}

boolean if_a_letter(char c)
{
	if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return TRUE;
	else
		return FALSE;
}

void trei(node* root)
{
	char c = getchar();
	node* temp_root = root;
	while(c != EOF)
	{
		while(c != '\n' && c != '\t' && c != '\r' && c != '\0' && c !=' ' && c != EOF)
		{
			if(if_a_letter(c) == TRUE)
			{
				if(c >= 'A' && c <= 'Z')
					c = c - 'a' - 'A';
				temp_root = insert(temp_root, c);			
			}
			c = getchar();
		}
		temp_root -> end_of_word = TRUE;
		temp_root -> count++;
		while(c == '\n' && c == '\t' && c == '\r' && c == '\0' && c == ' ' && c == EOF)
			c = getchar();
		temp_root = root;
	}
}

void up_order_lexicographic_print(node* root)
{
	if(root -> end_of_word)
			printf("%s %ld", root -> word, root ->count);
	for(int i = 0; i < NUM_LETTERS; i++)
	{
		if(root -> children[i] != NULL)
			up_order_lexicographic_print(root -> children[i]);
	}
}

void down_order_lexicographic_print(node* root)
{
	if(root -> end_of_word)
			printf("%s %ld", root -> word, root -> count);
	for(int i = NUM_LETTERS; i > 0; i--)
	{
		if(root -> children[i] != NULL)
			down_order_lexicographic_print(root -> children[i]);
	}
}

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

int main(int argc, char* argv[])
{
	node* trei_root = create_node(0);
	if(trei_root == NULL)
		return 0;
	trei(trei_root);
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

