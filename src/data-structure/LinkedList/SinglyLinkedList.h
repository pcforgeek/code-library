#ifndef DS_ALGO_CPP_LINKEDLIST_H
#define DS_ALGO_CPP_LINKEDLIST_H

template<class T>
class SinglyLinkedList {
    struct Node {
        T data;
        Node *next;
    };

    Node *head;
    Node *tail;
    int _size;

public:

    SinglyLinkedList();

    ~SinglyLinkedList() {
        delete (head);
        delete (tail);
    }

    void addLast(T data);

    void addFirst(T data);

    void addAt(int index, T data);

    T removeFirst();

    T removeLast();

    T remove(int index);

    int size();

    void show();
};

#endif //DS_ALGO_CPP_LINKEDLIST_H
