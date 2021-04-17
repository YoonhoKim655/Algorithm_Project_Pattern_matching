//2016112166 김윤호

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
};//Node의 struct

// Red-Black Tree의 Class
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
	//비어 있는  tree일 때, 새로 넣는 node를 root값으로 설정을 했습니다.

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
	/*tree가 비어있지 않을 경우, 새로 넣는 값을 재귀 형식으로 각 node의 값과
	비교를 해서 자리를 찾고 적절한 자리에 값을 넣었습니다.*/
	else

	return root;
}

int BSTsearch(Node* p, int n)
{
	int result;   // Result returned

	if (p == 0)
		result = 0;//tree가 비었을 경우 0을 return해주었습니다.
	else if (n < p->data)
		result = BSTsearch(p->left, n);//searchkey가 element보다 작으면 left값과 비교를 해주는 코드 입니다.
	else if (n > p->data)
		result = BSTsearch(p->right, n);//searchkey가 element보다 크면 right값과 비교를 해주는 코드 입니다.
	else
	{
		n = p->data;
		result = 1;
	}//searchkey가 element와 같으면 1을 return 해주는 코드입니다.

	return result;
}

void RBTree::rotateLeft(Node *&root, Node *&pt)
{
	Node *pt_right = pt->right;

	pt->right = pt_right->left;
	/*기존에 중심이었던 node의 오른쪽 자식이 중심이 되어야 하므로
	오른쪽 자식의 왼쪽 자식을 기존 중심 node의 오른쪽 자식으로 바꿨습니다.*/
	if (pt->right != NULL)
		pt->right->parent = pt;

	pt_right->parent = pt->parent;
	/*오른쪽 자식이 중심이 되기 위해서
	조부모노드의 자식 노드로 바꿨습니다.*/
	if (pt->parent == NULL)
		root = pt_right;//기존의 node가 root 였을 경우

	else if (pt == pt->parent->left)
		pt->parent->left = pt_right;

	else
		pt->parent->right = pt_right;
	/*위에 두 상황은 왼쪽 자식인지 오른쪽 자식인지를
	결정을 하는 부분입니다.*/
	pt_right->left = pt;
	pt->parent = pt_right;
	/*기존 중심노드와 새로운 중심을 서로 연결을 했습니다.*/
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
}/*right-rotation은 왼쪽과 반대로 만들었습니다.*/

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
			부모 node가 조부모 node의 왼쪽 자식일 경우 */
		if (parent_pt == grand_parent_pt->left)
		{
			Node *uncle_pt = grand_parent_pt->right;

			/* Case : 1
			   부모와 삼촌 node의 색이
			   모두 빨간색일 경우*/
			if (uncle_pt != NULL && uncle_pt->color == RED)
			{
				grand_parent_pt->color = RED;
				parent_pt->color = BLACK;
				uncle_pt->color = BLACK;
				pt = grand_parent_pt;
			}
			/*case 1의 해결 방식에 따라서 조부모의 색을 black으로
			부모와 삼촌 node의 색을 red로 바꾸었습니다.*/
			else
			{
				/* Case : 2
				   case 1이 아니고 삽입된 node의 위치가
				   부모 node의 오른쪽 자식일 경우*/
				if (pt == parent_pt->right)
				{
					rotateLeft(root, parent_pt);
					pt = parent_pt;
					parent_pt = pt->parent;
				}
				/*case 2에 따라서 삽입된 node의 부모 node를
				기준으로 left-rotation을 했습니다.*/

				/* Case : 3
				   case 1이 아니고 삽입된 node의 위치가
				   부모 node의 왼쪽 자식일 경우 */
				rotateRight(root, grand_parent_pt);
				swap(parent_pt->color, grand_parent_pt->color);
				pt = parent_pt;
				/*이 경우는 left-rotation을 하고서
				right-rotation을 한 번 해주니다*/
			}
		}

		/* Case : B
		 부모 node가 조부모 node의 오른쪽 자식일 경우
		 세부 case들은 위와 같다.*/
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
	//data의 값을 key로 가지는 새로운 node를 생성을 합니다.

	root = BSTInsert(root, pt);
	//새로운 node를 삽입을 합니다.

	fixup(root, pt);
	//새로 삽입된 node를 red-black tree의 특성에 맞게 fix를 해줍니다.
}

int RBTree::search(int n)
{
	int result = BSTsearch(root, n);

	return result;//찾는 값이 없을 경우, 0을 return을 했습니다.
}

void make_ref(char * ref, string F_name)//make_ref(string F_name)/*string F_name*/
{

	random_device rd;//seed 값을 얻기 위한 random_device 생성
	mt19937 gen(rd());//random_device를 통해 난수 생성 엔진을 초기화 
	uniform_int_distribution<int> dis(0, 3);//0~3의 값을 랜덤으로 생성을 하는 균등 분포 정의
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
		}/*switch문을 사용을 해서 생성되는 random값에 따라서 reference DNA sequence를 생성*/
	}
	ref[250000] = '\0';
	cout << "a : " << a << " b : " << b << " c : " << c << " d : " << d << " 합 : " << (a + b + c + d) << endl;

	ofstream ref_file(F_name);
	ref_file << ref << endl;
	ref_file.close();//file을 저장
	delete[] ref;
}

void make_myDNA(string ref_file, string my_DNA, int k)
{
	char *my = new char[250001];
	char *my1 = new char[250001];
	ifstream refer(ref_file);
	refer.getline(my1, 250001);
	refer.close();// 생성한 reference DNA를 가지고 옮

	int a = (2 * (250000 / k));	//x%

	my = my1;
	random_device rd;//seed 값을 얻기 위한 random_device 생성
	mt19937 gen(rd());//random_device를 통해 난수 생성 엔진을 초기화 
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
	/*랜덤한 값을 입력을 받아서 reference DNA의 위치를 결정을 하고 그 위치의 값에 따라서 다시 random값을 입력을 받아서 값에 따라서 새로 입력을 
	받는 값이 정해지는 방식으로 myDNA를 새로 만들었습니다.*/
	my[250000] = '\0';

	ofstream my_file(my_DNA);
	my_file << my << endl;
	my_file.close();
	cout << "mydna" << endl;
}

void shortread(string my_name, string short_name, int k, int n)
{
	random_device rd;//seed 값을 얻기 위한 random_device 생성
	mt19937 gen(rd());//random_device를 통해 난수 생성 엔진을 초기화 
	uniform_int_distribution<int> dis(0, 100000 - k);

	char my[100001];

	ifstream refer(my_name);
	refer.getline(my, 100001);//myDNA를 문자열에 저장
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
	}//랜덤한 값을 입력을 받고서 그 값을 시작점으로 정해서 주어진 길이만큼의 shortread를 만들었습니다.
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
}//나쁜 문자열을 찾았을 경우 이동거리를 결정해주는 것을 위한 table입니다.

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
			if (j < 2)//2는 mismatch 수
			{
				if (tree.search(s) == 1)// 현재 발견한 index의 값이 tree에 존재할 때,
					s += (s + k < 100000) ? k - badchar[ref_[s + k]] : 1;	//새로운 값을 찾습니다.
				else
				{
					tree.insert(s);
					
					for (int a = 0; a < k; a++)
					{
						new_my[s + a] = short_read1[a];
					}
					break;
				}//tree에 해당 index값이 없으면 복원을 시작을 합니다.
			}
			else
				s += max(1, bad - badchar[ref_[s + bad]]);//없을 경우 다음 위치로 이동
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
			/*index i에서 pattern 문자열을 확인을 해줍니다.*/
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
	cout << "오차율 : " << err_rate(my_name, new_name) << "%" << endl;
	end = clock();
	cout << "수행 시간 : " << ((end - start) / CLOCKS_PER_SEC)<<endl;

	
	start = clock();
	sequence_Brute(short_name, new_name_2, ref_name, 50, 200000);
	cout << "오차율 : " << err_rate(my_name, new_name_2) << "%" << endl;
	end = clock();
	cout << "수행 시간 : " << ((end - start) / CLOCKS_PER_SEC) << endl;

	return 0;
}