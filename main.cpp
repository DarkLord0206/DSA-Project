#include <iostream>
#include <cmath>
#include <vector>
#include <math.h>
#include <bits/stdc++.h>
using namespace std;
 
// Used to hold details of a point
struct Point
{
    int x;
    int y;
 
    Point(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
    Point()
    {
        x = 0;
        y = 0;
    }
};
struct Circle
{
    Point center;
    float radius;
    Circle(int x,int y,float rad)
    {
        center=Point(x,y);
        radius=rad;
    }
};
struct Rectangle
{
    Point center;
    Point topLeft;
    Point botRight;
    Rectangle(Point _topLeft,Point _botRight)
    {
        topLeft=_topLeft;
        botRight=_botRight;
        center=Point((topLeft.x+botRight.x)/2,(topLeft.y+botRight.y)/2);
    }
};
 
// The objects that we want stored in the quadtree
struct Node
{
    Point pos;
    int data;
 
    Node(Point _pos, int _data)
    {
 
        pos = _pos;
        data = _data;
    }
    Node()
    {
 
        data = 0;
    }
};
 
// The main quadtree class
class Quad
{
    // Hold details of the boundary of this node
    string loc;
    Point topLeft;
    Point botRight;
    Quad *parent;
 
    // Contains details of node
    Node *n;
 
    // Children of this tree
    Quad *topLeftTree;
    Quad *topRightTree;
    Quad *botLeftTree;
    Quad *botRightTree;
 
public:
    Quad()
    {
        topLeft = Point(0, 0);
        botRight = Point(0, 0);
        n = NULL;
        parent=NULL;
        topLeftTree  = NULL;
        topRightTree = NULL;
        botLeftTree  = NULL;
        botRightTree = NULL;
        loc="";
    }
    Quad(Point topL, Point botR, Quad* _parent, string rel_loc)
    {
        parent=_parent;
        n = NULL;
        topLeftTree  = NULL;
        topRightTree = NULL;
        botLeftTree  = NULL;
        botRightTree = NULL;
        topLeft = topL;
        botRight = botR;
        if (_parent!=NULL)
        {
            loc = parent->loc + rel_loc;
        }
        else loc=rel_loc;
    }
    void insert(Node*);
    Node* search(Point);
    void rangeQuery(Circle cir,vector<Node> &ans);
    void rangeQuery(Rectangle rec,vector<Node> &ans);
    void subDivide();
    bool inBoundary(Point p);
    Node* nearestNeighbour(Point target);
    // vector<Node> rangeQuery(Rectangle rec);
};
 
 
void Quad::insert(Node *node)
{
    if (node == NULL)
    {
        return;
    }
    // Current quad cannot contain it
    if (!inBoundary(node->pos))
    {
        return;
    }
    if(n == NULL)
    {
        if(topLeftTree == NULL)
        {
            n = node;
            return;
        }
        else
        {
            if ((topLeft.x + botRight.x) / 2 >= node->pos.x)
            {
                // Indicates topLeftTree
                if ((topLeft.y + botRight.y) / 2 >= node->pos.y)
                {
                    topLeftTree->insert(node);
                }
 
                // Indicates botLeftTree
                else
                {
                    botLeftTree->insert(node);
                }
            }
            else
            {
                // Indicates topRightTree
                if ((topLeft.y + botRight.y) / 2 >= node->pos.y)
                {
                    topRightTree->insert(node);
                }
 
                // Indicates botRightTree
                else
                {
                    botRightTree->insert(node);
                }
            }
        }
    }
    else
    {
        this->subDivide();
        n=NULL;
        if ((topLeft.x + botRight.x) / 2 >= node->pos.x)
        {
            // Indicates topLeftTree
            if ((topLeft.y + botRight.y) / 2 >= node->pos.y)
            {
                topLeftTree->insert(node);
            }
 
            // Indicates botLeftTree
            else
            {
                botLeftTree->insert(node);
            }
        }
        else
        {
            // Indicates topRightTree
            if ((topLeft.y + botRight.y) / 2 >= node->pos.y)
            {
                topRightTree->insert(node);
            }
 
            // Indicates botRightTree
            else
            {
                botRightTree->insert(node);
            }
        }
    }
 
 
}
 
void Quad::subDivide()
{
    botRightTree = new Quad(
        Point((topLeft.x + botRight.x) / 2,
            (topLeft.y + botRight.y) / 2),
        Point(botRight.x, botRight.y),this, "11");
 
   topRightTree = new Quad(
        Point((topLeft.x + botRight.x) / 2,
            topLeft.y),
        Point(botRight.x,
            (topLeft.y + botRight.y) / 2),this, "00"); 
 
    botLeftTree = new Quad(
        Point(topLeft.x,
            (topLeft.y + botRight.y) / 2),
        Point((topLeft.x + botRight.x) / 2,
            botRight.y),this, "10");
 
    topLeftTree = new Quad(
        Point(topLeft.x, topLeft.y),
        Point((topLeft.x + botRight.x) / 2,
            (topLeft.y + botRight.y) / 2),this, "01");
 
    if ((topLeft.x + botRight.x) / 2 >= n->pos.x)
    {
        // Indicates topLeftTree
        if ((topLeft.y + botRight.y) / 2 >= n->pos.y)
        {
            topLeftTree->insert(n);
        }
 
        // Indicates botLeftTree
        else
        {
            botLeftTree->insert(n);
        }
    }
    else
    {
        // Indicates topRightTree
        if ((topLeft.y + botRight.y) / 2 >= n->pos.y)
        {
            topRightTree->insert(n);
        }
 
        // Indicates botRightTree
        else
        {
            botRightTree->insert(n);
        }
    }
}
 
// Find a node in a quadtree
Node* Quad::search(Point p)
{
    // Current quad cannot contain it
    if (!inBoundary(p))
    {
        return NULL;
    }
    // We are at a quad of unit length
    // We cannot subdivide this quad further
    if (n != NULL)
    {
        if(n->pos.x==p.x && n->pos.y==p.y)
        {
            return n;
        }
        else
        {
            return NULL;
        }
    }
    if ((topLeft.x + botRight.x) / 2 >= p.x)
    {
        // Indicates topLeftTree
        if ((topLeft.y + botRight.y) / 2 >= p.y)
        {
            if (topLeftTree == NULL)
                return NULL;
            return topLeftTree->search(p);
        }
 
        // Indicates botLeftTree
        else
        {
            if (botLeftTree == NULL)
                return NULL;
            return botLeftTree->search(p);
        }
    }
    else
    {
        // Indicates topRightTree
        if ((topLeft.y + botRight.y) / 2 >= p.y)
        {
            if (topRightTree == NULL)
                return NULL;
            return topRightTree->search(p);
        }
 
        // Indicates botRightTree
        else
        {
            if (botRightTree == NULL)
                return NULL;
            return botRightTree->search(p);
        }
    }
};
bool Quad::inBoundary(Point p)
{
    return (p.x >= topLeft.x &&
        p.x <= botRight.x &&
        p.y >= topLeft.y &&
        p.y <= botRight.y);
}
// Check if current quadtree contains the point
bool inBoundaryRect(Point p,Rectangle rec)
{
    return (p.x >= rec.topLeft.x &&
        p.x <= rec.botRight.x &&
        p.y >= rec.topLeft.y &&
        p.y <= rec.botRight.y);
}
bool inBoundaryCircle(Point p,Circle cir)
{
    float dist=(p.x-cir.center.x)*(p.x-cir.center.x)+(p.y-cir.center.y)*(p.y-cir.center.y);
    dist=sqrt(dist);
    return dist-cir.radius<0.00001;
}
void Quad::rangeQuery(Circle cir,vector<Node> &ans)
{
    Point a1=topLeft;
    Point a3=botRight;
    Point a2 = Point(botRight.x,topLeft.y);
    Point a4 = Point(topLeft.x,botRight.y);
    if(inBoundaryCircle(a1,cir) || inBoundaryCircle(a2,cir) || inBoundaryCircle(a3,cir) || inBoundaryCircle(a4,cir))
    {
        if(n==NULL)
        {
            if(topLeftTree!=NULL)
            {
                topLeftTree->rangeQuery(cir,ans);
            }
            if(botRightTree!=NULL)
            {
                botRightTree->rangeQuery(cir,ans);
            }
            if(topRightTree!=NULL)
            {
                topRightTree->rangeQuery(cir,ans);
            }
            if(botLeftTree!=NULL)
            {
                botLeftTree->rangeQuery(cir,ans);
            }
        }
        else
        { 
            if(inBoundaryCircle(n->pos,cir))
            { 
                ans.push_back(*n);
            }
        }
    }
    else
    {   
        if(inBoundary(cir.center))
        {
            if(n==NULL)
            {
                if(topLeftTree!=NULL)
                    topLeftTree->rangeQuery(cir,ans);
                if(botRightTree!=NULL)
                    botRightTree->rangeQuery(cir,ans);
                if(topRightTree!=NULL)
                    topRightTree->rangeQuery(cir,ans);
                if(botLeftTree!=NULL)
                    botLeftTree->rangeQuery(cir,ans);
            }
            else if(inBoundaryCircle(n->pos,cir))
            { 
                ans.push_back(*n);
            }
        }
    }
}
void Quad::rangeQuery(Rectangle rec,vector<Node> &ans)
{
    Point a1=topLeft;
    Point a3=botRight;
    Point a2 = Point(botRight.x,topLeft.y);
    Point a4 = Point(topLeft.x,botRight.y);
    if(inBoundaryRect(a1,rec) || inBoundaryRect(a2,rec) || inBoundaryRect(a3,rec) || inBoundaryRect(a4,rec))
    {
        if(n==NULL)
        {
            if(topLeftTree!=NULL)
            {
                topLeftTree->rangeQuery(rec,ans);
            }
            if(botRightTree!=NULL)
            {
                botRightTree->rangeQuery(rec,ans);
            }
            if(topRightTree!=NULL)
            {
                topRightTree->rangeQuery(rec,ans);
            }
            if(botLeftTree!=NULL)
            {
                botLeftTree->rangeQuery(rec,ans);
            }
        }
        else
        { 
            if(inBoundaryRect(n->pos,rec))
            { 
                ans.push_back(*n);
            }
        }
    }
    else
    {   
        if(inBoundaryRect(rec.center,Rectangle(topLeft,botRight)))
        {
            if(n==NULL)
            {
                if(topLeftTree!=NULL)
                    topLeftTree->rangeQuery(rec,ans);
                if(botRightTree!=NULL)
                    botRightTree->rangeQuery(rec,ans);
                if(topRightTree!=NULL)
                    topRightTree->rangeQuery(rec,ans);
                if(botLeftTree!=NULL)
                    botLeftTree->rangeQuery(rec,ans);
            }
            else if(inBoundaryRect(n->pos,rec))
            { 
                ans.push_back(*n);
            }
        }
    }
}
Node* Quad::nearestNeighbour(Point target)
{
    int size=1;
    vector<Node> ans;
    while(true)
    {
        Rectangle area(Point(target.x-size,target.y-size),Point(target.x+size,target.y+size));
        rangeQuery(area,ans);
        size++;
        if(ans.size()>0)
        {
            break;
        }
    }
    Node *anser;
    float dist=-1;
    for(auto k:ans)
    {
        float temp_dist=(k.pos.x-target.x)*(k.pos.x-target.x)+(k.pos.y-target.y)*(k.pos.y-target.y);
        temp_dist=sqrt(temp_dist);
        cout<<temp_dist<<endl;
        if(dist==-1 || temp_dist<dist)
            anser=&k;
    }
    return anser;
}
// stuff to add
// range querry box and circle
// json file with all data
// nearest neighbour
// remove point
// edit file and change vars
// visuals
 
// Driver program
int main()
{ 
    Quad center(Point(0, 0), Point(9, 9),NULL, "");
    Node a(Point(1, 1), 1);
    Node b(Point(2, 5), 2);
    Node c(Point(7, 6), 5);
    Node d(Point(2,2),3);
    center.insert(&d);
    center.insert(&a);
    center.insert(&b);
    center.insert(&c);
    cout << "Node a: " <<
        center.search(Point(1, 1))->data << "\n";
    cout << "Node b: " <<
        center.search(Point(2, 5))->data << "\n";
    cout << "Node c: " <<
        center.search(Point(7, 6))->data << "\n";
    vector<Node> ans;
    center.rangeQuery(Rectangle(Point(0,0),Point(8,8)),ans);
    cout<<center.nearestNeighbour(Point(3,3))->data<<endl;
    // cout<<ans.size();
    for(auto &x : ans)
    {
        cout<<x.data<<" ";
    }
    return 0;
}