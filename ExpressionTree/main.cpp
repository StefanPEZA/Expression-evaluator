#include <iostream>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <winbgim.h>


using namespace std;

#include "abstract.h"



int main()
{
    char infix[101];

    cout << "Give the infix expression: ";
    cin.getline(infix, 100);

    cout << "\n";
    char *postfix = NULL;
    postfix = infixToPostfix(infix);

    Node* root = NULL;
    if (postfix != NULL)
    {
        root = constructExpressionTree(postfix);
        free(postfix);

        char result[] = "";
        postfixOrder(root, result);
        cout << "Postfix order from tree: "<< result <<endl;

        strcpy(result, "");
        prefixOrder(root, result);
        cout <<"Prefix order from tree: "<< result << endl;

        strcpy(result, "");
        infixOrder(root, result);
        cout <<"Infix order from tree: " << result << endl;

        cout << endl << eval(root) << endl << endl;



        cout << "Do you want to draw the tree: Y/N (Press Y - for yes)";
        if (_getch() == 'y' || _getch() == 'Y')
            DrawTree(root, 950, 600);

    }
    else
        cout << "Invalid expression" << endl;


    cout << "\n\nPress any key to exit...";
    _getch();
}
