#include <iostream>
using namespace std;

template <class type>
class doubly_circular_list;  // Forward declaration of doubly_circular_list

// Node structure for doubly circular linked list
template <class type>
class dcnode {
    friend class doubly_circular_list<type>;  // Granting doubly_circular_list access to dcnode's private members
    type data;
    dcnode<type>* next;
    dcnode<type>* prev;
public:
    dcnode() : next(NULL), prev(NULL) {}
};

// Doubly Circular Linked List class
template <class type>
class doubly_circular_list {
    dcnode<type>* last;  // Pointer to the last node

    dcnode<type>* getnode();  // Helper function to get a new node
    dcnode<type>* findnode() const;  // Helper function to find a node by value

public:
    doubly_circular_list() : last(NULL) {}
    ~doubly_circular_list();  // Destructor to delete all nodes

    void display();  // Display the list
    void append();  // Append a node at the end
    void add_start();  // Add a node at the start
    void insert_after();  // Insert a node after a given node
    void insert_before();  // Insert a node before a given node
    void delet();  // Delete a specific node
    void delete_start();  // Delete the first node
    void delete_end();  // Delete the last node
    void delete_all();  // Delete all nodes
    void reverse();  // Reverse the list
    void sort();  // Sort the list
    void del_all_oc();  // Delete all occurrences of a given value
};

// Helper function to create a new node
template <class type>
dcnode<type>* doubly_circular_list<type>::getnode() {
    dcnode<type>* ptr = new dcnode<type>;
    cout << "\nEnter data part of the node: ";
    cin >> ptr->data;
    return ptr;
}

// Helper function to find a node by value
template <class type>
dcnode<type>* doubly_circular_list<type>::findnode() const {
    if (last == NULL) {
        cout << "\nList is empty.\n";
        return NULL;
    }
    dcnode<type>* ptr = last->next;
    type val;
    cout << "\nEnter node value to be searched: ";
    cin >> val;
    do {
        if (ptr->data == val)
            return ptr;
        ptr = ptr->next;
    } while (ptr != last->next);
    cout << "\nNode not found.\n";
    return NULL;
}

// Display the entire list
template <class type>
void doubly_circular_list<type>::display() {
    if (last == NULL) {
        cout << "\nList is empty.\n";
        return;
    }
    dcnode<type>* ptr = last->next;
    cout << "\nDoubly Circular Linked List is: ";
    do {
        cout << ptr->data << " ";
        ptr = ptr->next;
    } while (ptr != last->next);
    cout << endl;
}

// Append a node at the end of the list
template <class type>
void doubly_circular_list<type>::append() {
    dcnode<type>* temp = getnode();
    if (last == NULL) {
        last = temp;
        last->next = last;
        last->prev = last;
    } else {
        temp->next = last->next;
        last->next->prev = temp;
        last->next = temp;
        temp->prev = last;
        last = temp;
    }
}

// Add a node at the start of the list
template <class type>
void doubly_circular_list<type>::add_start() {
    dcnode<type>* temp = getnode();
    if (last == NULL) {
        last = temp;
        last->next = last;
        last->prev = last;
    } else {
        temp->next = last->next;
        temp->prev = last;
        last->next->prev = temp;
        last->next = temp;
    }
}

// Insert a node after a given node
template <class type>
void doubly_circular_list<type>::insert_after() {
    dcnode<type>* curr = findnode();
    if (curr != NULL) {
        dcnode<type>* ptr = getnode();
        ptr->next = curr->next;
        ptr->prev = curr;
        curr->next->prev = ptr;
        curr->next = ptr;
        if (curr == last) {
            last = ptr;
        }
    }
}

// Insert a node before a given node
template <class type>
void doubly_circular_list<type>::insert_before() {
    dcnode<type>* curr = findnode();
    if (curr != NULL) {
        dcnode<type>* temp = getnode();
        if (curr == last->next) {
            temp->next = last->next;
            temp->prev = last;
            last->next->prev = temp;
            last->next = temp;
        } else {
            dcnode<type>* prev = curr->prev;
            prev->next = temp;
            temp->prev = prev;
            temp->next = curr;
            curr->prev = temp;
        }
    }
}

// Delete a specific node
template <class type>
void doubly_circular_list<type>::delet() {
    dcnode<type>* curr = findnode();
    if (curr != NULL) {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        if (curr == last) {
            last = (curr == last->next) ? NULL : curr->prev;
        }
        delete curr;
    }
}

// Delete the first node
template <class type>
void doubly_circular_list<type>::delete_start() {
    if (last == NULL) {
        cout << "\nList is empty.\n";
        return;
    }
    dcnode<type>* temp = last->next;
    if (last->next == last) {
        last = NULL;
    } else {
        last->next = temp->next;
        temp->next->prev = last;
    }
    delete temp;
}

// Delete the last node
template <class type>
void doubly_circular_list<type>::delete_end() {
    if (last == NULL) {
        cout << "\nList is empty.\n";
        return;
    }
    dcnode<type>* temp = last;
    if (temp->next == last) {
        delete last;
        last = NULL;
    } else {
        temp = last->prev;
        temp->next = last->next;
        last->next->prev = temp;
        delete last;
        last = temp;
    }
}

// Delete all nodes in the list
template <class type>
void doubly_circular_list<type>::delete_all() {
    if (last == NULL)
        return;
    dcnode<type>* ptr = last->next;
    do {
        dcnode<type>* temp = ptr;
        ptr = ptr->next;
        delete temp;
    } while (ptr != last->next);
    last = NULL;
}

// Reverse the list
template <class type>
void doubly_circular_list<type>::reverse() {
    if (last == NULL || last->next == last)
        return;
    dcnode<type>* curr = last->next;
    dcnode<type>* prev = NULL;
    dcnode<type>* next = NULL;
    do {
        next = curr->next;
        curr->next = prev;
        curr->prev = next;
        prev = curr;
        curr = next;
    } while (curr != last->next);
    last->next = prev;
    last = curr;
}

// Sort the list in ascending order
template <class type>
void doubly_circular_list<type>::sort() {
    if (last == NULL || last->next == last)
        return;
    bool swapped;
    do {
        swapped = false;
        dcnode<type>* curr = last->next;
        dcnode<type>* next = curr->next;
        do {
            if (curr->data > next->data) {
                swap(curr->data, next->data);
                swapped = true;
            }
            curr = next;
            next = next->next;
        } while (curr != last);
    } while (swapped);
}

// Delete all occurrences of a specific value
template <class type>
void doubly_circular_list<type>::del_all_oc() {
    if (last == NULL)
        return;
    type val;
    cout << "\nEnter value to delete all occurrences: ";
    cin >> val;
    bool found = false;
    dcnode<type>* curr = last->next;
    do {
        if (curr->data == val) {
            found = true;
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            if (curr == last) {
                last = (curr == last->next) ? NULL : curr->prev;
            }
            dcnode<type>* temp = curr;
            curr = curr->next;
            delete temp;
        } else {
            curr = curr->next;
        }
    } while (curr != last->next);
    if (!found)
        cout << "\nValue not found.\n";
}

// Destructor definition
template <class type>
doubly_circular_list<type>::~doubly_circular_list() {
    delete_all();  // Calls delete_all method to clean up memory
}

int main() {
    doubly_circular_list<int> list;
    int choice;
    do {
        cout << "\n1. Append Node\n2. Add Start\n3. Insert After\n4. Insert Before\n5. Delete Node\n6. Delete Start\n7. Delete End\n8. Delete All\n9. Display\n10. Reverse\n11. Sort\n12. Delete All Occurrences\n13. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: list.append(); break;
            case 2: list.add_start(); break;
            case 3: list.insert_after(); break;
            case 4: list.insert_before(); break;
            case 5: list.delet(); break;
            case 6: list.delete_start(); break;
            case 7: list.delete_end(); break;
            case 8: list.delete_all(); break;
            case 9: list.display(); break;
            case 10: list.reverse(); break;
            case 11: list.sort(); break;
            case 12: list.del_all_oc(); break;
            case 13: cout << "\nExiting...\n"; break;
            default: cout << "\nInvalid choice.\n";
        }
    } while (choice != 13);
    return 0;
}
