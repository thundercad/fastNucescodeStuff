//q1+q2
//#include<iostream>

//using namespace std;

//template<class T>

//class SortedSet

//{

//	struct node {

//		node* next;

//		T data;

//	};

//	node* head;

//	node* tail;

//public:

//	SortedSet() :head(nullptr), tail(nullptr) {};//constructor

//	void insert(T const key)

//	{

//		node* n = new node();

//		if (n != nullptr)

//		{

//			n->data = key;

//			if (head == nullptr)

//			{

//				head = n;

//				tail = n;

//			}

//			else if (head->data > key)

//			{

//				n->next = head;

//				head = n;

//			}

//			else if (key > tail->data)

//			{

//				tail->next = n;

//				tail = n;

//			}

//			else

//			{

//				node* curr = head;

//				node* prev = nullptr;

//				while (curr != nullptr && curr->data < key)

//				{

//					prev = curr;

//					curr = curr->next;

//				}

//

//				if (curr != nullptr && curr->data == key)

//				{

//					delete n;

//					return;

//				}

//

//				n->next = curr;

//				if (prev != nullptr)

//				{

//					prev->next = n;

//				}

//				else

//				{

//					head = n;

//				}

//				if (curr == nullptr)

//					tail = n;

//			}

//		}

//	}

//	void deleteNode(int const index)//assuming that 1st element is at first index and so on

//	{

//		int valid = 0;

//		node* check = head;

//		while (check != nullptr)

//		{

//			++valid;

//			check = check->next;

//		}//checking for range of valid indexes

//

//		if (index > 0 and index<=valid)

//		{

//			if (head == nullptr)

//				cout << "list is empty";

//			else if (index == 1)

//			{

//				head = head->next;

//			}

//			else

//			{

//				node* track = head;

//				int tr = 0;

//				while (tr < index - 2)

//				{

//					track = track->next;

//					++tr;

//				}

//				node* del = track->next;

//				track->next = track->next->next;

//				delete del;

//				if (index == valid)

//				{

//					tail = track;

//				}

//			}

//		}

//		else

//		{

//			cout << "invalid index"<<endl;

//		}

//

//	}

//	void unionset(SortedSet<T> const& otherSet)

//	{

//		if (this->head != otherSet.head)

//		{

//			node* curr1 = head;

//			node* curr2 = otherSet.head;

//			node* tracker = nullptr;

//			head = nullptr;

//			tail = nullptr;

//			while (curr1 != nullptr && curr2 != nullptr)

//			{

//				if (curr1->data == curr2->data)

//				{

//					if (head == nullptr)

//					{

//						head = curr1;

//						tail = curr1;

//						tracker = curr1;

//					}

//					else

//					{

//						tracker->next = curr1;

//						tracker = curr1;

//					}

//

//					curr1 = curr1->next;

//					curr2 = curr2->next;

//

//				}

//				else if (curr1->data < curr2->data)

//				{

//					if (head == nullptr)

//					{

//						head = curr1;

//						tail = curr1;

//						tracker = curr1;

//					}

//					else

//					{

//						tracker->next = curr1;

//						tracker = curr1;

//					}

//					curr1 = curr1->next;

//				}

//				else

//				{

//					if (head == nullptr)

//					{

//						head = curr2;

//						tail = curr2;

//						tracker = curr2;

//					}

//					else

//					{

//						tracker->next = curr2;

//						tracker = curr2;

//					}

//					curr2 = curr2->next;

//				}

//			}

//			if (curr1 != nullptr)

//			{

//				tracker->next = curr1;

//				tail = otherSet.tail;

//			}

//			else if (curr2 != nullptr)

//			{

//				tracker->next = curr2;

//				tail = otherSet.tail;

//			}

//		}

//		else

//			return;

//	}

//	void print()

//	{

//		if (head == nullptr)

//			cout << "the list is empty";

//		else

//		{

//			node* trav = head;

//			while (trav != nullptr)

//			{

//				cout << trav->data;

//				if (trav->next != nullptr)

//					cout << "->";

//				trav = trav->next;

//			}

//		}

//	}

//	void rotate(int k = 0)

//	{

//		if (k < 0)

//			cout << "error";

//

//		else

//		{

//			int i = 0;

//			while (i < k)

//			{

//				node* temp = head;

//				head = head->next;

//				tail->next = temp;

//				tail = temp;

//				tail->next = nullptr;

//				++i;

//			}

//		}

//

//	}     //q2

//};

//int main()

//{

//	SortedSet<int>s1;

//	s1.insert(10);

//	s1.insert(20);

//	s1.insert(30);

//	s1.insert(3);

//	s1.insert(69);

//	s1.insert(60);

//	s1.insert(10);

//	s1.insert(20);

//	s1.insert(30);

//	s1.print();

//	cout << endl;

//

//	SortedSet<int>s2;

//	s2.insert(10);

//	s2.insert(20);

//	s2.insert(30);

//	s2.insert(40);

//	s2.insert(50);

//	s2.insert(5);

//	s2.insert(16);

//	s2.insert(60);

//	s2.insert(69);

//

//	s1.unionset(s2);

//

//	cout <<endl;

//

//	s1.print();

//

//	cout <<endl;

//

//

//	return 0;

//}

// 

// 

// 



//question 3

#include<iostream>

using namespace std;

template<class T>

struct node {

		node* next;

		T data;

	};

template<class T>

class SortedSet

{

	node<T>* head;

	node<T>*tail;

public:

	SortedSet() :head(nullptr), tail(nullptr) {};//constructor

	void insert(T const key)

	{

		node<T>* n = new node<T>();

		if (n != nullptr)

		{

			n->data = key;

			if (head == nullptr)

			{

				head = n;

				tail = n;

			}

			else if (head->data > key)

			{

				n->next = head;

				head = n;

			}

			else if (key > tail->data)

			{

				tail->next = n;

				tail = n;

			}

			else

			{

				node<T>* curr = head;

				node<T>* prev = nullptr;

				while (curr != nullptr && curr->data < key)

				{

					prev = curr;

					curr = curr->next;

				}



				if (curr != nullptr && curr->data == key)

				{

					delete n;

					return;

				}



				n->next = curr;

				if (prev != nullptr)

				{

					prev->next = n;

				}

				else

				{

					head = n;

				}

			}

		}

	}



	void deleteNode(int const index)//assuming that 1st element is at first index and so on

	{

		if (head == nullptr)

			cout << "list is empty";

		else if (head->next == nullptr)

		{

			tail = nullptr;

			head = nullptr;

		}

		else

		{

			node<T>*track = head;

			int tr = 0;

			while (tr < index - 2)

			{

				track = track->next;

				++tr;

			}

			node<T>*del = track->next;

			track->next = track->next->next;

			delete del;

		}



	}

	void print()

	{

		if (head == nullptr)

			cout << "the list is empty";

		else

		{

			node<T>*trav = head;

			while (trav != nullptr)

			{

				cout << trav->data;

				if (trav->next != nullptr)

					cout << "->";

				trav = trav->next;

			}

		}

	}

	node<T>* gethead()

	{

		return head;

	}

	node<T>* gettail()

	{

		return tail;

	}

	void setHead(node<T>* newHead) {

		head = newHead;

	}

	void setTail(node<T>* newTail) {

		tail = newTail;

	}

};

template<class T>

void reverse(SortedSet<T>& obj)

{

	if (obj.gethead() == nullptr)

		return;



	node<T>* prev = nullptr;

	node<T>* curr = obj.gethead();

	node<T>* next = nullptr;



	while (curr != nullptr)

	{

		next = curr->next;

		curr->next = prev;

		prev = curr;

		curr = next;

	}



	obj.setHead(prev);

	obj.setTail(obj.gethead());

}



int main()

{

	SortedSet<int>s1;

	s1.insert(1);

	s1.insert(2);

	s1.insert(5);

	s1.insert(2);

	s1.insert(1);

	s1.insert(2);

	s1.insert(5);

	s1.insert(7);

	reverse(s1);

	s1.print();

	

	return 0;

}



