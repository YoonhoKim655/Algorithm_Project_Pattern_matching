//2016112166 ����ȣ

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <map>
#include <random>
#include <climits>
#include <time.h>

using namespace std;

enum Color { RED, BLACK };

struct Node
{
	int data;
	bool color;
	Node *left, *right, *parent;

	// Constructor 
	Node(int data)
	{
		this->data = data;
		left = right = parent = NULL;
		this->color = RED;
	}
};//Node�� struct

// Red-Black Tree�� Class
class RBTree
{
private:
	Node *root;
protected:
	void rotateLeft(Node *&, Node *&);
	void rotateRight(Node *&, Node *&);
	void fixup(Node *&, Node *&);
public:
	// Constructor 
	RBTree() { root = NULL; }
	void insert(const int &n);
	int search(int n);
};

Node* BSTInsert(Node* root, Node *pt)
{

	if (root == NULL)
		return pt;
	//��� �ִ�  tree�� ��, ���� �ִ� node�� root������ ������ �߽��ϴ�.

	if (pt->data < root->data)
	{
		root->left = BSTInsert(root->left, pt);
		root->left->parent = root;
	}
	else if (pt->data > root->data)
	{
		root->right = BSTInsert(root->right, pt);
		root->right->parent = root;
	}
	/*tree�� ������� ���� ���, ���� �ִ� ���� ��� �������� �� node�� ����
	�񱳸� �ؼ� �ڸ��� ã�� ������ �ڸ��� ���� �־����ϴ�.*/
	else

	return root;
}

int BSTsearch(Node* p, int n)
{
	int result;   // Result returned

	if (p == 0)
		result = 0;//tree�� ����� ��� 0�� return���־����ϴ�.
	else if (n < p->data)
		result = BSTsearch(p->left, n);//searchkey�� element���� ������ left���� �񱳸� ���ִ� �ڵ� �Դϴ�.
	else if (n > p->data)
		result = BSTsearch(p->right, n);//searchkey�� element���� ũ�� right���� �񱳸� ���ִ� �ڵ� �Դϴ�.
	else
	{
		n = p->data;
		result = 1;
	}//searchkey�� element�� ������ 1�� return ���ִ� �ڵ��Դϴ�.

	return result;
}

void RBTree::rotateLeft(Node *&root, Node *&pt)
{
	Node *pt_right = pt->right;

	pt->right = pt_right->left;
	/*������ �߽��̾��� node�� ������ �ڽ��� �߽��� �Ǿ�� �ϹǷ�
	������ �ڽ��� ���� �ڽ��� ���� �߽� node�� ������ �ڽ����� �ٲ���ϴ�.*/
	if (pt->right != NULL)
		pt->right->parent = pt;

	pt_right->parent = pt->parent;
	/*������ �ڽ��� �߽��� �Ǳ� ���ؼ�
	���θ����� �ڽ� ���� �ٲ���ϴ�.*/
	if (pt->parent == NULL)
		root = pt_right;//������ node�� root ���� ���

	else if (pt == pt->parent->left)
		pt->parent->left = pt_right;

	else
		pt->parent->right = pt_right;
	/*���� �� ��Ȳ�� ���� �ڽ����� ������ �ڽ�������
	������ �ϴ� �κ��Դϴ�.*/
	pt_right->left = pt;
	pt->parent = pt_right;
	/*���� �߽ɳ��� ���ο� �߽��� ���� ������ �߽��ϴ�.*/
}

void RBTree::rotateRight(Node *&root, Node *&pt)
{
	Node *pt_left = pt->left;

	pt->left = pt_left->right;

	if (pt->left != NULL)
		pt->left->parent = pt;

	pt_left->parent = pt->parent;

	if (pt->parent == NULL)
		root = pt_left;

	else if (pt == pt->parent->left)
		pt->parent->left = pt_left;

	else
		pt->parent->right = pt_left;

	pt_left->right = pt;
	pt->parent = pt_left;
}/*right-rotation�� ���ʰ� �ݴ�� ��������ϴ�.*/

void RBTree::fixup(Node *&root, Node *&pt)
{
	Node *parent_pt = NULL;
	Node *grand_parent_pt = NULL;

	while ((pt != root) && (pt->color != BLACK) &&
		(pt->parent->color == RED))
	{
		parent_pt = pt->parent;
		grand_parent_pt = pt->parent->parent;

		/*  Case : A
			�θ� node�� ���θ� node�� ���� �ڽ��� ��� */
		if (parent_pt == grand_parent_pt->left)
		{
			Node *uncle_pt = grand_parent_pt->right;

			/* Case : 1
			   �θ�� ���� node�� ����
			   ��� �������� ���*/
			if (uncle_pt != NULL && uncle_pt->color == RED)
			{
				grand_parent_pt->color = RED;
				parent_pt->color = BLACK;
				uncle_pt->color = BLACK;
				pt = grand_parent_pt;
			}
			/*case 1�� �ذ� ��Ŀ� ���� ���θ��� ���� black����
			�θ�� ���� node�� ���� red�� �ٲپ����ϴ�.*/
			else
			{
				/* Case : 2
				   case 1�� �ƴϰ� ���Ե� node�� ��ġ��
				   �θ� node�� ������ �ڽ��� ���*/
				if (pt == parent_pt->right)
				{
					rotateLeft(root, parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}
				/*case 2�� ���� ���Ե� node�� �θ� node��
				�������� left-rotation�� �߽��ϴ�.*/

				/* Case : 3
				   case 1�� �ƴϰ� ���Ե� node�� ��ġ��
				   �θ� node�� ���� �ڽ��� ��� */
				rotateRight(root, grand_parent_pt);
				swap(parent_pt->color, grand_parent_pt->color);
				pt = parent_pt;
				/*�� ���� left-rotation�� �ϰ�
				right-rotation�� �� �� ���ִϴ�*/
			}
		}

		/* Case : B
		 �θ� node�� ���θ� node�� ������ �ڽ��� ���
		 ���� case���� ���� ����.*/
		else
		{
			Node *uncle_pt = grand_parent_pt->left;

			if ((uncle_pt != NULL) && (uncle_pt->color == RED))
			{
				grand_parent_pt->color = RED;
				parent_pt->color = BLACK;
				uncle_pt->color = BLACK;
				pt = grand_parent_pt;
			}
			else
			{
				if (pt == parent_pt->left)
				{
					rotateRight(root, parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}

				rotateLeft(root, grand_parent_pt);
				swap(parent_pt->color, grand_parent_pt->color);
				pt = parent_pt;
			}
		}
	}

	root->color = BLACK;
}


void RBTree::insert(const int &data)
{
	Node *pt = new Node(data);
	//data�� ���� key�� ������ ���ο� node�� ������ �մϴ�.

	root = BSTInsert(root, pt);
	//���ο� node�� ������ �մϴ�.

	fixup(root, pt);
	//���� ���Ե� node�� red-black tree�� Ư���� �°� fix�� ���ݴϴ�.
}

int RBTree::search(int n)
{
	int result = BSTsearch(root, n);

	return result;//ã�� ���� ���� ���, 0�� return�� �߽��ϴ�.
}

void make_ref(char * ref, string F_name)//make_ref(string F_name)/*string F_name*/
{

	random_device rd;//seed ���� ��� ���� random_device ����
	mt19937 gen(rd());//random_device�� ���� ���� ���� ������ �ʱ�ȭ 
	uniform_int_distribution<int> dis(0, 3);//0~3�� ���� �������� ������ �ϴ� �յ� ���� ����
	int i = 0;
	int a = 0, b = 0, c = 0, d = 0;
	while (i < 250000)
	{
		int x = dis(gen);

		switch (x)
		{
		case 0:
			ref[i] = 'A';
			i++;
			a++;
			break;
		case 1:
			ref[i] = 'C';
			i++;
			b++;
			break;
		case 2:
			ref[i] = 'G';
			i++;
			c++;
			break;
		case 3:
			ref[i] = 'T';
			i++;
			d++;
			break;
		}/*switch���� ����� �ؼ� �����Ǵ� random���� ���� reference DNA sequence�� ����*/
	}
	ref[250000] = '\0';
	cout << "a : " << a << " b : " << b << " c : " << c << " d : " << d << " �� : " << (a + b + c + d) << endl;

	ofstream ref_file(F_name);
	ref_file << ref << endl;
	ref_file.close();//file�� ����
	delete[] ref;
}

void make_myDNA(string ref_file, string my_DNA, int k)
{
	char *my = new char[250001];
	char *my1 = new char[250001];
	ifstream refer(ref_file);
	refer.getline(my1, 250001);
	refer.close();// ������ reference DNA�� ������ ��

	int a = (2 * (250000 / k));	//x%

	my = my1;
	random_device rd;//seed ���� ��� ���� random_device ����
	mt19937 gen(rd());//random_device�� ���� ���� ���� ������ �ʱ�ȭ 
	uniform_int_distribution<int> dis(0, 249999);
	uniform_int_distribution<int> new_dis(0, 2);

	for (int i = 0; i <= a; i++)
	{
		int x = dis(gen);
		int new_x = new_dis(gen);

		if (my[x] == 'A')
		{
			switch (new_x)
			{
			case 0:
				my[x] = 'G';
				break;
			case 1:
				my[x] = 'C';
				break;
			case 2:
				my[x] = 'T';
				break;
			}
		}

		else if (my[x] == 'C')
		{
			switch (new_x)
			{
			case 0:
				my[x] = 'A';
				break;
			case 1:
				my[x] = 'G';
				break;
			case 2:
				my[x] = 'T';
				break;
			}
		}

		else if (my[x] == 'G')
		{
			switch (new_x)
			{
			case 0:
				my[x] = 'A';
				break;
			case 1:
				my[x] = 'C';
				break;
			case 2:
				my[x] = 'T';
				break;
			}
		}

		else
		{
			switch (new_x)
			{
			case 0:
				my[x] = 'A';
				break;
			case 1:
				my[x] = 'C';
				break;
			case 2:
				my[x] = 'G';
				break;
			}
		}
	}
	/*������ ���� �Է��� �޾Ƽ� reference DNA�� ��ġ�� ������ �ϰ� �� ��ġ�� ���� ���� �ٽ� random���� �Է��� �޾Ƽ� ���� ���� ���� �Է��� 
	�޴� ���� �������� ������� myDNA�� ���� ��������ϴ�.*/
	my[250000] = '\0';

	ofstream my_file(my_DNA);
	my_file << my << endl;
	my_file.close();
	cout << "mydna" << endl;
}

void shortread(string my_name, string short_name, int k, int n)
{
	random_device rd;//seed ���� ��� ���� random_device ����
	mt19937 gen(rd());//random_device�� ���� ���� ���� ������ �ʱ�ȭ 
	uniform_int_distribution<int> dis(0, 100000 - k);

	char my[100001];

	ifstream refer(my_name);
	refer.getline(my, 100001);//myDNA�� ���ڿ��� ����
	refer.close();
	int q = 0;
	char * short_read = new char[k + 1];
	ofstream short_file(short_name);
	for (int i = 0; i < n; i++)
	{
		int x = dis(gen);
		for (int j = 0; j < k; j++)
		{
			short_read[j] = my[x + j];
		}
		short_read[k] = '\0';
		short_file << short_read << endl;
	}//������ ���� �Է��� �ް� �� ���� ���������� ���ؼ� �־��� ���̸�ŭ�� shortread�� ��������ϴ�.
	short_file.close();
}
int max(int a, int b)
{
	return (a > b) ? a : b;
}

void badCharHeuristic(char* str, int size, int badchar[256])
{
	for (int i = 0; i < 256; i++)
		badchar[i] = size;

	for (int i = 0; i < size; i++)
		badchar[str[i]] = size - 1 - i;
}//���� ���ڿ��� ã���� ��� �̵��Ÿ��� �������ִ� ���� ���� table�Դϴ�.

void sequence(string short_name, string newname, string ref_file, int k, int n)
{
	char ref_[100001];
	char new_my [100001];
	
	RBTree tree;

	ifstream refer(ref_file);
	refer.getline(ref_, 100001);
	refer.close();

	ifstream refer_(ref_file);
	refer_.getline(new_my, 100001);
	refer_.close();

	ifstream short_file(short_name);
	int g = 0;
	
	while (g<n)
	{
		char * short_read = new char[k + 1];
		char * short_read1 = new char[k + 1];

		short_file.getline(short_read,k+1);
		short_read1 = short_read;
		int badchar[256];
		badCharHeuristic(short_read, k, badchar);
		int s = 0;
		while (s <= (100000 - k))
		{
			int j = k - 1;
			int bad;
			int b_i = 0;
			while (j >= 2 && b_i < 3)
			{
				if (short_read1[j] == ref_[s + j])
					j--;
				else
				{
					if (b_i == 0)
					{
						bad = j;
					}		
					b_i++;
				}
					
			}
			if (j < 2)//2�� mismatch ��
			{
				if (tree.search(s) == 1)// ���� �߰��� index�� ���� tree�� ������ ��,
					s += (s + k < 100000) ? k - badchar[ref_[s + k]] : 1;	//���ο� ���� ã���ϴ�.
				else
				{
					tree.insert(s);
					
					for (int a = 0; a < k; a++)
					{
						new_my[s + a] = short_read1[a];
					}
					break;
				}//tree�� �ش� index���� ������ ������ ������ �մϴ�.
			}
			else
				s += max(1, bad - badchar[ref_[s + bad]]);//���� ��� ���� ��ġ�� �̵�
		}
		g++;
		delete[] short_read1;
	}

	short_file.close();
	ofstream my_file(newname);
	my_file << new_my << endl;
	my_file.close();
	
}

void sequence_Brute(string short_name, string newname, string ref_file, int k, int n)
{

	char ref_[100001];
	char new_my[100001];

	RBTree tree;

	ifstream refer(ref_file);
	refer.getline(ref_, 100001);
	refer.close();


	ifstream refer_(ref_file);
	refer_.getline(new_my, 100001);
	refer_.close();

	ifstream short_file(short_name);
	int g = 0;

	while (!short_file.eof())
	{
		char * short_read = new char[k + 1];
		char * short_read1 = new char[k + 1];

		short_file.getline(short_read, k + 1);
		short_read1 = short_read;
		for (int i = 0; i <= 100000 - k; i++)
		{
			int j;
			int x = 0;
			/*index i���� pattern ���ڿ��� Ȯ���� ���ݴϴ�.*/
			for (j = 0; j < k; j++)
			{
				if (ref_[i + j] != short_read1[j])
					x++;
				if (x > 2)//missmatch
					break;
			}
			if (j == k)
			{
				for (int a = 0; a < k; a++)
				{
					new_my[i + a] = short_read1[a];
				}
			}
		}
		g++;
		delete[] short_read1;
	}
	short_file.close();
	ofstream my_file(newname);
	my_file << new_my << endl;
}

float err_rate(string my, string new_my)
{
	float err = 0.0f;
	float rate;
	char * DNA = new char[100001];
	char * new_DNA = new char[100001];
	char * DNA_ = new char[100001];
	char * new_DNA_ = new char[100001];

	ifstream myDNA(my);
	myDNA.getline(DNA, 100001);
	myDNA.close();
	DNA_ = DNA;

	ifstream new_MD(new_my);
	new_MD.getline(new_DNA, 100001);
	new_MD.close();
	new_DNA_ = new_DNA;

	for (int i = 0; i < 100000; i++)
	{
		if(DNA_[i] != new_DNA_[i])
			err++;
	}
	rate = (float)((err / 100000)*100);
	return rate;
}

int main()
{
	char *ref = new char[100001];

	string ref_name = "ref.txt";
	string my_name = "my.txt";
	string short_name = "short.txt";
	string new_name = "newmy.txt";
	string new_name_2 = "newmy2.txt";

	clock_t start, end;
	
	
	//make_ref(ref, ref_name);
	//make_myDNA(ref_name, my_name, 50);
	shortread(my_name, short_name, 50, 200000);
	cout << "x" << endl;
	start = clock();
	sequence(short_name, new_name, ref_name,50, 200000);
	cout << "������ : " << err_rate(my_name, new_name) << "%" << endl;
	end = clock();
	cout << "���� �ð� : " << ((end - start) / CLOCKS_PER_SEC)<<endl;

	
	start = clock();
	sequence_Brute(short_name, new_name_2, ref_name, 50, 200000);
	cout << "������ : " << err_rate(my_name, new_name_2) << "%" << endl;
	end = clock();
	cout << "���� �ð� : " << ((end - start) / CLOCKS_PER_SEC) << endl;

	return 0;
}