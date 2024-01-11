#include <iostream>
#include <vector>

using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int data) : data(data), next(nullptr) {}
};

class LinkedList {
public:
    Node* head;
    Node* tail;
    int size;
    const int MAX_SIZE;

    LinkedList() : head(nullptr), tail(nullptr), size(0), MAX_SIZE(5) {}

    void append(int data) {
        if (size == 0) {
            head = new Node(data);
            tail = head;
        } else {
            Node* newNode = new Node(data);
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    int pop() {
        if (size == 0) {
            cout << "Queue is empty." << endl;
            return -1; // Or throw an exception
        }

        int poppedData = head->data;
        Node* temp = head;
        head = head->next;
        delete temp;
        size--;
        return poppedData;
    }

    void display() const {
        Node* current = head;
        // cout << "Linked List: ";
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

class Queue {
private:
    vector<LinkedList> lists;

public:
    Queue() {
        lists.push_back(LinkedList());
    }

    void push(int data) {
        if (lists.back().size == lists.back().MAX_SIZE) {
            lists.push_back(LinkedList());
        }
        lists.back().append(data);
        balanceLists();
    }

    int pop() {
        if (lists.empty()) {
            cout << "Queue is empty." << endl;
            return -1; // Or throw an exception
        }

        int poppedData = lists[0].pop();
        balanceLists();
        return poppedData;
    }

    void balanceLists() {
        for (size_t i = 0; i < lists.size() - 1; ++i) {
            if (lists[i].size < lists[i].MAX_SIZE && lists[i + 1].size > 0) {
                int transferValue = lists[i + 1].pop();
                lists[i].append(transferValue);
            }
        }
        // Clean up any empty lists at the end
        while (!lists.empty() && lists.back().size == 0) {
            lists.pop_back();
        }
    }

    void display() const {
        if (lists.empty()) {
            cout << "Queue is empty." << endl;
        } else {
            cout << "Displaying Queue content:" << endl;
            for (const auto& ll : lists) {
                ll.display();
            }
        }
    }
};

int main() {
    Queue q;

    char choice;
    int input;

    do {
        cout << "Enter 'p' to push, 'o' to pop, 'd' to display, or 'q' to quit: ";
        cin >> choice;

        switch (choice) {
            case 'p':
                cout << "Enter value to push: ";
                cin >> input;
                q.push(input);
                break;

            case 'o':
                cout << "Popped: " << q.pop() << endl;
                break;

            case 'd':
                q.display();
                break;

            case 'q':
                cout << "Quitting..." << endl;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 'q');

    return 0;
}
