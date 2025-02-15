#include <iostream>
using namespace std;

template <class type>
class s_list; // Forward declaration of s_list.

template <class type>
class node {
    friend class s_list<type>;
    type data;
    node<type>* next;
public:
    node() {
        next = NULL;
    }
};

template <class type>
class s_list {
    node<type>* head;
    node<type>* getnode();
    node<type>* findnode() const;

public:
    s_list() {
        head = NULL;
    }
    ~s_list() {
        delete_all();
    }
    void display();
    void append(); // Add last node
    void add_start(); // Add first node
    void insert_after();
    void insert_before();
    void delet(); // Delete a specific node
    void delete_after();
    void delete_before();
    void delete_end(); // Delete last node
    void delete_start(); // Delete first node
    void delete_all();
    void delete_even();
    void delete_odd();
    void reverse();
    void sort();
    void del_all_oc();
};

template <class type>
void s_list<type>::display() {
    if (head == NULL) {
        cout << "\nList is empty.\n";
        return;
    }
    node<type>* ptr = head;
    cout << "\nLinked List is: ";
    while (ptr != NULL) {
        cout << ptr->data << " ";
        ptr = ptr->next;
    }
    cout << endl;
}

template <class type>
node<type>* s_list<type>::getnode() {
    node<type>* ptr = new node<type>;
    cout << "\nEnter data part of the node: ";
    cin >> ptr->data;
    return ptr;
}

template <class type>
node<type>* s_list<type>::findnode() const {
    if (head == NULL) {
        cout << "List is empty." << endl;
        return NULL;
    }
    node<type>* ptr = head;
    type val;
    cout << "\nEnter node value to be searched: ";
    cin >> val;
    while (ptr != NULL) {
        if (ptr->data == val)
            return ptr;
        ptr = ptr->next;
    }
    cout << "\nNode not found.\n";
    return NULL;
}

template <class type>
void s_list<type>::append() {
    node<type>* temp = getnode();
    if (head == NULL) {
        head = temp;
    } else {
        node<type>* ptr = head;
        while (ptr->next != NULL)
            ptr = ptr->next;
        ptr->next = temp;
    }
}

template <class type>
void s_list<type>::add_start() {
    node<type>* temp = getnode();
    temp->next = head;
    head = temp;
}

template <class type>
void s_list<type>::insert_after() {
    node<type>* curr = findnode();
    if (curr != NULL) {
        node<type>* ptr = getnode();
        ptr->next = curr->next;
        curr->next = ptr;
    }
}

template <class type>
void s_list<type>::insert_before() {
    node<type>* curr = findnode();
    if (curr != NULL && curr != head) {
        node<type>* temp = getnode();
        node<type>* prev = head;
        while (prev != NULL && prev->next != curr)
            prev = prev->next;
        if (prev != NULL) {
            temp->next = curr;
            prev->next = temp;
        }
    } else if (curr == head) {
        add_start();
    }
}

template <class type>
void s_list<type>::delet() {
    node<type>* curr = findnode();
    if (curr != NULL) {
        if (curr == head) {
            head = curr->next;
        } else {
            node<type>* prev = head;
            while (prev->next != curr)
                prev = prev->next;
            prev->next = curr->next;
        }
        delete curr;
    }
}

template <class type>
void s_list<type>::delete_start() {
    if (head == NULL) {
        cout << "List is empty.\n";
        return;
    }
    node<type>* temp = head;
    head = head->next;
    delete temp;
}

template <class type>
void s_list<type>::delete_end() {
    if (head == NULL) {
        cout << "List is empty.\n";
        return;
    }
    if (head->next == NULL) {
        delete head;
        head = NULL;
    } else {
        node<type>* temp = head;
        while (temp->next != NULL && temp->next->next != NULL)
            temp = temp->next;
        delete temp->next;
        temp->next = NULL;
    }
}

template <class type>
void s_list<type>::delete_all() {
    node<type>* ptr = head;
    while (ptr != NULL) {
        node<type>* temp = ptr;
        ptr = ptr->next;
        delete temp;
    }
    head = NULL;
}

template <class type>
void s_list<type>::reverse() {
    if (head == NULL || head->next == NULL)
        return;
    node<type>* prev = NULL;
    node<type>* curr = head;
    node<type>* next;
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
}

template <class type>
void s_list<type>::sort() {
    if (head == NULL || head->next == NULL)
        return;
    bool swapped;
    do {
        swapped = false;
        node<type>* curr = head;
        while (curr != NULL && curr->next != NULL) {
            if (curr->data > curr->next->data) {
                swap(curr->data, curr->next->data);
                swapped = true;
            }
            curr = curr->next;
        }
    } while (swapped);
}

template <class type>
void s_list<type>::del_all_oc() {
    if (head == NULL)
        return;
    type val;
    cout << "Enter value to delete all occurrences: ";
    cin >> val;
    bool found = false;
    node<type>* curr = head;
    node<type>* prev = NULL;
    while (curr != NULL) {
        if (curr->data == val) {
            found = true;
            if (curr == head) {
                head = curr->next;
            } else {
                prev->next = curr->next;
            }
            node<type>* temp = curr;
            curr = curr->next;
            delete temp;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
    if (!found)
        cout << "Value not found in the list.\n";
}

int main() {
    s_list<int> list;
    int choice;

    cout << "\nSINGLY LINKED LIST MENU:\n";
    cout << "1. Append\n";
    cout << "2. Add at Start\n";
    cout << "3. Display\n";
    cout << "4. Insert After\n";
    cout << "5. Insert Before\n";
    cout << "6. Delete Node\n";
    cout << "7. Delete Start\n";
    cout << "8. Delete End\n";
    cout << "9. Delete All\n";
    cout << "10. Reverse\n";
    cout << "11. Sort\n";
    cout << "12. Delete All Occurrences\n";
    cout << "13. Exit\n";
    do {
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            list.append();
            break;
        case 2:
            list.add_start();
            break;
        case 3:
            list.display();
            break;
        case 4:
            list.insert_after();
            break;
        case 5:
            list.insert_before();
            break;
        case 6:
            list.delet();
            break;
        case 7:
            list.delete_start();
            break;
        case 8:
            list.delete_end();
            break;
        case 9:
            list.delete_all();
            break;
        case 10:
            list.reverse();
            break;
        case 11:
            list.sort();
            break;
        case 12:
            list.del_all_oc();
            break;
        case 13:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 13);
    return 0;
}
