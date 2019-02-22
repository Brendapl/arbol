#include <stdio.h>
#include <time.h>
#include <stdlib.h>
typedef enum{FALSE, TRUE} Bool;

/*Node struct with its members.*/
struct node
{
	int val;
	int balance;
	struct node *left_child;
	struct node *right_child;
};

/*Function which searches in a binary tree for a value (data), given a root Node.*/
struct node* search(struct node *root, int data){
	Bool found = FALSE;
	struct node *currNode = root;

	/*
	while(!found && currNode != NULL){
		if(data < currNode -> val){
			currNode = currNode -> left_child;
		}
		else if(data > currNode -> val){
			currNode = currNode -> right_child;
		}
		else if(data == currNode -> val){
			found = TRUE;
		}
		else{
			currNode = NULL;
		}
	}*/


	if(currNode != NULL){
		if(currNode -> val < data){
			currNode = search(currNode -> left_child, data);
		}
		else if(currNode -> val > data){
			currNode = search(currNode -> right_child, data);
		}
		else if(currNode -> val != data){
			currNode = NULL;
		}
	}

	/*
	while(currNode != NULL && !found){
		if(currNode -> val != data){
			if(data < currNode -> val && currNode -> left_child != NULL){
				currNode = search(currNode -> left_child, data);
			}
			else if(data > currNode -> val && currNode -> right_child != NULL){
				currNode = search(currNode -> right_child, data);
			}
		} else {
			found = TRUE;
			break;
		}
	}
	*/
	return(currNode);
}



struct node* create(int quantity){
	struct node *insert (int data, struct node *ptr, int *ht_inc);
	int rand_max = 1000;
	int ht_inc;
	int data = rand() % rand_max;
	//struct node *newRoot;
	//newRoot = NULL
	struct node *root = (struct node *) malloc(sizeof(struct node));
	//root = NULL;
	root -> val = data;
	root -> left_child = NULL;
	root -> right_child = NULL;
	root -> balance = 0;
	//newRoot = root;
	for(int i = 1; i < quantity; i++){
		data = rand() % rand_max;
		while(search(root, data) != NULL){
			data = rand() % rand_max;
		}
		root = insert(data, root, &ht_inc);
	}
	return root;
}

Bool searchFound(struct node *root, int data){
    struct node *someNode = (struct node *) malloc(sizeof(struct node));
    /*Time*/
    clock_t start = clock();
    someNode = search(root, data);
    clock_t stop = clock();
    /*Time*/
    Bool result;
		if(someNode != NULL){
    	if(someNode->val == data){
        	result = TRUE;
        	double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;
        	printf("Time elapsed in ms: %f \n", elapsed);
        	FILE* fichero;
        	fichero = fopen("data.txt", "a");
        	fprintf (fichero, "%lf%s%d \n", elapsed, " ",data);
        	fclose(fichero);
    	}
	}
	else{
        result = FALSE;
    }
    return result;
}

/*Function which inserts in a binary tree and Balance.*/
struct node *insert (int data, struct node *ptr, int *ht_inc)
{
    struct node *aptr;
    struct node *bptr;
    if(ptr==NULL)
    {
        ptr = (struct node *) malloc(sizeof(struct node));
        ptr -> val = data;
        ptr -> left_child = NULL;
        ptr -> right_child = NULL;
        ptr -> balance = 0;
        *ht_inc = TRUE; return (ptr);
    }
    if(data < ptr -> val)
    {
        {
            ptr -> left_child = insert(data, ptr -> left_child, ht_inc);
            if(*ht_inc==TRUE)
                switch(ptr -> balance) {
                    case -1: /* Right heavy */
                        ptr -> balance = 0;
                        *ht_inc = FALSE;
                        break;
                    case 0: /* Balanced */
                        ptr -> balance = 1;
                        break;
                    case 1: /* Left heavy */
                        aptr = ptr -> left_child;
                        if(aptr -> balance == 1) {
                            printf("Left to Left Rotation\n");
                            ptr -> left_child= aptr -> right_child;
                            aptr -> right_child = ptr;
                            ptr -> balance = 0;
                            aptr -> balance=0;
                            ptr = aptr;
                        }
                        else {
                            printf("Left to Right Rotation\n");
                            bptr = aptr -> right_child;
                            aptr -> right_child = bptr -> left_child;
                            bptr -> left_child = aptr;
                            ptr -> left_child = bptr -> right_child;
                            bptr -> right_child = ptr;
                            if(bptr -> balance == 1 )
                                ptr -> balance = -1;
                            else
                                ptr -> balance = 0;
                            if(bptr -> balance == -1)
                                aptr -> balance = 1;
                            else
                                aptr -> balance = 0;
                            bptr -> balance=0;
                            ptr = bptr;

                        }
                        *ht_inc = FALSE;
                }
        }
    }
    if(data > ptr -> val){
        ptr -> right_child = insert(data, ptr -> right_child, ht_inc);
        if(*ht_inc==TRUE){
            switch(ptr -> balance){
                case 1: /* Left heavy */
                    ptr -> balance = 0;
                    *ht_inc = FALSE;
                    break;
                case 0: /* Balanced */
                    ptr -> balance = -1;
                    break;
                case -1: /* Right heavy */
                    aptr = ptr -> right_child;
                    if(aptr -> balance == -1) {
                        printf("Right to Right Rotation\n");
                        ptr -> right_child= aptr -> left_child;
                        aptr -> left_child = ptr;
                        ptr -> balance = 0;
                        aptr -> balance=0;
                        ptr = aptr;
                    }
                    else{
                        printf("Right to Left Rotation\n");
                        bptr = aptr -> left_child;
                        aptr -> left_child = bptr -> right_child;
                        bptr -> right_child = aptr;
                        ptr -> right_child = bptr -> left_child;
                        bptr -> left_child = ptr;
                        if(bptr -> balance == -1)
                            ptr -> balance = 1;
                        else
                                ptr -> balance = 0;
                        if(bptr -> balance == 1)
                                    aptr -> balance = -1;
                                else
                                    aptr -> balance = 0;
                        bptr -> balance=0;
                        ptr = bptr;
                    }/*End of else*/
                    *ht_inc = FALSE;
            }
        }
    }
    return(ptr);
}
void display(struct node *ptr, int level){
    int i;
    if ( ptr!=NULL ){
        display(ptr -> right_child, level+1);
        printf("\n");
        for (i = 0; i < level; i++)
            printf(" ");
        printf("%d", ptr -> val);
        display(ptr -> left_child, level+1);
    }
}
void inorder(struct node *ptr){
    if(ptr!=NULL){
        inorder(ptr -> left_child);
        printf("%d ",ptr -> val);
        inorder(ptr -> right_child);
    }
}

int main(void){

    int ht_inc;
    int data ;
    int option;
		int quantity;
    struct node *root = (struct node *)malloc(sizeof(struct node));
    root = NULL;
    while(1){
        printf("1.Insert\n");
        printf("2.Display\n");
        printf("3.Search\n");
				printf("4.Insert Many\n");
        printf("5.Quit\n");
        printf("Enter your option : ");
        scanf("%d",&option);
        switch(option){
            case 1:
                printf("Enter the value to be inserted : ");
                scanf("%d", &data);
                if( search(root,data) == NULL )
                    root = insert(data, root, &ht_inc);
                else
                    printf("Duplicate value ignored\n");
                break;
            case 2:
                if(root==NULL)
                {
                    printf("Tree is empty\n");
                    continue;
                }
                printf("Tree is :\n");
                display(root, 1);
                printf("\n\n");
                printf("Inorder Traversal is: ");
                inorder(root);
                printf("\n");
                break;
            case 3:
                printf("Enter the value to be search : ");
                scanf("%d", &data);
                printf("%d",searchFound(root, data));
                printf("\n");
                break;
						case 4:
								printf("Enter the quantity to be inserted : ");
								scanf("%d", &quantity);
								root = create(quantity);
								break;
            case 5:
                exit(1);
            default:
                printf("Wrong option\n");


        }

    }


}
