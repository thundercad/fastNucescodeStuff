#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>
#include <string>
#include <thread>
#include <ctime> // Include the time library
using namespace std;
#define M_PI 3.14159265358979323846
using namespace std;

template<class T>
class Que
{
    struct Node {
        T data;
        Node* next;
        Node(T d = T()) : data(d), next(NULL) {};
    };
    Node* front;
    Node* rear;
    int maxSize;
    int size;
public:
    Que(int d = 100) : front(NULL), rear(NULL), size(0), maxSize(d) {};
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
            cout << "The queue is full";
        }
    }

    void deQue()
    {
        if (size == 0)
            cout << "The queue is empty";
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
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Josephus Problem - Soldier Elimination");

    sf::Texture texture;

    if (!texture.loadFromFile("goku.jpeg")) {
        cerr << "Failed to load image" <<endl;
        return 1;
    }

    int n, k;

    cout << "Enter the number of soldiers: ";
    cin >> n;

    cout << "Enter the soldiers to be skipped (k): ";
    cin >> k;

    vector<sf::Sprite> images(n);
    sf::Font font;

    if (!font.loadFromFile("LiberationSans-Regular.ttf")) {
        cerr << "Failed to load font" << endl;
        return 1;
    }

    for (int i = 0; i < n; i++) {
        images[i].setTexture(texture);
        sf::FloatRect bounds = images[i].getLocalBounds();
        images[i].setOrigin(bounds.width / 2, bounds.height / 2);
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    text.setPosition(350, 270);

    Que<int> soldiers;

    // Generate a random starting point
    srand(static_cast<unsigned>(time(0))); // Seed the random number generator
    int randomStart = rand() % n +1;
    cout << "Counting starts from random soldier " << randomStart << endl;

    // Initialize soldiers starting from the random point
    for (int i = randomStart; i <= n; i++) {
        soldiers.enQue(i);
    }
    for (int i = 1; i < randomStart; i++) {
        soldiers.enQue(i);
    }

    // Create an array of sf::Text objects for soldier numbers
    vector<sf::Text> soldierNumbers(n);

    for (int i = 0; i < n; i++) {
        images[i].setTexture(texture);
        sf::FloatRect bounds = images[i].getLocalBounds();
        images[i].setOrigin(bounds.width / 2, bounds.height / 2);

        // Initialize the soldier number text
        soldierNumbers[i].setFont(font);
        soldierNumbers[i].setCharacterSize(16);  // Adjust the font size as needed
        soldierNumbers[i].setFillColor(sf::Color::White);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::E) {
                    if (soldiers.getsize() > 1) {
                        for (int j = 0; j < k-1; j++) {
                            int eliminated = soldiers.peek();
                            soldiers.deQue();
                            soldiers.enQue(eliminated);
                        }
                        int eliminated = soldiers.peek();
                        soldiers.deQue();
                        text.setString("Soldier " + std::to_string(eliminated) + " Died");

                        if (eliminated <= n) {
                            images[eliminated - 1].setScale(0.1f, 0.1f);  // Scale down the eliminated soldier
                            soldierNumbers[eliminated - 1].setString("");  // Erase the soldier number text
                        }
                    }
                }
            }
        }

        // Calculate and display soldier numbers
        window.clear(sf::Color::Black);
        float radius = 200.0f;
        float centerX = window.getSize().x / 2;
        float centerY = window.getSize().y / 2;
        float angle = 0.0f;
        float angleIncrement = 2 * M_PI / soldiers.getsize();

        for (int i = 0; i < soldiers.getsize(); i++) {
            int soldierNumber = soldiers.peek();
            soldiers.deQue();

            float x = centerX + radius * std::cos(angle);
            float y = centerY + radius * std::sin(angle);
            images[soldierNumber - 1].setPosition(x, y);
            soldiers.enQue(soldierNumber);
            soldierNumbers[soldierNumber - 1].setPosition(x, y);
            soldierNumbers[soldierNumber - 1].setString(std::to_string(soldierNumber));

            angle += angleIncrement;
        }

        window.draw(text);
        for (int i = 0; i < n; i++) {
            window.draw(images[i]);
            window.draw(soldierNumbers[i]);  // Draw the soldier number text
        }

        window.display();

        this_thread::sleep_for(std::chrono::seconds(1));

        if (soldiers.getsize() == 1) {
            text.setString("Soldier " + std::to_string(soldiers.peek()) + " survived");
            cout << "The remaining soldier: " << soldiers.peek() << endl;
            break;
        }
    }

    return 0;
}

