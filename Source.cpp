#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>

using namespace std;
double MSL = 0;
vector<int> ARR;
vector<int> Temp;
struct Node
{
	int a;
	int h = 0;
	int lh = 0;
	int len = 0;
	int b = 0;
	int av = 0;
	int c = 0;
	Node *l, *r, *parent;
};
ifstream fin("input.txt");//tst.in
ofstream fout("output.txt");//tst.out
void print(Node *&tree)
{
	if (tree != NULL)
	{
		fout << tree->a << endl;
		print(tree->l);
		print(tree->r);
	}
}
void add_Node(int a, Node *&MyTree)
{
	if (MyTree == NULL)
	{
		MyTree = new Node;
		MyTree->a = a;
		MyTree->l = NULL;
		MyTree->r = NULL;
		MyTree->parent = NULL;
	}
	if (a < MyTree->a)
	{
		if (MyTree->l != NULL)
			add_Node(a, MyTree->l);
		else
		{
			MyTree->l = new Node;
			MyTree->l->l = NULL;
			MyTree->l->r = NULL;
			MyTree->l->parent = MyTree;
			MyTree->l->a = a;
		}
	}
	if (a > MyTree->a)
	{
		if (MyTree->r != NULL)
			add_Node(a, MyTree->r);
		else
		{
			MyTree->r = new Node;
			MyTree->r->a = a;
			MyTree->r->parent = MyTree;
			MyTree->r->l = NULL;
			MyTree->r->r = NULL;

		}
	}
}
Node* del(Node *&tree, int k)
{
	if (tree == NULL)
		return NULL;

	if (k < tree->a)
	{
		tree->l = del(tree->l, k);
		return tree;
	}
	else if (k > tree->a)
	{
		tree->r = del(tree->r, k);
		return tree;
	}
	if (k == tree->a)
	{
		if (tree->l == NULL)
			return tree->r;
		else
			if (tree->r == NULL)
				return tree->l;
			else
			{
				Node *temp = tree->r;
				while (temp->l)
					temp = temp->l;
				tree->r = del(tree->r, temp->a);
				tree->a = temp->a;
				return tree;
			}
	}

}
double max(int a, int  b)
{
	if (a > b)
		return a;
	else
		return b;
}

void high(Node *&tree)
{
	if (tree != NULL)
	{
		high(tree->l);
		high(tree->r);
		if ((tree->l == NULL&&tree->r==NULL))
		{
			tree->h = 0;
			tree->lh = 1;
		}
		else
			if ((tree->l == NULL && tree->r != NULL) || (tree->l != NULL && tree->r == NULL))
			{
				if (tree->l != NULL)
				{
					tree->h = tree->l->h + 1;
					tree->lh = tree->l->lh;
					tree->len = tree->l->h + 1;
					ARR.push_back(tree->l->h + 1);
				}
				if (tree->r != NULL)
				{
					tree->h = tree->r->h + 1;
					tree->lh = tree->r->lh;
					tree->len = tree->r->h + 1;
					ARR.push_back(tree->r->h + 1);
				}
			}
			else
			{
				tree->h = max(tree->l->h, tree->r->h) + 1;
				tree->len = tree->l->h + tree->r->h + 2;
				ARR.push_back(tree->l->h + tree->r->h + 2);
				if (tree->r->h == tree->l->h)
				{
					tree->lh = tree->r->lh + tree->l->lh;
				}
				else
				{
					if (tree->r->h > tree->l->h)
						tree->lh = tree->r->lh;
					else
						tree->lh = tree->l->lh;
				}
			}
	}
}
void preorder(Node*&tree)
{
	if (tree != NULL)
	{
		if ((tree->l == NULL && tree->r == NULL))
		{			
				tree->b = 0;
				if ((tree->av + tree->b!=0)&&(tree->av + tree->b)%2==0)
				{
					Temp.push_back(tree->a);
				}
		}
		else
			if ((tree->l == NULL && tree->r != NULL) || (tree->l != NULL && tree->r == NULL))
			{
				if (tree->l != NULL)
				{
					if (tree->len == MSL)
						tree->b = tree->l->lh;
					tree->l->av = tree->av + tree->b;
				}
				if (tree->r != NULL)
				{
					if (tree->len == MSL)
						tree->b = tree->r->lh;

					tree->r->av = tree->av + tree->b;
				}
				if ((tree->av + tree->b != 0) && ((tree->av + tree->b) % 2 == 0))
				{
					Temp.push_back(tree->a);
				}
			}
			else
			{
				if (tree->len == MSL)
				{
					tree->b = tree->l->lh*tree->r->lh;
				}

				if (tree->l->h > tree->r->h)
				{
					tree->l->av = tree->av + tree->b;
					tree->r->av = tree->b;
				}
				if (tree->r->h > tree->l->h)
				{
					tree->r->av = tree->av + tree->b;
					tree->l->av = tree->b;
				}
				if (tree->r->h == tree->l->h)
				{
					tree->l->av = tree->b + tree->l->lh*(tree->av/tree->lh);
					tree->r->av = tree->b + tree->r->lh*(tree->av/tree->lh);
				}
				if ((tree->av + tree->b != 0) && ((tree->av + tree->b) % 2 == 0))
				{
					Temp.push_back(tree->a);
				}
			}

		preorder(tree->l);
		preorder(tree->r);
	}
}

int main()
{
	Node*Tree = NULL;
	int i;
	while (fin >> i)
	{
		add_Node(i, Tree);
	}
	Tree->av = 0;
	high(Tree);
	sort(ARR.rbegin(), ARR.rend());
	MSL = ARR[0];
	preorder(Tree);
	if (Temp.size() == 0)
	{


	}
	else
	{
		sort(Temp.rbegin(), Temp.rend());
		Tree=del(Tree, Temp[Temp.size() - 1]);
	}
	print(Tree);
	return 0;
}