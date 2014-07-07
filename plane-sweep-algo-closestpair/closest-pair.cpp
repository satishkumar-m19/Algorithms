#include <iostream>
#include <cstdlib>

using namespace std;

#define sqr(x) ((x)*(x))
#define distance(x1,y1,x2,y2) (sqr(x1-x2) + sqr(y1-y2))

typedef struct ctreenode *ctree;
/*
 * Tree Node Declaration
 */
struct ctreenode
{
    int key, priority;
    ctree left, right;
};

struct Point
{
    int x, y;
};

ctree nullnode, root;

/*
 * Treap Class Declaration
 */
class CTree
{
    public:
        void initialize();
        void sigrotl(ctree &);
        void sigrotr(ctree &);
        void insert(ctree &, Point);
        void remove(ctree &, Point);
        void display(ctree, int);
        void inorder(ctree, Point, int &, Point &, Point &);
        bool find(ctree, int);
        CTree()
        {}
};
/*
 * Initializing node
 */
void CTree::initialize()
{
    nullnode = new ctreenode;
    nullnode->left = nullnode->right = nullnode;
    root = nullnode;
}

/*
 * Left Rotation
 */
void CTree::sigrotl(ctree& k1)
{
    ctree k2;
    k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1 = k2;
}

/*
 * Right Rotation
 */
void CTree::sigrotr(ctree& k1)
{
    ctree k2;
    k2 = k1->left;
    k1->left = k2->right;
    k2->right = k1;
    k1 = k2;
}
/*
 * Insert Element into Treap
 */
void CTree::insert(ctree& t, Point P)
{
    if (t == nullnode)
    {
        t = new ctreenode;
        t->left = t->right = nullnode;
        t->key = P.y;
        t->priority = P.x;
    }
    else
    {
        if (t->key == P.y)
        {
            return;
        }
        else
        {
            if (P.y < t->key)
            {
                insert(t->left, P);
                if (t->left->priority > t->priority)
                    sigrotr(t);
            }
            else
            {
                insert(t->right, P);
                if (t->right->priority > t->priority)
                sigrotl(t);
            }
        }
    }
}

/*
 * Remove Element from Treap
 */
void CTree::remove(ctree& t, Point P)
{
    if (t == nullnode)
        return;
    if (P.y > t->key)
        remove(t->right, P);
    else if (P.y < t->key)
        remove(t->left, P);
    else
    {
        if (t->left == nullnode && t->right == nullnode)
        {
            delete t;
            t = nullnode;
        }
        else if (t->left == nullnode)
        {
            ctree tmp = t;
            t = t->right;
            delete tmp;
        }
        else if (t->right == nullnode)
        {
            ctree tmp = t;
            t = t->left;
            delete tmp;
        }
        else
        {
            if (t->left->priority < t->right->priority)
            {
                sigrotl(t);
                remove(t->left, P);
            }
            else
            {
                sigrotr(t);
                remove(t->right, P);
            }
        }
    }
}
/*
 * Search an element in Treap
 */
bool CTree::find(ctree t,int x)
{
    if (t == nullnode)
        return false;
    if (t->key == x)
        return true;
    else
    {
        if (x < t->key)
            return find(t->left, x);
        else
            return find(t->right, x);
    }
}
/*
 * Display elements of Treap
 */
void CTree::display(ctree ptr, int level)
{
    int i;
    if (ptr == nullnode)
        return;
    if (ptr != NULL)
    {
        display(ptr->right, level + 1);
        cout<<endl;
        if (ptr == root)
       	   cout<<"Root->:  ";
        else
        {
            for (i = 0; i < level; i++)
                cout<<"       ";
        }
        cout<<ptr->key;
        display(ptr->left, level + 1);
    }
}
/*
 * Inorder Travesal of Treap
 */
void CTree::inorder(ctree ptr,Point P,int& d , Point& closePairP1,Point& closePairP2)
{
    int d_temp;
    if (ptr == nullnode)
        return;
    if (ptr != NULL)
    {
        inorder(ptr->left, P, d , closePairP1, closePairP2);
        cout<< ptr->priority <<" " << ptr->key << endl;
        //function call with if condition
        if(((P.y - d) <  (ptr->key)) && ((ptr->key) < (P.y + d))){
            d_temp = distance(P.x,P.y,ptr->priority,ptr->key);
            if (d_temp < d){
                d = d_temp;
                closePairP1.x =  ptr->priority ;
                closePairP1.y =  ptr->key ;
                closePairP2 = P;
            }
        } 
        inorder(ptr->right, P, d , closePairP1, closePairP2);
    }
}

// Needed to sort array of points according to X coordinate
int compareX(const void* a, const void* b)
{
    Point *p1 = (Point *)a,  *p2 = (Point *)b;
    return (p1->x - p2->x);
}

void processPoints(int n, Point P[], CTree c){
    cout<<"inside process points";
    int d=0, l=0, r=2, maximumNodes = 0, maxTempnodes = 0;
    Point closePairP1, closePairP2, nextPoint = P[r];
    closePairP1 = P[0];
    closePairP2 = P[1];
    d=distance(P[0].x,P[0].y,P[1].x,P[1].y);
    cout<< d << endl;
    while(P[l].x < (nextPoint.x-d)){
        cout<<"inside while";
        l=l+1;
    }
    cout<< l << " l value ";
    for(int i=l;i<r;i++){
        cout<<"inside for";
        c.insert(root,P[i]);
    }
    while(r<=n){
        //for(int j=0;j<;j++){
            cout<<" Here ";
            c.inorder(root, nextPoint, d , closePairP1, closePairP2); // for is maintained here
            c.insert(root, nextPoint);
            if (r < n){
                nextPoint = P[r+1];
                while(P[l].x < (nextPoint.x-d)){
                    cout<<"inside while";
                    c.remove(root, P[l]);
                    l=l+1;
                }
            }
        //}
        r = r+1;
    }
    cout << endl;
    cout << "minimum distance :  " <<  d <<endl ;
    cout << "closest pairs co-ordinates : "<<closePairP1.x << "  "<< closePairP1.y << "  " << closePairP2.x << "  "<< closePairP2.y << endl;
}

int main()
{
    CTree ct;
    int n, choice, num, dmin=0;
    bool flag = false;
    ct.initialize();

    cout<<"Enter number of points : ";
    cin>>n;
    Point *pt = new Point[n];
    Point Px[n];
    if (pt == 0) {
        cout << "Error assigning memory.";
    }
    else{
        for (int i = 0; i < n; i++) {
            cout << "Enter x and y : ";
            std::cin >> pt[i].x >> pt[i].y;
            cout << endl;
        }
    }
    /*for(int i=0;i<n;i++){
        cout<<pt[i].x<<"\t"<<pt[i].y<<endl;
    }*/
    for (int i = 0; i < n; i++)
    {
        Px[i] = pt[i];
    }

    qsort(Px, n, sizeof(Point), compareX);

    processPoints(n,Px, ct);
    /*for (int i = 0; i < n; i++)
    {
        ct.insert(root,Px[i]);
    }

    /*cout<<"Inorder Traversal:"<<endl;
    ct.inorder(root);*/

    cout<<"After sorting "<<endl;
    for(int i=0;i<n;i++){
        cout<<Px[i].x<<"\t"<<Px[i].y<<endl;
    }

    delete[] pt;
}

