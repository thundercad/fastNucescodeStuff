#include<iostream>
using namespace std;
template <class T>
class Que
{
   struct Node {
       T data;
       Node* next;
       Node(T d = T()) :data(d), next(NULL) {};
   };
   Node* front;
   Node* rear;
   int maxSize;
   int size;
public:
   Que(int d = 100) :front(NULL), rear(NULL), size(0), maxSize(d) {};
   int getsize()
   {
       return size;
   }
   T getFront()
   {
       return front->data;
   }
   void enQue(T data)
   {
       if (size != maxSize)
       {
           Node* newNode = new Node(data);
           if (front == NULL)
           {
               front = newNode;
               rear = newNode;
           }
           else
           {
               rear->next = newNode;
               rear = newNode;
           }
           ++size;
       }

       else
       {
           cout << "The que is full";
       }

   }

   void deQue()
   {
       if (size == 0)
           cout << "the que is empty";
       else
       {
           Node* del = front;
           front = front->next;
           delete del;
           --size;
       }
   }

   bool isEmpty()
   {
       if (size == 0)
           return true;

       return false;
   }

   void clear()
   {
       while (!isEmpty())
       {
           deQue();
       }
   }

   T peek(int index = 0)
   {
       Node* track = front;
       int t = 0;
       while (t < index)
       {
           track = track->next;
           t++;
       }
       return track->data;
       track = NULL;
   }


   void print()
   {
       if (isEmpty())
       {
           cout << "The queue is empty" << endl;
           return;
       }

       Que<T> tempQueue(maxSize);
       while (!isEmpty())
       {
           T element = getFront();
           cout << element << " ";
           deQue();
           tempQueue.enQue(element);
       }
       while (!tempQueue.isEmpty())
       {
           T element = tempQueue.getFront();
           enQue(element);
           tempQueue.deQue();
       }
   }



};

void radixsortIntegers(Que<int>& input, int n, int k)
{
   Que<int>* queKeys = new Que<int>[10];
   int divisor =1;
   for (int i = 0;i < k ;i++)
   {
       while (!input.isEmpty())
       {
           int num = input.getFront();
           input.deQue();
           queKeys[(num / divisor) % 10].enQue(num);
       }

       for (int j = 0;j < 10;j++)
       {
           if (!queKeys[j].isEmpty())
           {
               while (!queKeys[j].isEmpty())
               {
                   input.enQue(queKeys[j].getFront());
                   queKeys[j].deQue();
               }
           }
       }
       divisor = divisor * 10;
   }


}

void radixSortString(Que<string>& input, int n, int k) {
   Que<string>* queKeys = new Que<string>[128];

   for (int i = k - 1; i >= 0; i--) {
       while (!input.isEmpty()) {
           string currFront = input.getFront();

           if (currFront.length() > i) {
               int index = currFront[i] - 'O';
               queKeys[index].enQue(currFront);
           }
           else {
               queKeys[127].enQue(currFront);
           }
           input.deQue();
       }

       for (int z = 0; z < 128; z++) {
           while (!queKeys[z].isEmpty()) {
               input.enQue(queKeys[z].getFront());
               queKeys[z].deQue();
           }
       }
   }
   delete[] queKeys;

   Que<string>* queKeysLen = new Que<string>[k];
   while(!input.isEmpty())
   {
       int len = input.getFront().length();
       string key = input.getFront();
       input.deQue();
       queKeysLen[len-1].enQue(key);
   }


   for (int i = 0; i < k; i++) {
       while (!queKeysLen[i].isEmpty()) {
           input.enQue(queKeysLen[i].getFront());
           queKeysLen[i].deQue();
       }
   }

   delete[]queKeysLen;
}


int main()
{

   /*Que<string>myQue;
   int k = 0, n;
   cout << "enter digits number:\n";
   cin >> k;
   cout << "enter the value of n:\n";
   cin >> n;
   cout << "enter elemnts of max " << k << "digits:\n";
   string element;
   for (int i = 0;i < n;i++)
   {
       cin >> element;
       myQue.enQue(element);
   }

   cout << "\n" << "original que:";
   myQue.print();
   cout << endl;

   radixSortString(myQue, n, k);
   cout << "\n" << "sorted que:";
   myQue.print();*/

   //integer sort
  Que<int> myque;
   int k = 0, n;
   cout << "enter digits number:\n";
   cin >> k;
   cout << "enter the value of n:\n";
   cin >> n;
   cout << "enter elemnts of max " << k << "digits:\n";
   int element;
   for (int i = 0;i < n;i++)
   {
       cin >> element;
       myque.enQue(element);
   }

   cout << "\n" << "original que:";
   myque.print();
   cout << endl;

   radixsortIntegers(myque, n, k);
   cout << "\n" << "sorted que:";
   myque.print();


}