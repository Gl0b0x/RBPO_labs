#include <initializer_list>
#include <iterator>

class DynamicArray {
private:
	int* arr;
	unsigned count;
	void initArray(int* other_arr, int other_count) {
		arr = new int[other_count];
		count = other_count;
		for (int i = 0; i < count; ++i) {
			arr[i] = other_arr[i];
		}
	}
	void initArray(std::initializer_list<int> list) {
		arr = new int[list.size()];
		count = list.size();
		int i = 0;
		for (auto number : list) {
			arr[i] = number;
			i++;
		}
	}
public:
	class Iterator {
	private:
		int* current;
	public:
		Iterator(int* ptr) {
			current = ptr;
		}
	};
	DynamicArray() {
		arr = new int[0];
		count = 0;
	}
	explicit DynamicArray(unsigned size) {
		arr = new int[size];
		count = size;
	}
	DynamicArray(const DynamicArray& other) {
		initArray(other.arr, count);
	}
	DynamicArray(DynamicArray&& other) {
		arr = other.arr;
		count = other.count;
		other.arr = nullptr;
	}
	~DynamicArray() {
		delete[] arr;
	}
	DynamicArray(std::initializer_list<int> list) {
		initArray(list);
	}
	unsigned GetSize() const {
		return count;
	}
	DynamicArray::Iterator begin() {
		return Iterator(arr);
	}
	const DynamicArray::Iterator begin() const {
		return Iterator(arr);
	}
	DynamicArray::Iterator end() {
		return Iterator(arr+count);
	}
	const DynamicArray::Iterator end() const {
		return Iterator(arr+count);
	}
	const int& operator[](int index) const {
		if (index >= 0 && index < count) {
			return arr[index];
		}
	}
	int& operator[](int index){
		if (index >= 0 && index < count) {
			return arr[index];
		}
	}
	DynamicArray& operator=(const DynamicArray& other)
	{
		if (this == &other) {
			return *this;
		}
		delete this;
		initArray(other.arr, other.count);
		return *this;
	}
	DynamicArray& operator=(DynamicArray&& other)
	{
		if (this == &other) {
			return *this;
		}
		delete this;
		initArray(other.arr, other.count);
		return *this;
	}
	DynamicArray& operator=(std::initializer_list<int> list) {
		delete this;
		initArray(list);
		return *this;
	}
};