#include "bst.h"

//The function prints the BST like a tree
void Display( Node *node, int level )
{
    //Setting up an iterator
    int i;

    //Checking if the node is NULL
    if ( node != 0 ) {
        //If not, go right and print next level
        Display( node->right, level + 1 );

        //Print as many spaces as the level (the node has no spaces)
        for ( i = 0; i <= level; i++ ) {
            printf( "      " );
        }

        //Print the values of the nodes
        printf( "%d\n", node->data );

        //Go left and print the next level
        Display( node->left, level + 1 );
    }
}

//The function prints all the values in the BST likewise: node, left, right
void preorder( Node *node )
{
    //Check if the node is NULL
    if ( node != NULL ) {

        //If not, print its value
        printf( "\n%d", node->data );

        //Recur left
        preorder( node->left );
        //Recur right
        preorder( node->right );
    }
}

//The function prints all the values in the BST likewise: left, node, right
void inorder( Node *node )
{
    ////Check if the node is NULL
    if ( node != NULL ) {
        //If not recur left
        inorder( node->left );
        //Print its value
        printf( "\n%d", node->data );
        //Recur right
        inorder( node->right );
    }
}

//The function prints all the values in the BST likewise: right, left, node
void postorder( Node *node )
{
    //Check if the node is NULL
    if ( node != NULL ) {
        //Recur left
        postorder( node->left );
        //Recur right
        postorder( node->right );
        //Print its data
        printf( "\n%d", node->data );
    }
}

//The function is used later to determine the successor value of a node
Node *FindMin( Node *node )
{
    //Go to the last value of the left sub-tree
    while ( node->left != NULL ) {
        node = node->left;
    }

    //Return the last found node
    return node;
}

//This function is used to delete a node from the BST
Node *Delete( Node *node, int data )
{
    //Find the position of the node to be deleted
    //Check if the node is NULL
    if ( node == NULL ) {
        //If true return it
        return node;
    } else if ( data < node->data ) {
        //Else recur left (the value is smaller than the current node's)
        node->left = Delete( node->left, data );
    }

    else if ( data > node->data ) {
        //Else recur right (the value is greater than the current node's)
        node->right = Delete( node->right, data );
    }

    else {
        //If both children are NULL, the node is a leaf. Deallocate its memory and set it to NULL
        if ( node->left == NULL && node->right == NULL ) {
            //Deallocating memory
            free( node );
            //Setting it to NULL
            node = NULL;
            //If the node has a child on the right (no child on the left).
        } else if ( node->left == NULL ) {
            //Create a temporary node and initialize it to the current working node
            Node *temp = node;
            //Set it to point to its right child
            node = node->right;
            //Deallocate memory
            free( temp );
            //If the node has a child on the left (no child on the right)
        } else if ( node->right == NULL ) {
            //Create a temporary node and initialize it to the current working node
            Node *temp = node;
            //Set it to point to its left child
            node = node->left;
            //Deallocate memory
            free( temp );
        }
        //If it has two children (both right and left are non-NULL)
        else {
            //Create a temporary node and initialize it to the successor of the node. (the smallest value from the right sub-tree)
            Node *temp = FindMin( node->right );
            //Node's data is replaced by the successor's data
            node->data = temp->data;
            //Delete the successor node from the BST.
            node->right = Delete( node->right, temp->data );
        }
    }

    //Return the node
    return node;
}

//Insert a new value in the BST
Node *Add_Node( Node *node, int data )
{
    //Check if the current node is a NULL
    if ( node == NULL ) {
        //If yes, then allocate memory to the size of a node
        node = ( Node * )malloc( sizeof( Node ) );
        //Set its data to whatever value you want to insert
        node->data = data;
        //Set both of its children to NULL (every node is inserted as a LEAF!)
        node->left = node->right = NULL;
        //Else recur left (the value we want to insert is smaller than the current node's)
    } else if ( data <= node->data ) {
        //Recur left
        node->left = Add_Node( node->left, data );
        //Else recur right (the value we want to insert is greater than the current node's)
    } else {
        //Recur right
        node->right = Add_Node( node->right, data );
    }

    //Return the node
    return node;
}

//The function determines the smallest value in the BST
int getMin( Node *node )
{
    //Create a temporary node and initialize it to root. (that's how me make the function call)
    Node *node_iterator = node;

    //Go the last left node
    while ( node_iterator->left != NULL ) {
        node_iterator = node_iterator->left;
    }

    //Return the smallest value
    return ( node_iterator->data );
}

//The function determines the greatest value in the BST
int getMax( Node *node )
{
    //Create a temporary node and initialize it to root. (that's how me make the function call)
    Node *node_iterator = node;

    //Go to the last right node
    while ( node_iterator->right != NULL ) {
        node_iterator = node_iterator->right;
    }

    //Return the greatest value
    return ( node_iterator->data );
}

//A function which returns a random value
int randomNumberGenerator()
{
    //Using the built-in rand function
    return rand() % G_values_limit;
}

//The function determines if all the BST's values are bounded by 2 values
bool checkValues( Node *node, int minimum, int maximum )
{
    //Get the global minimum and maximum of the BST
    int global_minimum = getMin( node );
    int global_maximum = getMax( node );

    //Check if the BST minimum and maximum are bounded by the 2 values
    if ( global_minimum >= minimum && global_maximum <= maximum ) {
        //If true, proceed to check all the node's values are bounded by those 2 values
        //Check if the current node's data is bounded and recur left and right
        if ( node->data < global_maximum && node->data > global_minimum ) {
            //Check the left child's data
            return checkValues( node->left, minimum, maximum );
            //Check the right child's data
            return checkValues( node->right, minimum, maximum );
        }
        //Return true if all the values are bounded
        return true;
    } else {
        //Return false otherwise
        return false;
    }
}

//The function will delete the entire BST
//The call will be made upon the root's address
void deleteBST(Node **node)
{
    //Checking if the current node is NULL
    if(*node == NULL){
        //If true exit
        return;
    }

    //Else delete the node's children
    deleteBST(&(*node)->left);
    deleteBST(&(*node)->right);

    //Check if both children are different from NULL
    if(!(*node)->left && !(*node)->right){
        //Delete the parent
        delete *node;
        //Set the parent to NULL
        *node = NULL;
    }


}


//A function which checks if the BST is empty.
//It will return true if the BST is empty
//The call will be made upon the root
bool isEmpty( Node *node )
{
    //Checking if the node (root) is empty
    if ( node == NULL ) {
        //IF true return true
         printf( "\nEmpty tree!\n" );
        return true;
    }
    //If not return false
    return false;
}


//A function used to test the program "numberOfTests" times
void makeTests(Node *node, int numberOfTests)
{
    //Setting up some local variables
    int bound = 0;
    int global_minimum = 0;
    int global_maximum = 0;
    int minimum = 0;
    int maximum = 0;
    bool status = false;

    //Iterating "numberOfTests" times
    for(int iterator1 = 0; iterator1 <numberOfTests ; iterator1++){
        //Setting the bound for inserting a random number of values
        bound = rand()%(G_values_limit+iterator1);

        //Inserting "bound" number of values
        for (int iterator2 = 0; iterator2 < bound ; iterator2++){
            node = Add_Node(node,randomNumberGenerator());
        }

	
        //Setting up the BST's minimum and maximum;
        global_minimum = getMin(node);
        global_maximum = getMax(node);

        //Setting up the boundedness values
        minimum = rand()%(numberOfTests/100);
        maximum = rand()%((numberOfTests*5));

        //Printing them
        printf("\nBST's minimum and maximum are: %d %d ",global_minimum,global_maximum);
        printf("\nBoundedness values set to %d %d",minimum, maximum);

        //Setting up the status
        status = checkValues(node,minimum,maximum);

        //Printing the result
        if(status==true){
            printf("\nResult -> PASSED! <-------------------------------------------------------------\n");
        }else{
            printf("\nResult -> FAILED\n");
        }

        deleteBST(&node);

    }
}


//A function used to check if a value already exists in the BST
bool search(Node *node, int target)
{
	//Checking if the BST is empty
	if (node == NULL) {
		//If so return false
		return false;
	//Else see if we can find the value 
	} else {
		//If the current node stores the value, return true
		if (node->data == target) {
			return true;
		//Else recur on the right subtree
		} else {
			//IF the value is smaller than the node's, recur to the left
			if (target < node->data) {
				return search(node->left, target);

			//Else recur to the right
			} else {
				return search(node->right, target);
			}
		}
	}
	//If the above code executed, it means the value does not exists i the BST, return false
	return false;
}


//A function which will write parameter and values to a file
void buildFile( FILE *f, int nuberOfItems)
{
	//Checking if the file opened correctly
	if(f == NULL){
		printf("\nError opening file! \n");
	}else{
		//Flag variable used to check if the file has been already built
		int flag = 0;
		//Scan the first line
		fscanf(f, "B %d", &flag);

		//IF true, the file has been alrady built
		if(flag){
			printf("\nError! File already built! Skipping to testing.... \n");
		}else{
			//Else start writing values to file ( I stand for input, later used to insert the values)
			fprintf(f, "B %d\n", 1);
			int iterator;

			for (iterator = 0; iterator<nuberOfItems; iterator++) {
				fprintf(f, "I %d\n", randomNumberGenerator());
			}

			for(iterator=0;iterator<nuberOfItems/6;iterator++){
				fprintf(f,"D %d\n",randomNumberGenerator());
			}

			for (iterator = 0; iterator<nuberOfItems; iterator++) {
				fprintf(f, "V %d %d\n", randomNumberGenerator(), randomNumberGenerator());
			}

			for (iterator = 0; iterator<nuberOfItems / 4; iterator++) {
				fprintf(f, "S %d\n", randomNumberGenerator());
			}

			//M-min and max
			fprintf(f, "M\n", randomNumberGenerator());
			//P-preorder
			fprintf(f, "P\n", randomNumberGenerator());
			//i-inorder
			fprintf(f, "i\n", randomNumberGenerator());
			//p-postorder
			fprintf(f, "Post\n", randomNumberGenerator());
			//d-display
			fprintf(f, "d\n", randomNumberGenerator());
			//B-delete BST
			fprintf(f, "B\n", randomNumberGenerator());
			//E- is empty?
			fprintf(f, "E\n", randomNumberGenerator());

		}	
	}
}

void readFile(FILE *fp, Node *node)
{
	//Define the key to be inserted
	int key;

	int g_minimum, g_maximum;
	int minimum, maximum;
	//Define the task selection
	char option;
	//Open the input file
	printf("\nAttempting to open file...\n");

	//Check if the file was successfully opened
	if (!fp) {
		//If not, warn the user and exit the program
		perror("Unable to open file");
		exit(0);
		//Else start the tasks
	}
	else {
		printf("Success!\n");
		//Continue reading while there is something to read
		while (!feof(fp)) {

			//Red each line and check the task selection
			fscanf(fp, "%c", &option);

			// "I" is for inserting
			if (option == 'I') {
				//Read the value
				fscanf(fp, "%d", &key);

				//Checking if the values already exists in the BST
				if (!search(node, key)) {
					//Insert it in the BSt
					node = Add_Node(node, key);
				}
				else {
					printf("%d already exists in the tree! \n", key);
				}

				//"D" is for deleting
			}
			else if (option == 'D') {
				//Read the value
				fscanf(fp, "%d", &key);

				//Checking if the value exists in the BST, if so we can delete it
				if (search(node, key)) {
					//Delete it
					node = Delete(node, key);
				}
				else {
					printf("%d does not exist in the BST! \n", key);
				}


				//"M" is for maximum and minimum
			}
			else if (option == 'M') {

				//Retrieve the minimum and maximum, then print them
				g_maximum = getMax(node);
				g_minimum = getMin(node);
				printf("\n The GLOBAL minimum and maximum are :%d %d", g_minimum, g_maximum);

				//"V" checks boundedness
			}
			else if (option == 'V') {
				//Check if the BST is empty
				if (!isEmpty(node)) {
					//Retrieve the BSTS's minimum and maximum
					g_minimum = getMin(node);
					g_maximum = getMax(node);
					printf("\nMinimum and maximum of the current BST are: %d %d", g_minimum, g_maximum);

					//Read the boundedness values from file
					fscanf(fp, "%d %d ", &minimum, &maximum);

					printf("\nBoundedness values set to : %d %d", minimum, maximum);

					//Check if all the values are bounded
					bool status = checkValues(node, minimum, maximum);

					printf("\nBoundedness result : ");
					//IF the function returns true, then all the values are bounded, false otherwise
					if (true == status) {
						printf("PASSED!\n");
					}
					else {
						printf("FAILED!\n");
					}
				}
			}
			else if (option == 'P') {
				//Checking if the BST is empty
				if (isEmpty(node)) {
					//If true, exit from the procedure
				}
				else {
					//Else print it
					preorder(node);
					printf("\n");
				}
			}
			else if (option == 'p') {
				//Checking if the BST is empty
				if (isEmpty(node)) {
					//If true, exit from the procedure

				}
				else {
					//Else print it
					postorder(node);
					printf("\n");
				}
			}
			else if (option == 'i') {
				//Checking if the BST is empty
				if (isEmpty(node)) {
					//If true, exit from the procedure
				}
				else {
					inorder(node);
					printf("\n");
				}
			}
			else if (option == 'd') {
				if (isEmpty(node)) {
					//If true, exit from the procedure
				}
				else {
					//Else print it
					Display(node, 0);
				}
			}
			else if (option == 'B') {
				//Check if the BSt is empty
				if (isEmpty(node)) {
					//IF true, exit
				}
				else {
					//Else delete it
					deleteBST(&node);
					printf("\nFinished deleting the BST! \n");
				}
			}
			else if (option == 'E') {
				if (isEmpty(node)) {
				}
				else {
					printf("The BST is not empty! \n");
				}
			}
		}
	}
}
