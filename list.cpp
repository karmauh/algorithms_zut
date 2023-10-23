#include <iostream>
#include <string.h>
#include <time.h>
using namespace std;

class List {
public:
    int id;
    int data;
    char ch;
    List* next = NULL;
    List* prev = NULL;
    List* head = NULL;
    List();
    ~List();
    void pushFront(int _data, char _ch);
    void to_String(int _number);
    void pushBack(int _data, char _ch);
    void popBack();
    void popFront();
    void deleteList();
    void findByIndex(int _id);
    void changeDataByIndex(int _id, int _data, char _ch);
    List* findElement(int _data, char _ch);
    bool findAndDelete(int _data, char _ch);
};

int main() {
    List newList;
    clock_t start, stop;
    float time, timeElement;
    const int add_element = 100;
    const int test_number = 100;
    int _data;
    int n = 0;
    char _ch;
    for(int i = 0; i <= test_number; i++) {
        start = clock();
        for(int j = 0; j < n; j++) {
            _ch = 97 + rand() % 26;
            _data = rand() % 10000 + 1;
            newList.pushBack(_data, _ch);
        }

        stop = clock();
        time = (float)(stop - start) / CLOCKS_PER_SEC;
        timeElement = time / n;
        newList.to_String(100);
        cout << "Wczytanie " << n << " elementow do listy zajelo (" << time << " sekund)" << "\nCo daje srednio: (" << timeElement << " sekund) na element" << endl << endl;
        n = n + add_element;
    }
}

List::List()
    : id(0)
    , data(0)
    , ch('c')
{}

List::~List() {
    if (head != NULL) {
        List* current = head->next;
        List* temp;
        while (current != NULL) {
            temp = current->next;
            delete current;
            current = temp;
        }
        delete head;
        head = NULL;
    }
}

void List::pushFront(int _data, char _ch) {
    List* newE = new List();
    newE->data = _data;
    newE->ch = _ch;

    newE->next = head;
    newE->prev = NULL;
    newE->id = 0;

    if (head != NULL) {
        head->prev = newE;
        List* current = head;
        while (current != NULL) {
            current->id++;
            current = current->next;
        }
    }
    head = newE;

}

void List::to_String(int _number) {
    int numberOfElements = 0;
    List* current = head;
    if (head != NULL && _number > 0) {
        while (current != NULL) {
            if (numberOfElements < _number) {
                cout << "ID: " << current->id + 1 << " " << current->data << " " << current->ch << endl;
            }
            if (numberOfElements == _number) {
                cout << "..." << endl;
            }
            current = current->next;
            numberOfElements++;
        }
        cout << "Cala lista zawiera " << numberOfElements << " elementow powyzej przedstawiono " << _number << " z nich" << endl;
    }
    else {
        cout << "Lista jest pusta!" << endl;
    }
}

void List::pushBack(int _data, char _ch) {
    List* newE = new List();
    List* current = head;
    newE->data = _data;
    newE->ch = _ch;

    if (head == NULL) {
        newE->prev = NULL;
        newE->next = NULL;
        head = newE;
        newE->id = 0;
    }
    else {
        while (current->next != NULL) {
            current = current->next;
        }
        newE->next = NULL;
        newE->id = current->id + 1;
        current->next = newE;
        newE->prev = current;
    }
}

void List::popBack() {
    if (head != NULL) {
        List* current = head;

        while (current->next != NULL) {
            current = current->next;
        }
        current->prev->next = NULL;
        delete current;
        current = NULL;
    }
}

void List::popFront() {
    List* current;
    if (head != NULL)
        if (head->next != NULL) {
            current = head;
            head = current->next;
            head->prev = NULL;

            delete current;
            current = NULL;
            current = head;

            while (current != NULL) {
                current->id--;
                current = current->next;
            }
        }
        if (head->next == NULL)
            deleteList();
}

void List::deleteList() {
    if (head != NULL) {
        List* current = head->next;
        List* temp;
        while (current != NULL) {
            temp = current->next;
            delete current;
            current = temp;
        }

        delete head;
        head = NULL;
    }
}

void List::findByIndex(int _id) {
    List* current = head;
    while (current != NULL) {
        if (current->id == _id) {
            cout << "ID: " << current->id << " " << current->data << " " << current->ch << endl;
            return;
        }
        current = current->next;
    }

    cout << NULL << endl;
}

void List::changeDataByIndex(int _id, int _data, char _ch) {
    List* current = head;
    while (current != NULL) {
        if (current->id == _id) {
            current->data = _data;
            current->ch = _ch;
            return;
        }
        current = current->next;
    }

    cout << NULL << endl;
}

List* List::findElement(int _data, char _ch) {
    List* current = head;
    while (current != NULL) {
        if ((current->data == _data) && (current->ch == _ch)) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

bool List::findAndDelete(int _data, char _ch) {
    List* current = head;
    while (current != NULL) {
        if ((current->data == _data) && (current->ch == _ch)) {
            if (current->prev == NULL) {
                popFront();
                return true;
            }
            if (current->next == NULL) {
                popBack();
                return true;
            }
        }
        current = current->next;
    }

    return false;
}
