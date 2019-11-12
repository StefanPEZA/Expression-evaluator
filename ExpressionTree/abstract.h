#include <math.h>
#include "converters.h"
#include "BinaryTree.h"
char* EmptyString()
{
    char *result = (char*)malloc(sizeof(char));
    result[0] = '\0';
    return result;
}
//stack
typedef struct Stack
{
    char *data;
    Stack* next;
} Stack;

struct Variable
{
    char* name;
    float value;

} var[100];
int var_Nr = -1;

void deleteVar()
{
    var_Nr = -1;
    int i = 0;
    while(i < 100 && var[i].name != NULL)
    {
        var[i].name = NULL;
        var[i].value = 0;
        i++;
    }

}

bool isEmpty(void* top)
{
    if (top == NULL)
        return true;
    else
        return false;
}

void push(Stack** top, char *value)
{
    struct Stack *newNode;
    newNode = (struct Stack*)malloc(sizeof(struct Stack));
    newNode->data = value;
    if((*top) == NULL)
        newNode->next = NULL;
    else
        newNode->next = (*top);
    (*top) = newNode;
}

void pop(Stack** top)
{
    if((*top) == NULL)
        return;
    else
    {
        struct Stack *temp = (*top);
        (*top) = temp->next;
        free(temp);
    }
}

char* top(Stack* top)
{
    if (top == NULL)
        return NULL;
    else
        return top->data;
}



bool isOperand(char ch);
bool isOperator(char ch);
int Priority(char ch);

char* infixToPostfix(char infix[])
{
    char* postfix = EmptyString();
    Stack* S = NULL;

    for (unsigned int i = 0; i<strlen(infix); ++i)
    {

        // If the scanned character is an operand, add it to output.
        if (isOperand(infix[i]) || infix[i] == '.')
            strncat(postfix, infix+i, 1);

        // If the scanned character is an '(', push it to the stack.

        else if (infix[i] == '(')
        {
            if (i == strlen(infix)-1)
                return NULL;
            char c[2] = "(";
            push(&S, c);
        }


        // If the scanned character is an ')', pop and output from the stack
        // until an '(' is encountered.
        else if (infix[i] == ')')
        {
            if (i == 0)
            {
                return NULL;
            }
            char c[2] = "(";
            while (!isEmpty(S) && strcmp(top(S),c))
            {
                strcat(postfix, " ");
                strcat(postfix, top(S));
                pop(&S);
            }
            pop(&S);
        }
        else if (isOperator(infix[i]))// an operator is encountered
        {
            if (i==0 || i==strlen(infix)-1)
            {
                return NULL;
            }
            strcat(postfix, " ");
            while (!isEmpty(S) && Priority(infix[i]) <= Priority(top(S)[0]) && infix[i] != '^')
            {

                strcat(postfix, top(S));
                strcat(postfix, " ");
                pop(&S);
            }
            char *d = EmptyString();
            strncat(d, infix+i, 1);
            push(&S, d);


        }
        else if(infix[i] == ' ') {}
        else
            return NULL;

    }

    // pop all the operators from the stack
    while (!isEmpty(S))
    {
        char d[2] = "(";
        if(!strcmp(top(S),d))
            return NULL;
        strcat(postfix, " ");
        strcat(postfix, top(S));
        pop(&S);
    }

    return postfix;
}


Node* constructExpressionTree(char postfix[])
{
    treeStack *st = NULL;
    Node *t, *t1, *t2;
    char *postFIX[strlen(postfix)];

    char* p;
    p = strtok(postfix, " ");
    int L = 0;
    while (p)
    {
        if (strcmp(p, " "))
        {
            postFIX[L] = EmptyString();
            strcat(postFIX[L], p);
            L ++;
            p = strtok(NULL, " ");
        }
    }

    // Traverse through every character of
    // input expression
    for (int i=0; i<L; i++)
    {
        // If operand, simply push into stack
        if (!isOperator(postFIX[i][0]))
        {
            t = createNode(postFIX[i]);
            treePush(&st, t);
        }
        else // operator
        {
            t = createNode(postFIX[i]);

            // Pop two top nodes
            t1 = treeTop(st); // Store top
            treePop(&st);      // Remove top
            t2 = treeTop(st);
            treePop(&st);

            //  make them children
            t->right = t1;
            t->left = t2;

            // Add this subexpression to stack
            treePush(&st, t);
        }
    }

    //  only element will be root of expression
    // tree
    t = treeTop(st);
    treePop(&st);

    return t;
}

bool isOperand(char ch)
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >='0' && ch <= '9'))
        return true;
    else
        return false;
}

bool isOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^')
        return true;
    else
        return false;
}

int Priority(char ch)
{
    if (ch == '+' || ch == '-')
        return 1;
    else if (ch == '*' || ch == '/')
        return 2;
    else if (ch == '^')
        return 3;
    else
        return -1;
}

bool isNumber(char *str)
{
    if (str[0] >= '0' && str[0]<= '9')
    {
        return true;
    }
    else
        return false;
}

float eval(Node* root)
{
    if (root == NULL)
        return 0;

    if (root->left == NULL && root->right == NULL)
    {
        if (isNumber(root->data))
            return stringToNumber(root->data);
        else
        {
            int i = 0;
            while(i < 100 && var[i].name != NULL)
            {
                if (!strcmp(var[i].name, root->data))
                    return var[i].value;
                i++;
            }
            var_Nr += 1;
            var[var_Nr].name = root->data;
            std::cout << root->data << " = ";
            std::cin >> var[var_Nr].value;
            return var[var_Nr].value;

        }
    }

    float left_nr = eval(root->left);

    float right_nr = eval(root->right);

    if (!strcmp(root->data, "+"))
    {
        return left_nr + right_nr;
    }
    else  if (!strcmp(root->data, "-"))
    {
        return left_nr - right_nr;
    }
    else  if (!strcmp(root->data, "*"))
    {
        return left_nr * right_nr;
    }
    else if (!strcmp(root->data, "/"))
    {
        return left_nr / right_nr;
    }
    else
    {
        return pow(left_nr, right_nr);
    }


}


