#include<iostream>
#include<vector>
#include<queue>
using namespace std;
template <class k, class v>
class SpecialBST
{
public:
	struct BSTNode
	{
		BSTNode* left;
		BSTNode* right;
		k key;
		v value;
	};
	BSTNode* root;
private:

	void printHelper(BSTNode* root)
	{

		if (root == NULL)
			return;
		queue<BSTNode*> q;

		q.push(root);

		while (q.empty() == false) {

			BSTNode* node = q.front();
			cout << node->value << " ";
			q.pop();

			if (node->left != NULL)
				q.push(node->left);

			if (node->right != NULL)
				q.push(node->right);
		}
	}
	BSTNode* getNewNode(k key, v value)
	{
		BSTNode* newNode = new BSTNode();
		newNode->value = value;
		newNode->key = key;
		newNode->left = newNode->right = nullptr;
		return newNode;
	}
	void getValuesInOrderHelper(BSTNode* root, vector<v>& result)
	{
		if (root != nullptr)
		{
			getValuesInOrderHelper(root->left, result);
			result.push_back(root->value);
			getValuesInOrderHelper(root->right, result);
		}
	}
	void levelTraversalHelper(BSTNode* root, vector<v>& result)
	{
		if (root == NULL)
			return;

		queue<BSTNode*>q;
		q.push(root);

		while (q.empty() == false)
		{

			BSTNode* node = q.front();
			result.push_back(node->value);
			q.pop();

			if (node->left != NULL)
				q.push(node->left);

			if (node->right != NULL)
				q.push(node->right);
		}
	}
	BSTNode* insertHelper(BSTNode*& root, k key, v value)
	{
		if (root == nullptr)
		{
			BSTNode* newNode = getNewNode(key, value);
			root = newNode;
		}
		else if (root->key > key)
		{
			root->left = insertHelper(root->left, key, value);
		}
		else
		{
			root->right = insertHelper(root->right, key, value);
		}

		return root;

	}
	BSTNode* updateTree(BSTNode* root, int key) {
		if (root == nullptr)
			return root;
		if (root->key == key) {
			return root;
		}

		if (root->left != nullptr && root->left->key == key) {
			BSTNode* pivot = root;
			root = root->left;
			BSTNode* connect = root->right;
			root->right = pivot;
			pivot->left = connect;
			return root;
		}

		if (root->right != nullptr && root->right->key == key) {
			BSTNode* pivot = root;
			root = root->right;
			BSTNode* connect = root->left;
			root->left = pivot;
			pivot->right = connect;
			return root;
		}

		if (root->key > key) {
			root->left = updateTree(root->left, key);
			if (root->left != nullptr && root->left->key == key) {
				BSTNode* pivot = root;
				root = root->left;
				BSTNode* connect = root->right;
				root->right = pivot;
				pivot->left = connect;
			}
		}
		else if (root->key < key) {
			root->right = updateTree(root->right, key);
			if (root->right != nullptr && root->right->key == key)
			{
				BSTNode* pivot = root;
				root = root->right;
				BSTNode* connect = root->left;
				root->left = pivot;
				pivot->right = connect;
			}
		}

		return root;
	}
	k deletHelper(BSTNode* root, k key)
	{
		if (root->key == key)
			return root->key;
		else if ((root->left != nullptr && root->left->key == key) || (root->right != nullptr && root->right->key == key)) 
		{
			return root->key;  // Return the key of the parent node
		}

		if (key < root->key) {
			return deletHelper(root->left, key);
		}
		else {
			return deletHelper(root->right, key);
		}
	}

	k searchHelper(BSTNode*& root, k key)
	{
		if (root == nullptr)
		{
			return k();
		}
		if (root->key == key)
		{
			return root->key;
		}
		if (root->left == nullptr && root->right == nullptr)
		{
			return root->key;
		}
		else if (root->key > key)
		{
			searchHelper(root->left, key);
		}
		else
		{
			searchHelper(root->right, key);
		}

	}
public:

	SpecialBST()
	{
		root = nullptr;
	}
	void print()
	{
		printHelper(root);
	}
	vector<v>* getValuesInOrder()
	{
		vector<v>* result = new vector<v>();
		getValuesInOrderHelper(root, *result);
		return result;
	}
	vector<v>* levelTraversal()
	{
		vector<v>* result = new vector<v>();
		levelTraversalHelper(root, *result);
		return result;
	}
	BSTNode* minValueNode(BSTNode* node) {
		// Find the leftmost node in the tree (smallest node)
		while (node->left != nullptr) {
			node = node->left;
		}
		return node;
	}
	bool insertNode(k key, v value)
	{
		if (root != nullptr)
		{
			k check = searchHelper(root, key);
			if (check == key)
			{
				root = updateTree(root, check);
				return 0;
			}
			else
			{
				root = insertHelper(root, key, value);
				root = updateTree(root, key);
				return 1;
			}
		}
		else
		{
			root = insertHelper(root, key, value);
			root = updateTree(root, key);
			return 1;
		}

	}
	void searchNode(k key)
	{
		k check = searchHelper(root, key);
		if (check != key)
		{
			cout << "The member not found";
		}
		root = updateTree(root, check);
	}
	bool deleteNode(k key)
	{
		k check = searchHelper(root, key);
		if (check == key)
		{
			check = deletHelper(root, key);
			root = updateTree(root, check);
			if (root->key == key )
			{
				if (root->left == nullptr)
				{
					BSTNode* temp = root;
					root = root->right;
					delete temp;
				}
				else if (root->right == nullptr)
				{
					BSTNode* temp = root;
					root = root->left;
					delete temp;
				}
				else
				{
					BSTNode* temp = root;//tracking minimum 
					BSTNode* t = root->right;
					while (t->left != nullptr)
					{
						temp = t;
						t = t->left;
					}
					if (temp != root)
						temp->left = t->right;
					else
						temp->right = t->right;

					{
						root->key = t->key;
						root->value = t->value;
					}
					delete t;
				}

			}
			else if (root->right!=nullptr && key == root->right->key)
			{
				BSTNode* temp = root->right;
				root->right = root->right->right;
				temp = nullptr;
				delete temp;
			}
			else
			{
				BSTNode* temp = root->left;
				root->left = root->left->left;
				temp = nullptr;
				delete temp;
			}
			return 1;
		}
		else
		{
			cout << "the node doest exist";
			root = updateTree(root, check);
			return 0;
		}

	}

};
struct student;
class studentList :public SpecialBST<int, student*>
{
	public:
	struct student
	{
		int rollNum;
		int batch;
		float cgpa;
		string firstName;
		string lastName;
		string department;
		student(int rollNum = -1, int batch = -1, float cgpa = -1, string firstName = " ", string lastName = " ", string department = "")
		{
			this->rollNum = rollNum;
			this->batch = batch;
			this->cgpa = cgpa;
			this->firstName = firstName;
			this->lastName = lastName;
			this->department = department;
		}

		student& operator=(const student& other)
		{
			if (this != &other) // Self-assignment check
			{
				rollNum = other.rollNum;
				batch = other.batch;
				cgpa = other.cgpa;
				firstName = other.firstName;
				lastName = other.lastName;
				department = other.department;
			}
			return *this;
		}
	};
	SpecialBST<int, student*>* tree;


public:

	studentList()
	{
		tree = new SpecialBST<int, student*>();
	}

	bool insertNewStudent(float rollNum = -1, float batch = -1, float cgpa = -1, string firstName = " ", string lastName = " ", string department = "")
	{
		student* newStudent = new student(rollNum, batch, cgpa, firstName, lastName, department);
		bool found= tree->insertNode(rollNum, newStudent);
		tree->insertNode(rollNum, newStudent);
		if (!found)
		{
			cout << "The rollnumber already exists \n";
			return 0;
		}
		return 1;

	}

	bool deleteStudent(int key)
	{
		return tree->deleteNode(key);
	}

	void printAllStudents()
	{
		if (tree->root == nullptr)
		{
			cout << "there is no record of students";
		}
		else
		{
			vector<student*>list = *tree->getValuesInOrder();
			for (student* s : list)
			{
				cout << "Roll Number: " << s->rollNum << "\n";
				cout << "Batch: " << s->batch << "\n";
				cout << "CGPA: " << s->cgpa << "\n";
				cout << "Department: " << s->department << "\n";
				cout << "First Name: " << s->firstName << "\n";
				cout << "Last Name: " << s->lastName << "\n";
				cout << "------------------------\n";
			}
		}
	}

	void searchstudent(int key)
	{
		tree->searchNode(key);
		 if (tree->root!=nullptr && tree->root->key == key)//in case found
		{
			cout << tree->root->value->rollNum<<"\n";
			cout << tree->root->value->firstName << "\n";
			cout << tree->root->value->lastName << "\n";
			cout << tree->root->value->cgpa << "\n";
			cout << tree->root->value->batch << "\n";
			cout << tree->root->value->department << "\n";
		}
		else
		{
			cout<<"NO";
		}
	}
	bool updateStudent(float oldRollNumber, float newRollNumber, string newFirstName, string newLastName, int newBatch, string newDepartment, float newCgpa)
	{
		tree->searchNode(oldRollNumber);
		if (tree->root != nullptr && tree->root->key == oldRollNumber)
		{
			tree->deleteNode(oldRollNumber);
			student* updatedStudent = new student(newRollNumber, newBatch, newCgpa, newFirstName, newLastName, newDepartment);//creating a new student;
			bool inserted = tree->insertNode(newRollNumber, updatedStudent);//checking if insertion is done 
			if (!inserted)
			{
				cout << "Error inserting the updated student into the tree." << endl;
				return false;
			}

			return true;
		}
		else//incase the student doest exits at all
		{
			cout << "doesnt exist" << endl;
			return false;
		}
	}

};
void menue(studentList*& LIST )
{
	LIST = new studentList();
	char option='a';
	float num=-1;

	string fn="null";
	string ln = "null";
	string dep = "null";
	float cgpa = 0;
	int batch = 0;
	char string;
	while (option != 'E')
	{
		cout << "Press I to insert a new student\n";
		cout << "Press D to delete a student.\n";
		cout << "Press S to search a student by roll number.\n";
		cout << "Press U to update the data of a student.\n";
		cout << "Press P to print all students sorted by roll number.\n";
		cout << "Press E to exit.\n";
		cin >> option;
		if (option == 'I')
		{
			cout << "Please enter new data of student in this order: Roll Number, First Name, Last Name, Batch, Department, CGPA\n";	
			cin >> num >> fn >> ln >> batch >> dep >> cgpa;
			LIST->insertNewStudent(num,batch,cgpa,fn,ln,dep);
		}
		else if (option=='D')
		{
			cin >> num;
			LIST->deleteStudent(num);
		}
		else if (option == 'P')
		{
			LIST->printAllStudents();
		}
		else if(option == 'U')
		{ 
			float old = 0;
			cout << "enter old rollnumber\n";
			cin >> old;
			cout << "enter new details";
			cin >> num >> fn >> ln >> batch >> dep >> cgpa;
			LIST->updateStudent(old, num, fn, ln, batch, dep, cgpa);
		}
		else if (option == 'S')
		{
			cout << "enter rollnumber";
			cin >> num;
			LIST->searchstudent(num);
		}
	}

}
int main()
{
	studentList* s1 = new studentList();
	menue(s1);
}
