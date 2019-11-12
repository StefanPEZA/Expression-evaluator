

typedef struct Node
{
    char *data;
    short x;
    short y;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(char *data)
{
    struct Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void infixOrder(Node* root, char* result)
{
    if (root == NULL)
        return;

    if (root->left != NULL && root->right != NULL)
    {
        strcat(result, "(");
    }

    infixOrder(root->left, result);
    strcat(result, root->data);
    infixOrder(root->right, result);

    if (root->left != NULL && root->right != NULL)
    {
        strcat(result, ")");
    }
}

void postfixOrder(Node* root, char* result)
{
    if (root == NULL)
        return;
    postfixOrder(root->left, result);
    postfixOrder(root->right, result);
    strcat(result, root->data);
    strcat(result, " ");
}

void prefixOrder(Node* root, char* result)
{
    if (root == NULL)
        return;
    strcat(result, root->data);
    strcat(result, " ");
    prefixOrder(root->left, result);
    prefixOrder(root->right, result);

}


struct treeStack
{
    struct Node* treeData;
    treeStack* next;
};


void treePush(treeStack** top, Node* treeData)
{
    struct treeStack *newNode;
    newNode = (struct treeStack*)malloc(sizeof(struct treeStack));
    newNode->treeData = treeData;
    if((*top) == NULL)
        newNode->next = NULL;
    else
        newNode->next = (*top);
    (*top) = newNode;
}

void treePop(treeStack** top)
{
    if((*top) == NULL)
        return;
    else
    {
        struct treeStack *temp = (*top);
        (*top) = temp->next;
        free(temp);
    }
}

Node* treeTop(treeStack* top)
{
    if (top == NULL)
        return NULL;
    else
        return top->treeData;
}

short maxX;
Node *selNode = NULL;
short mx2 = 0;
short offset;
bool selected = false;
void drawT(Node** root);

void ComputeXY(Node** root, int x, int y)
{
    if ((*root) == NULL)
        return;

    short Xlen = (maxX/2/pow(2, y/60));

    if ((*root)->left != NULL)
        ComputeXY(&((*root)->left), x-Xlen, y+60);
    if ((*root)->right != NULL)
        ComputeXY(&((*root)->right), x+Xlen, y+60);

    (*root)->x = x;
    (*root)->y = y;
}

void updateDraw(Node* root)
{
    drawT(&root);
}
bool firstClick = false;

void DrawTree(Node* root, int width, int height)
{
    initwindow(width, height, "Expression tree drawing...");

    maxX = getmaxx();

    ComputeXY(&root, maxX/2, 60);

    char c = 0;

    setfillstyle(SOLID_FILL, LIGHTGRAY);
    floodfill(0,0,10);
    updateDraw(root);
    while(c!=27)
    {
        if ((GetAsyncKeyState(VK_LBUTTON) && mousey() > 10)|| selNode != NULL)
        {
            if (selNode != NULL || !firstClick)
            {
                setfillstyle(SOLID_FILL, LIGHTGRAY);
                floodfill(0,0,10);
                updateDraw(root);
                firstClick = true;
            }

        }
        else {firstClick = false;}

        if (_kbhit())
            c = _getch();
    }
    closegraph();
}
int mx;
int my;

void drawT(Node** root)
{


    mx = mousex();
    my = mousey();
    if (GetAsyncKeyState(VK_LBUTTON))
    {

        if (((my<=(*root)->y+17 && my>=(*root)->y-17)&&(mx>=(*root)->x-17 && mx<=(*root)->x+17)) || selNode != NULL)
        {
            if (selected == false)
            {
                offset = mx - (*root)->x;
            }

            if (selected == false)
                selNode = (*root);
            if ((*root) == selNode)
            (*root)->x = mx - offset;
            selected = true;
        }
    }
    else
    {
        selected = false;
        selNode = NULL;
    }

    if ((*root)->left != NULL && (*root)->right != NULL)
    {

        drawT(&((*root)->left));
        drawT(&((*root)->right));

        setcolor(BLACK);
        line((*root)->x, (*root)->y, (*root)->left->x, (*root)->left->y);
        line((*root)->x, (*root)->y, (*root)->right->x, (*root)->right->y);
    }


    if ((*root) == selNode)
        setcolor(RED);
    else
        setcolor(BLUE);
    setfillstyle(SOLID_FILL, BLACK);
    fillellipse((*root)->x, (*root)->y, 18, 18);
    setcolor(WHITE);
    outtextxy((*root)->x-textwidth((*root)->data)/2, (*root)->y-textheight((*root)->data)/2, (*root)->data);





}
