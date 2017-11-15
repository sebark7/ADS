#include "bst.h"

//Set the root of the BST to NULL (Empty tree)
Node *root = NULL;


int main()

{
    //Define iterators and such
    int choice, new_value, del_value, minimum, maximum, g_minimum, g_maximum;

    //Keep the program open and select its tasks
    do {
        //Print a menu and select a task
        printf( "\n1.Insert value:" );
        printf( "\n2.Delete value:" );
        printf( "\n3.Preorder:" );
        printf( "\n4.Inorder:" );
        printf( "\n5.Postorder:" );
        printf( "\n6.Print BST:" );
        printf( "\n7.Minimum and Maximum:" );
        printf( "\n8.Random insertion of n values:" );
        printf( "\n9.Check boundedness:" );
        printf( "\n10.Read tasks from file:" );
        printf( "\n11.Delete the entire BST:" );
        printf( "\n12. Make tests:" );
        printf( "\n13.Exit:" );
        printf( "\nYour choice: " );
        scanf( "%d", &choice );

        //The switch statement determines which task will be fulfilled
        switch ( choice ) {
            //Add a node
            case 1: {
                    printf( "\nNew value:" );
                    //Read the node's value
                    scanf( "%d", &new_value );
                    //Insert the new value into the BST
                    root = Add_Node( root, new_value );
                    //Finish the task
                    break;
                }//end case 1


            //Delete a node
            case 2: {
                    //Checking if the BST is empty
                    if ( isEmpty( root ) ) {
                        break;
                    } else {
                        //Else begin the deletion procedure
                        printf( "\nValue to be deleted:" );
                        //Read the value
                        scanf( "%d", &del_value );
                        //Delete the node
                        root = Delete( root, del_value );
                        //Finish the task
                        break;
                    }
                }//end case 2


            //Pre-order printing
            case 3: {
                    //Checking if the BST is empty
                    if ( isEmpty( root ) ) {
                        //If true, exit from the procedure
                        break;
                    } else {
                        //Else print it
                        preorder( root );
                        break;
                    }
                }//end case 3


            //In-order printing
            case 4: {
                    //Checking if the BST is empty
                    if ( isEmpty( root ) ) {
                        //If true, exit from the procedure
                        break;
                    } else {
                        inorder( root );
                        break;
                    }
                }//end case 4


            //Post-order printing
            case 5: {
                    //Checking if the BST is empty
                    if ( isEmpty( root ) ) {
                        //If true, exit from the procedure
                        break;
                    } else {
                        //Else print it
                        postorder( root );
                        break;
                    }
                }//end case 5


            //Printing the BST tree-like
            case 6: {
                    if ( isEmpty( root ) ) {
                        //If true, exit from the procedure
                        break;
                    } else {
                        //Else print it
                        Display( root, 0 );
                        break;
                    }
                }//end case 6


            //Determine and print the minimum and maximum of the BST
            case 7: {
                    //Check if the tree is empty (the call is made upon the root)
                    if ( !isEmpty( root ) ) {
                        //If not retrieve the maximum and minimum
                        g_minimum = getMin( root );
                        g_maximum = getMax( root );
                        //Print them
                        printf( "\nMinimum: %d \nMaximum %d\n", g_minimum, g_maximum );

                    }
                    break;
                }//end case 7


            //Randomly insert a number of values in the BST
            case 8: {
                    //Define an iterator and a number of values
                    int iterator1 = 0, no_values = 0;
                    printf( "\nHow many values would you like to insert?\n" );
                    //Read the number of values
                    scanf( "%d", &no_values );

                    //Insert a number of values
                    for ( iterator1 = 0; iterator1 < no_values; iterator1++ ) {
                        root = Add_Node( root, randomNumberGenerator() );
                    }

                    break;
                }//end case 8


            //Check if the BST's values are bounded
            case 9: {
                    //Check if the tree is empty
                    if ( !isEmpty( root ) ) {
                        printf( "\n Boundedness values:" );
                        //Read the desired boundedness values
                        scanf( "%d %d", &minimum, &maximum );

                        //Retrieve the BST minimum and maximum
                        g_maximum = getMax( root );
                        g_minimum = getMin( root );

                        //Check if all the values are bounded
                        bool status = checkValues( root, minimum, maximum );

                        //IF the function returns true, then all the values are bounded, false otherwise
                        if ( true == status ) {
                            printf( "\nOK!\n" );
                        } else {
                            printf( "\nNO!\n" );
                        }

                    }

                    break;
                }//end case 9


            //Testing file
            case 10: {
                    //Define the key to be inserted
                    int key;
                    //Define the task selection
                    char option;
                    //Open the input file
                    printf( "\nAttempting to open file...\n" );
                    FILE *fp = fopen( "input.txt", "r" );

                    //Check if the file was successfully opened
                    if ( !fp ) {
                        //If not, warn the user and exit the program
                        perror( "Unable to open file" );
                        exit( 0 );
                        //Else start the tasks
                    } else {
                        printf( "Success!\n" );
                        //Continue reading while there is something to read
                        while ( !feof( fp ) ) {
                            //Red each line and check the task selection
                            fscanf( fp, "%c", &option );

                            // "I" is for inserting
                            if ( option == 'I' ) {
                                //Read the value
                                fscanf( fp, "%d", &key );
                                //Insert it in the BSt
                                root = Add_Node( root, key );
                                //"D" is for deleting
                            } else if ( option == 'D' ) {
                                //Read the value
                                fscanf( fp, "%d", &key );
                                //Delete it
                                root = Delete( root, key );
                                //"M" is for maximum and minimum
                            } else if ( option == 'M' ) {
                                //Retrieve the minimum and maximum, then print them
                                g_maximum = getMax( root );
                                g_minimum = getMin( root );
                                printf( "\n The GLOBAL minimum and maximum are :%d %d", g_minimum, g_maximum );
                                //"V" checks boundedness
                            } else if ( option == 'V' ) {
                                //Check if the BST is empty
                                if ( !isEmpty( root ) ) {
                                    //Retrieve the BSTS's minimum and maximum
                                    g_minimum = getMin( root );
                                    g_maximum = getMax( root );
                                    printf( "\nMinimum and maximum of the current BST are: %d %d", g_minimum, g_maximum );

                                    //Read the boundedness values from file
                                    fscanf( fp, "%d %d ", &minimum, &maximum );
                                    //rewind(fp);

                                    printf( "\nBoundedness values set to : %d %d", minimum, maximum );

                                    //Check if all the values are bounded
                                    bool status = checkValues( root, minimum, maximum );

                                    printf( "\nBoundedness result : " );
                                    //IF the function returns true, then all the values are bounded, false otherwise
                                    if ( true == status ) {
                                        printf( "PASSED!\n" );
                                    } else {
                                        printf( "FAILED!\n" );
                                    }
                                }
                            }
                        }
                        printf( "\nClosing file...\n" );
                        printf( "Success!\n" );
                        //Close the file
                        fclose( fp );

                    }//end else
                    break;
                }//end case 10


            //Delete the entire BST
            case 11:{
                //Check if the BST is empty
                if(isEmpty(root)){
                        break;
                   }else{
                       //Else proceed to deletion
                        deleteBST(&root);
                   }
                break;

            }//end case 11


            case 12:{
                makeTests(root,300);
                break;
            }//end case 12


            //Exit
            case 13:{
                printf( "\nExiting...." );
                exit( 0 );
            }//end case 11

        }//end switch


    } while ( choice );

    return 0;

}//end main
