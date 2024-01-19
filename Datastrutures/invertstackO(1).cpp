#include <iostream>
using namespace std;
template<class T>
class FlipStack {
    T* array;
    int front;
    int rear;
    int size;
    bool inverted;

public:
    FlipStack(int size) : inverted(false), front(-1), rear(0), size(size) {
        array = new int[size];
    }

    ~FlipStack() {
        delete[] array;
    }
    void resize(int t)
    {
        T* newArr = new T[t];
       for (int i = 0; i <= top(); i++)
       {
       	newArr[i] = array[i];
       }
       delete[] array;
       array = newArr;
       size = t;
    }
    void insertFront(int key)
    {
        if (isFull()) {
            cout << "resized" << endl;
        }

        if (front == -1) {
            front = 0;
            rear = 0;
        }
        else if (front == 0)
            front = size - 1;
        else
            front = front - 1;

        array[front] = key;
    }
    void insertRear(int key)
    {
        if (isFull()) {
            cout << "resized" << endl;
        }

        if (front == -1) {
            front = 0;
            rear = 0;
        }
        else if (rear == size - 1)
            rear = 0;
        else
            rear = rear + 1;

        array[rear] = key;
    }
    void deleteFront()
    {
        if (isEmpty()) {
            cout << "array underflow" << endl;
            return;
        }

        if (front == rear) {
            front = -1;
            rear = -1;
        }
        else if (front == size - 1) {
            front = 0;
        }
        else {
            front = front + 1;
        }
    }
    void deleteRear()
    {
        if (isEmpty()) {
            cout << "stack empty" << endl;
            return;
        }

        if (front == rear) {
            front = -1;
            rear = -1;
        }
        else if (rear == 0) {
            rear = size - 1;
        }
        else {
            rear = rear - 1;
        }

    }
    int getFront()
    {
        if (isEmpty()) {
            cout << "stack empty" << endl;
            return -1;
        }
        return array[front];
    }
    int getRear()
    {
        if (isEmpty() || rear < 0) {
            cout << "stack empty" << endl;
            return -1;
        }
        return array[rear];

    }
    void push(int val)
    {
        if (!inverted) {
            insertFront(val);
        }
        else {
            insertRear(val);
        }
    }
    void pop()
    {
        if (!inverted) {
            deleteFront();
        }
        else {
            deleteRear();
        }

    }
    bool isFull()
    {
        if((front == 0 && rear == size - 1) || front == rear + 1)
        {
            this->resize(size * 2);
            return true;
        }
        return false;
    }
    bool isEmpty()
    {
        return front == -1;
    }
    void flipStack()
    {
        inverted = !inverted;
    }
    int top()
    {
        if (inverted) {
            return getRear();
        }
        return getFront();
    }
    void print()
    {
        FlipStack temp(size);
        while (!isEmpty()) {
            cout << top() << endl;
            temp.push(this->top());
            pop();
        }
        while (!temp.isEmpty()) {
            this->push(temp.top());
            temp.pop();
        }
    }
};


 
int main() {
    FlipStack<int> q1(8);
    q1.push(1);
    q1.push(2);
    q1.push(3);
    cout << "test case1: " << '\n';
    q1.print();
    cout << "\n";

    q1.flipStack();
    cout << "test case2: " << '\n';
    q1.print();
    cout << "\n";

    q1.push(50);
    cout << "test case3: " << '\n';
    q1.print();
    cout << "\n";

    q1.flipStack();
    cout << "test case4: " << '\n';
    q1.print();
    cout << "\n";

    q1.pop();
    q1.pop();
    q1.flipStack();
    q1.push(69);
    cout << "test case5: " << '\n';
    q1.print();
    cout << "\n";

    return 0;
}
