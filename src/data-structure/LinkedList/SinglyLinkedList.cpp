#include <iostream>
#include "SinglyLinkedList.h"

using std::string;
using std::cout;
using std::endl;

template<typename T>
SinglyLinkedList<T>::SinglyLinkedList() {
    head = tail = nullptr;
    _size = 0;
}

template<typename T>
void SinglyLinkedList<T>::addLast(T data) {
    if (head != nullptr) {
        Node *n = new Node();
        n->data = data;
        n->next = nullptr;
        tail->next = n;
        tail = n;
        _size++;
    } else {
        Node *n = new Node();
        n->data = data;
        n->next = nullptr;
        head = tail = n;
        _size++;
    }
}

template<typename T>
void SinglyLinkedList<T>::addFirst(T data) {
    Node *n = new Node();
    n->data = data;
    n->next = head;
    head = n;
    _size++;
}

template<typename T>
void SinglyLinkedList<T>::addAt(int index, T data) {
    if (index == 0) {
        addFirst(data);
        return;
    }

    Node *temp = head;
    int idx = 0;
    while (idx < index - 1) {
        temp = temp->next;
        idx++;
    }
    Node *n = new Node();
    n->data = data;
    n->next = temp->next;
    temp->next = n;
    _size++;
}

template<typename T>
T SinglyLinkedList<T>::removeFirst() {
    Node *removedNode = head;
    head = head->next;
    _size--;
    return removedNode->data;
}

template<typename T>
T SinglyLinkedList<T>::removeLast() {
    if (_size == 0) {
        cout << "Empty linked list";
        T t;
        return t;
    }

    if (_size == 1) {
        Node *rm = head;
        head = tail = nullptr;
        _size--;
        return rm->data;
    }

    _size--;
    Node *temp = head;
    while (temp->next->next != nullptr) {
        temp = temp->next;
    }
    Node *removed = temp->next;
    temp->next = nullptr;
    return removed->data;
}

template<typename T>
T SinglyLinkedList<T>::remove(int index) {
    if (_size <= index || index < 0) {
        cout << "Out of bound";
        T t;
        return t;
    } else if (index == 0) {

        return removeFirst();
    } else if (index == _size - 1) {
        return removeLast();
    }

    _size--;

    Node *temp = head;
    Node *prev = head;
    int idx = 0;
    while (idx < index) {
        prev = temp;
        temp = temp->next;
        idx++;
    }
    Node *removed = temp;
    prev->next = temp->next;
    return removed->data;
}

template<typename T>
int SinglyLinkedList<T>::size() {
    return _size;
}

template<typename T>
void SinglyLinkedList<T>::show() {
    Node *temp = head;
    while (temp != nullptr) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "null\n";
}

void singlyLinkedListDriver() {
    SinglyLinkedList<string> list;
    list.addLast("10yo");
    list.addLast("20yo");
    list.addLast("1yo");
    list.addLast("12yo");
    list.addLast("11yo");
    list.show();
    cout << list.remove(0) << endl;
    cout << list.remove(list.size() - 1) << endl;
    list.show();
    list.addLast("111yo!");//todo
    list.show();
    cout << list.remove(1) << endl;
    list.show();
}

