#include <iostream>
using namespace std;

template <class T>
class Node
{
public:
    T info;
    Node<T>* next;
    Node(T value) : info(value), next(nullptr)
    {}
};

template <class T>
class LinkedList
{
private:
    Node<T>* head;

public:
    LinkedList() : head(nullptr)
    {}
    ~LinkedList()
    {
        if (head)
        {
            Node<T>* current = head;
            do
            {
                Node<T>* temp = current;
                current = current->next;
                delete temp;
            } while (current != head);
        }
    }
    LinkedList(const LinkedList<T>& other)
    {
        if (other.head == nullptr)
        {
            head = nullptr;
            return;
        }
        Node<T>* current = other.head;
        do
        {
            insertAtTail(current->info);
            current = current->next;
        } while (current != other.head);
    }
    void insertAtHead(T value)
    {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr)
        {
            head = newNode;
            head->next = head;
        }
        else
        {
            Node<T>* last = head;
            while (last->next != head)
            {
                last = last->next;
            }
            newNode->next = head;
            head = newNode;
            last->next = head;
        }
    }
    void insertAtTail(T value)
    {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr)
        {
            head = newNode;
            head->next = head;
        }
        else
        {
            Node<T>* last = head;
            while (last->next != head)
            {
                last = last->next;
            }
            last->next = newNode;
            newNode->next = head;
        }
    }
    bool deleteAtHead()
    {
        if (head == nullptr)
        {
            return false;
        }

        if (head->next == head)
        {
            delete head;
            head = nullptr;
            return true;
        }

        Node<T>* last = head;
        while (last->next != head)
        {
            last = last->next;
        }

        Node<T>* temp = head;
        head = head->next;
        last->next = head;
        delete temp;
        return true;
    }
    bool deleteAtTail()
    {
        if (head == nullptr)
        {
            return false;
        }

        if (head->next == head)
        {
            delete head;
            head = nullptr;
            return true;
        }

        Node<T>* prev = nullptr;
        Node<T>* current = head;
        while (current->next != head)
        {
            prev = current;
            current = current->next;
        }
        prev->next = head;
        delete current;
        return true;
    }
    bool insertAfter(T value, T key)
    {
        if (head == nullptr)
        {
            return false;
        }

        Node<T>* current = head;
        do
        {
            if (current->info == key)
            {
                Node<T>* newNode = new Node<T>(value);
                newNode->next = current->next;
                current->next = newNode;
                return true;
            }
            current = current->next;
        } while (current != head);

        return false;
    }
    bool insertBefore(T value, T key)
    {
        if (head == nullptr)
        {
            return false;
        }

        Node<T>* current = head;
        Node<T>* prev = nullptr;
        do
        {
            if (current->info == key)
            {
                Node<T>* newNode = new Node<T>(value);
                if (prev == nullptr)
                {
                    Node<T>* last = head;
                    while (last->next != head)
                    {
                        last = last->next;
                    }
                    newNode->next = head;
                    head = newNode;
                    last->next = head;
                }
                else
                {
                    newNode->next = current;
                    prev->next = newNode;
                }
                return true;
            }
            prev = current;
            current = current->next;
        } while (current != head);
        return false;
    }
    void display() const
    {
        if (head == nullptr)
        {
            cout << "List is empty." << endl;
            return;
        }

        Node<T>* current = head;
        do
        {
            cout << current->info << " -> ";
            current = current->next;
        } while (current != head);
        cout << "(head)" << endl;
    }
    bool deleteBefore(T key)
    {
        if (head == nullptr || head->next == head)
        {
            return false;
        }

        Node<T>* current = head;
        Node<T>* prev = nullptr;
        Node<T>* beforePrev = nullptr;

        do
        {
            beforePrev = prev;
            prev = current;
            current = current->next;

            if (current->info == key)
            {
                if (prev == head)
                {

                    Node<T>* tail = head;
                    while (tail->next != head)
                    {
                        tail = tail->next;
                    }
                    if (tail == head)
                    {
                        return false;
                    }

                    Node<T>* temp = tail;
                    tail = nullptr;
                    delete temp;
                    return true;
                }
                else if (beforePrev == nullptr)
                {
                    return false;
                }
                else
                {

                    beforePrev->next = current;
                    delete prev;
                    return true;
                }
            }
        } while (current != head);
        return false;
    }
    bool deleteAfter(T value)
    {
        if (head == nullptr || head->next == head)
        {
            return false;
        }

        Node<T>* current = head;
        do
        {
            if (current->info == value)
            {
                Node<T>* toDelete = current->next;
                if (toDelete == head)
                {
                    Node<T>* temp = head;
                    while (temp->next != head)
                    {
                        temp = temp->next;
                    }
                    if (temp == head)
                    {
                        return false;
                    }
                    temp->next = head->next;
                    delete head;
                    head = temp->next;
                }
                else
                {

                    current->next = toDelete->next;
                    delete toDelete;
                }
                return true;
            }
            current = current->next;
        } while (current != head);

        return false;
    }
    int getLength()
    {
        if (head == nullptr)
        {
            return 0;
        }

        int count = 0;
        Node<T>* current = head;
        do
        {
            count++;
            current = current->next;
        } while (current != head);

        return count;
    }
    Node<T>* search(T x)
    {
        if (head == nullptr)
        {
            return nullptr;
        }

        Node<T>* current = head;
        do
        {
            if (current->info == x)
            {
                return current;
            }
            current = current->next;
        } while (current != head);
        return nullptr;
    }
    Node<T>* sortLinkedList(Node<T>* head)
    {
        if (head == nullptr || head->next == head)
        {
            return head;  // If the list is empty or has only one element, it's already sorted
        }

        bool swapped;
        Node<T>* current;
        Node<T>* last = nullptr;

        do
        {
            swapped = false;
            current = head;

            while (current->next != last && current->next != head)
            {
                if (current->info > current->next->info)
                {
                    // Swap the data of the nodes
                    T temp = current->info;
                    current->info = current->next->info;
                    current->next->info = temp;
                    swapped = true;
                }
                current = current->next;
            }
            last = current;

        } while (swapped);

        return head;
    }
    Node<T>* mergeLinkedLists(Node<T>* head1, Node<T>* head2)
    {
        if (head1 == nullptr) return head2;
        if (head2 == nullptr) return head1;

        Node<T>* tail1 = head1;
        while (tail1->next != head1)
        {
            tail1 = tail1->next;
        }

        Node<T>* tail2 = head2;
        while (tail2->next != head2)
        {
            tail2 = tail2->next;
        }

        // Join the two lists
        tail1->next = head2;
        tail2->next = head1;  // This keeps the circular nature intact

        return head1; // Return the new head of the merged list
    }
    bool deleteEvenNodes()
    {
        if (head == nullptr)
        {
            return false;
        }

        bool deletedAny = false;
        Node<T>* current = head;
        Node<T>* prev = nullptr;
        while (current->info % 2 == 0)
        {
            deletedAny = true;
            if (current->next == head)
            {
                delete head;
                head = nullptr;
                return true;
            }
            else
            {
                Node<T>* temp = current;
                prev = head;
                while (prev->next != head)
                {
                    prev = prev->next;
                }
                head = head->next;
                prev->next = head;
                current = head;
                delete temp;
            }
        }
        prev = current;
        current = current->next;

        while (current != head)
        {
            if (current->info % 2 == 0)
            {
                deletedAny = true;
                Node<T>* temp = current;
                prev->next = current->next;
                current = current->next;
                delete temp;
            }
            else
            {
                prev = current;
                current = current->next;
            }
        }

        return deletedAny;
    }

};