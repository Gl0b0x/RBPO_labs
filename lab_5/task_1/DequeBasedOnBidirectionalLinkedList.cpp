#include <algorithm>
#include <iostream>
using namespace std;
template <typename T>
class AbstractDeque {
public:
	virtual int GetSize() const = 0;
	virtual void PushFront(const T& element) = 0;
	virtual T PopFront() = 0;
	virtual void PushBack(const T& element) = 0;
	virtual T PopBack() = 0;
	virtual T PeekFront() const = 0;
	virtual T PeekBack() const = 0;
};

template <typename T>
class Deque : public AbstractDeque<T> {
	struct Node {
		T data;
		Node* prev;
		Node* next;
		Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
	};
	Node* head;
	Node* tail;
	unsigned count;
	void initList(const Deque& other) {
		head = tail = nullptr;
		count = other.count;
		Clear();
		if (other.head == nullptr) {
			return;
		}
		Node* temp = other.head;
		Node* predPointer, * pointer;
		predPointer = new Node(temp->data);
		head = predPointer;
		temp = temp->next;
		if (temp == nullptr) {
			tail = head;
			return;
		}
		while (temp != nullptr) {
			pointer = new Node(temp->data);
			predPointer->next = pointer;
			pointer->prev = predPointer;
			predPointer = pointer;
			temp = temp->next;
		}
		tail = pointer;
	}
public:
	class Iterator {
	private:
		Node* current;
	public:
		Iterator(Node* node) : current(node) {}
		Iterator begin() const {
			return Iterator(head);
		}
		Iterator end() const {
			return Iterator(nullptr);
		}
		const Iterator begin() {
			return Iterator(head);
		}
		const Iterator end() {
			return Iterator(nullptr);
		}
	};
	const T& operator[](int index) const {
		Node node = getAt(index);
		return node->data;
	}
	T& operator[](int index) {
		Node* node = getAt(index);
		return node->data;
	}
	void Clear() {
		Node* current = head;
		while (current != nullptr) {
			Node* next = current->next;
			delete current;
			current = next;
		}
		head = tail = nullptr;
		count = 0;
	}
	~Deque() {
		Clear();
	}
	Deque() : head(nullptr), tail(nullptr), count(0) {}
	Deque(const Deque& other) {
		initList(other);
	}
	Deque(Deque&& other) {
		if (this == &other) {
			return *this;
		}
		head = std::move(other.head);
		tail = std::move(other.tail);
		count = std::move(other.count);
		other.head = other.tail = nullptr;
		other.count = 0;
	}
	Deque(std::initializer_list<T> ilist) : head(nullptr), tail(nullptr), count(0) {
		Deque<T> temp;
		for (const T& number : ilist) {
			temp.PushBack(number);
		}
		std::swap(head, temp.head);
		std::swap(tail, temp.tail);
		std::swap(count, temp.count);

		if (&temp != this) {
			temp.head = nullptr;
			temp.tail = nullptr;
			temp.count = 0;
		}

	}
	Node* getAt(int index) {
		Node* ptr = head;
		int i = 0;
		if (index >= count) {
			return tail;
		}
		for (int i = 0; i < index; i++) {
			ptr = ptr->next;
		}
		return ptr;
	}
	void PushBack(const T& element) override {
		Node* newNode = new Node(element);
		if (tail == nullptr) {
			tail = head = newNode;
		}
		else {
			newNode->prev = tail;
			tail->next = newNode;
			tail = newNode;
		}
		count++;
	}
	void PushFront(const T& element) override {
		Node* newNode = new Node(element);
		if (tail == nullptr) {
			tail = head = newNode;
		}
		else {
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
		}
		count++;
	}
	T PopBack() override {
		if (head == nullptr) {
			return 0;
		}
		T element = tail->data;
		if (count == 1) {
			delete tail;
			head = tail = nullptr;
			count--;
			return true;
		}
		Node* pred = tail->prev;
		pred->next = nullptr;
		delete tail;
		tail = pred;
		count--;
		return element;
	}
	T PopFront() override {
		if (head == nullptr) {
			return 0;
		}
		T element = head->data;
		if (count == 1) {
			delete head;
			head = tail = nullptr;
			count--;
			return true;
		}
		Node* pred = head->next;
		pred->prev = nullptr;
		delete head;
		head = pred;
		count--;
		return element;
	}
	T PeekFront() const override {
		if (count == 0) {
			return 0;
		}
		return head->data;
	}
	T PeekBack() const override {
		if (count == 0) {
			return false;
		}
		return tail->data;
	}
	void InsertAt(const T& value, int index) {
		Node* right = getAt(index);
		Node* pointer = new Node(value);
		if (right == head) {
			pointer->next = head;
			head->prev = pointer;
			head = pointer;
			count++;
			return;
		}
		if (right == tail) {
			tail->next = pointer;
			pointer->prev = tail;
			tail = pointer;
			count++;
			return;
		}
		Node* left = right->prev;
		pointer->prev = left;
		pointer->next = right;
		left->next = pointer;
		right->prev = pointer;
		count++;
	}
	int RemoveAt(int index) {
		Node* pointer = getAt(index);
		int deleteValue = pointer->data;
		count--;
		if (pointer == head) {
			Node* newHead = pointer->next;
			if (newHead != nullptr) {
				newHead->prev = nullptr;
			}
			delete head;
			head = newHead;
			return deleteValue;
		}
		if (pointer == tail) {
			Node* newTail = pointer->prev;
			if (newTail != nullptr) {
				newTail->next = nullptr;
			}
			delete tail;
			tail = newTail;
			return deleteValue;
		}
		Node* left = pointer->prev;
		Node* right = pointer->next;
		left->next = right;
		right->prev = left;
		delete pointer;
		return deleteValue;
	}
	int GetSize() const override {
		return count;
	}
	Deque& operator=(const Deque& other) {
		if (this == &other) {
			return *this;
		}
		initList(other);
		return *this;
	}
	Deque& operator=(Deque&& other) {
		if (this == &other) {
			return *this;
		}
		head = std::move(other.head);
		tail = std::move(other.tail);
		count = std::move(other.count);
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
		return *this;
	}
	Deque& operator=(std::initializer_list<int> ilist) {
		Deque<T> temp;
		for (const T& number : ilist) {
			temp.PushBack(number);
		}
		swap(head, temp.head);
		swap(tail, temp.tail);
		swap(count, temp.count);

		if (&temp != this) {
			temp.head = nullptr;
			temp.tail = nullptr;
			temp.count = 0;
		}

		return *this;
	}
};

int main() {
	Deque<int> deq = { 1, 2, 3 };
	cout << deq.GetSize() << endl;
	deq.PushBack(1);
	cout << deq.GetSize() << endl;
	cout << deq.PopBack() << endl;
	cout << deq.GetSize() << endl;
	return 0;
}