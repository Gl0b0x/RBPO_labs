#include <iostream>

template <typename T>
class AbstractDeque {
public:
    virtual ~AbstractDeque() = default;
    virtual int GetSize() const = 0;
    virtual void PushFront(const T& element) = 0;
    virtual T PopFront() = 0;
    virtual void PushBack(const T& element) = 0;
    virtual T PopBack() = 0;
    virtual T PeekFront() const = 0;
    virtual T PeekBack() const = 0;
    virtual bool IsEmpty() const = 0;
};

template <typename T>
class Node {
public:
    T data;
    Node* next;

    Node(const T& value) : data(value), next(nullptr) {}
};

template <typename T>
class LinkedListDeque : public AbstractDeque<T> {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    LinkedListDeque() : head(nullptr), tail(nullptr), size(0) {}

    ~LinkedListDeque() {
        Clear();
    }

    LinkedListDeque(const LinkedListDeque& other) : head(nullptr), tail(nullptr), size(0) {
        CopyFrom(other);
    }

    LinkedListDeque& operator=(const LinkedListDeque& other) {
        if (this != &other) {
            Clear();
            CopyFrom(other);
        }
        return *this;
    }

    LinkedListDeque(LinkedListDeque&& other) noexcept : head(nullptr), tail(nullptr), size(0) {
        MoveFrom(std::move(other));
    }

    LinkedListDeque& operator=(LinkedListDeque&& other) noexcept {
        if (this != &other) {
            Clear();
            MoveFrom(std::move(other));
        }
        return *this;
    }

    int GetSize() const override {
        return size;
    }

    void PushFront(const T& element) override {
        Node<T>* newNode = new Node<T>(element);
        if (IsEmpty()) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head = newNode;
        }
        size++;
    }

    T PopFront() override {
        if (IsEmpty()) {
            return 0;
        }
        Node<T>* temp = head;
        T value = temp->data;
        head = head->next;
        delete temp;
        size--;
        if (IsEmpty()) {
            tail = nullptr;
        }
        return value;
    }

    void PushBack(const T& element) override {
        Node<T>* newNode = new Node<T>(element);
        if (IsEmpty()) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    T PopBack() override {
        if (IsEmpty()) {
            return 0;
        }
        T value = tail->data;
        Node<T>* cur = head;
        if (cur == tail) {
            delete head;
            tail = head = nullptr;
            size--;
            return value;
        }
        while (true) {
            if (cur->next == tail) {
                break;
            }
            cur = cur->next;
        }
        delete tail;
        size--;
        tail = cur;
        tail->next = nullptr;
        return value;
    }

    T PeekFront() const override {
        if (IsEmpty()) {
            return 0;
        }
        return head->data;
    }

    T PeekBack() const override {
        if (IsEmpty()) {
            return 0;
        }
        return tail->data;
    }

    bool IsEmpty() const override {
        return size == 0;
    }

    void Clear() {
        while (!IsEmpty()) {
            PopFront();
        }
    }

private:
    void CopyFrom(const LinkedListDeque& other) {
        Node<T>* temp = other.head;
        while (temp != nullptr) {
            PushBack(temp->data);
            temp = temp->next;
        }
    }

    void MoveFrom(LinkedListDeque&& other) {
        head = other.head;
        tail = other.tail;
        size = other.size;
        other.head = other.tail = nullptr;
        other.size = 0;
    }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const LinkedListDeque<U>& deque);
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const LinkedListDeque<T>& deque) {
    Node<T>* temp = deque.head;
    while (temp != nullptr) {
        os << temp->data << " ";
        temp = temp->next;
    }
    return os;
}

// Функция, получающая указатель на базовый класс и демонстрирующая работу
template <typename T>
void ShowDequeUsingPointer(const LinkedListDeque<T>* deque) {
    std::cout << "Deque using pointer: " << *deque << std::endl;
}

// Функция, получающая ссылку на базовый класс и демонстрирующая работу
template <typename T>
void ShowDequeUsingReference(const LinkedListDeque<T>& deque) {
    std::cout << "Deque using reference: " << deque << std::endl;
}

int main() {
    LinkedListDeque<int> deque;
    deque.PushBack(1);
    deque.PushBack(2);
    deque.PushFront(0);

    // Демонстрация работы функций с указателем и ссылкой на базовый класс
    ShowDequeUsingPointer(&deque);
    ShowDequeUsingReference(deque);

    return 0;
}