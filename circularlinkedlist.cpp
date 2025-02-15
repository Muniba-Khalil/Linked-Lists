#include <iostream>
using namespace std;


template <class type>
class cir_list; // Forward declaration of cir_list.

template <class type>
class node {
    friend class cir_list<type>;
    type data;
    node<type>* next;
public:
    node() {
        next = NULL;
    }
};

template <class type>
class cir_list {
    node<type>* last;
    node<type>* getnode();
    node<type>* findnode() const;

public:
    cir_list() {
        last = NULL;
    }
    ~cir_list() {
        delete_all();
    }
    void display();
    void append(); // add last node
    void add_start(); // add first node
    void insert_after();
    void insert_before();
    void delet(); // delete a specific node
    void delete_after();
    void delete_before();
    void delete_end(); // delete last node
    void delete_start(); // delete first node
    void delete_all();
    void delete_even();
    void delete_odd();
    void reverse();
    void sort();
    void del_all_oc();
};

template <class type>
void cir_list<type>::display() {
    if (last == NULL) {
        cout << "\nList is empty.\n";
        return;
    }
    node<type>* ptr = last->next;
    cout << "\nLinked List is: ";
    do {
        cout << ptr->data << " ";
        ptr = ptr->next;
    } while (ptr != last->next);
    cout << endl;
}

template <class type>
node<type>* cir_list<type>::getnode() {
    node<type>* ptr = new node<type>;
    cout << "\nEnter data part of the node: ";
    cin >> ptr->data;
    return ptr;
}

template <class type>
node<type>* cir_list<type>::findnode() const {
    if (last == NULL) {
        cout << "List is empty." << endl;
        return NULL;
    }
    node<type>* ptr = last->next;
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

template <class type>
void cir_list<type>::append() {
    node<type>* temp = getnode();
    if (last == NULL) {
        last = temp;
        last->next = last;
    } else {
        temp->next = last->next;
        last->next = temp;
        last = temp;
    }
}

template <class type>
void cir_list<type>::add_start() {
    node<type>* temp = getnode();
    if (last == NULL) {
        last = temp;
        last->next = last;
    } else {
        temp->next = last->next;
        last->next = temp;
    }
}

template <class type>
void cir_list<type>::insert_after() {
    node<type>* curr = findnode();
    if (curr != NULL) {
        node<type>* ptr = getnode();
        ptr->next = curr->next;
        curr->next = ptr;
        if (curr == last)
            last = ptr;
    }
}

template <class type>
void cir_list<type>::insert_before() {
    node<type>* curr = findnode();
    if (curr != NULL) {
        node<type>* temp = getnode();
        if (curr == last->next) {
            temp->next = last->next;
            last->next = temp;
        } else {
            node<type>* prev = last->next;
            while (prev->next != curr)
                prev = prev->next;
            temp->next = curr;
            prev->next = temp;
        }
    }
}

template <class type>
void cir_list<type>::delet() {
    node<type>* curr = findnode();
    if (curr != NULL) {
        node<type>* prev = last->next;
        while (prev->next != curr)
            prev = prev->next;
        prev->next = curr->next;
        if (curr == last)
            last = (curr == last->next) ? NULL : prev;
        delete curr;
    }
}

template <class type>
void cir_list<type>::delete_start() {
    if (last == NULL) {
        cout << "List is empty.\n";
        return;
    }
    node<type>* temp = last->next;
    if (last->next == last) {
        last = NULL;
    } else {
        last->next = temp->next;
    }
    delete temp;
}

template <class type>
void cir_list<type>::delete_end() {
    if (last == NULL) {
        cout << "List is empty.\n";
        return;
    }
    node<type>* temp = last->next;
    if (temp == last) {
        delete last;
        last = NULL;
    } else {
        while (temp->next != last)
            temp = temp->next;
        temp->next = last->next;
        delete last;
        last = temp;
    }
}

template <class type>
void cir_list<type>::delete_all() {
    if (last == NULL)
        return;
    node<type>* ptr = last->next;
    while (ptr != last) {
        node<type>* temp = ptr;
        ptr = ptr->next;
        delete temp;
    }
    delete last;
    last = NULL;
}

template <class type>
void cir_list<type>::reverse() {
    if (last == NULL || last->next == last)
        return;
    node<type>* prev = last;
    node<type>* curr = last->next;
    node<type>* next;
    do {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    } while (curr != last->next);
    last->next = prev;
    last = next;
}

template <class type>
void cir_list<type>::sort() {
    if (last == NULL || last->next == last)
        return;
    bool swapped;
    do {
        swapped = false;
        node<type>* curr = last->next;
        node<type>* next = curr->next;
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

template <class type>
void cir_list<type>::del_all_oc() {
    if (last == NULL)
        return;
    type val;
    cout << "Enter value to delete all occurrences: ";
    cin >> val;
    bool found = false;
    node<type>* curr = last->next;
    node<type>* prev = last;
    do {
        if (curr->data == val) {
            found = true;
            prev->next = curr->next;
            if (curr == last)
                last = (curr == last->next) ? NULL : prev;
            node<type>* temp = curr;
            curr = curr->next;
            delete temp;
            if (curr == last->next)
                break;
        } else {
            prev = curr;
            curr = curr->next;
        }
    } while (curr != last->next);
    if (!found)
        cout << "Value not found in the list.\n";
}

int main() {
    cir_list<int> list;
    int choice;

    cout << "\nCIRCULAR LINKED LIST MENU:\n";
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
