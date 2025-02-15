#include <iostream>
using namespace std;

template <class type>
class doubly_list; // Forward declaration of doubly_list.

template <class type>
class dnode {
    friend class doubly_list<type>;
    type data;
    dnode<type>* prev;
    dnode<type>* next;

public:
    dnode() {
        prev = next = NULL;
    }
};

template <class type>
class doubly_list {
    dnode<type>* head;

    dnode<type>* getnode();
    dnode<type>* findnode() const;

public:
    doubly_list() {
        head = NULL;
    }

    ~doubly_list() {
        delete_all();
    }

    void display();
    void append(); // Add at the end
    void add_start(); // Add at the start
    void insert_after();
    void insert_before();
    void delet(); // Delete a specific node
    void delete_start(); // Delete the first node
    void delete_end(); // Delete the last node
    void delete_all(); // Delete the entire list
    void reverse(); // Reverse the list
    void sort(); // Sort the list
    void del_all_oc(); // Delete all occurrences of a value
};

template <class type>
dnode<type>* doubly_list<type>::getnode() {
    dnode<type>* ptr = new dnode<type>;
    cout << "Enter data part of the node: ";
    cin >> ptr->data;
    return ptr;
}

template <class type>
dnode<type>* doubly_list<type>::findnode() const {
    if (head == NULL) {
        cout << "List is empty.\n";
        return NULL;
    }
    dnode<type>* ptr = head;
    type val;
    cout << "Enter node value to search: ";
    cin >> val;
    while (ptr != NULL) {
        if (ptr->data == val)
            return ptr;
        ptr = ptr->next;
    }
    cout << "Node not found.\n";
    return NULL;
}

template <class type>
void doubly_list<type>::display() {
    if (head == NULL) {
        cout << "List is empty.\n";
        return;
    }
    dnode<type>* ptr = head;
    cout << "Doubly Linked List: ";
    while (ptr != NULL) {
        cout << ptr->data << " ";
        ptr = ptr->next;
    }
    cout << endl;
}

template <class type>
void doubly_list<type>::append() {
    dnode<type>* temp = getnode();
    if (head == NULL) {
        head = temp;
    } else {
        dnode<type>* ptr = head;
        while (ptr->next != NULL)
            ptr = ptr->next;
        ptr->next = temp;
        temp->prev = ptr;
    }
}

template <class type>
void doubly_list<type>::add_start() {
    dnode<type>* temp = getnode();
    if (head == NULL) {
        head = temp;
    } else {
        temp->next = head;
        head->prev = temp;
        head = temp;
    }
}

template <class type>
void doubly_list<type>::insert_after() {
    dnode<type>* curr = findnode();
    if (curr != NULL) {
        dnode<type>* temp = getnode();
        temp->next = curr->next;
        temp->prev = curr;
        if (curr->next != NULL)
            curr->next->prev = temp;
        curr->next = temp;
    }
}

template <class type>
void doubly_list<type>::insert_before() {
    dnode<type>* curr = findnode();
    if (curr != NULL) {
        dnode<type>* temp = getnode();
        temp->prev = curr->prev;
        temp->next = curr;
        if (curr->prev != NULL)
            curr->prev->next = temp;
        else
            head = temp; // Update head if inserting before the first node
        curr->prev = temp;
    }
}

template <class type>
void doubly_list<type>::delet() {
    dnode<type>* curr = findnode();
    if (curr != NULL) {
        if (curr->prev != NULL)
            curr->prev->next = curr->next;
        else
            head = curr->next; // Update head if the first node is deleted
        if (curr->next != NULL)
            curr->next->prev = curr->prev;
        delete curr;
    }
}

template <class type>
void doubly_list<type>::delete_start() {
    if (head == NULL) {
        cout << "List is empty.\n";
        return;
    }
    dnode<type>* temp = head;
    head = head->next;
    if (head != NULL)
        head->prev = NULL;
    delete temp;
}

template <class type>
void doubly_list<type>::delete_end() {
    if (head == NULL) {
        cout << "List is empty.\n";
        return;
    }
    dnode<type>* ptr = head;
    while (ptr->next != NULL)
        ptr = ptr->next;
    if (ptr->prev != NULL)
        ptr->prev->next = NULL;
    else
        head = NULL; // If only one node exists
    delete ptr;
}

template <class type>
void doubly_list<type>::delete_all() {
    while (head != NULL)
        delete_start();
}

template <class type>
void doubly_list<type>::reverse() {
    if (head == NULL || head->next == NULL)
        return;
    dnode<type>* curr = head;
    dnode<type>* temp = NULL;
    while (curr != NULL) {
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;
        curr = curr->prev; // Move to the previous node
    }
    if (temp != NULL)
        head = temp->prev; // Update head to the new first node
}

template <class type>
void doubly_list<type>::sort() {
    if (head == NULL || head->next == NULL)
        return;
    bool swapped;
    do {
        swapped = false;
        dnode<type>* ptr = head;
        while (ptr->next != NULL) {
            if (ptr->data > ptr->next->data) {
                swap(ptr->data, ptr->next->data);
                swapped = true;
            }
            ptr = ptr->next;
        }
    } while (swapped);
}

template <class type>
void doubly_list<type>::del_all_oc() {
    if (head == NULL)
        return;
    type val;
    cout << "Enter value to delete all occurrences: ";
    cin >> val;
    dnode<type>* ptr = head;
    while (ptr != NULL) {
        if (ptr->data == val) {
            dnode<type>* temp = ptr;
            ptr = ptr->next;
            if (temp->prev != NULL)
                temp->prev->next = temp->next;
            else
                head = temp->next; // Update head if the first node is deleted
            if (temp->next != NULL)
                temp->next->prev = temp->prev;
            delete temp;
        } else {
            ptr = ptr->next;
        }
    }
}

int main() {
    doubly_list<int> list;
    int choice;

    cout << "\nDOUBLY LINKED LIST MENU:\n";
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
