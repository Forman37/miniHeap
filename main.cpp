//I don't think I have an insert issue. I think the issue is parsing through the array and finding the min and deleting it.
//There's something going on where it's not going through the whole array.

#include <fstream>
#include <string>
#include <iostream>
using namespace std;

template <typename T>
class MinHeap{
private:
	T* elements;
	size_t capacity;
	size_t size;
	
	void resize(){
		capacity = (capacity == 0) ? 1 : capacity * 2;
		T* newElements = new T[capacity];
		for(size_t i = 0; i < size; ++i){
			newElements[i] = elements[i];
		}
		delete[] elements;
		elements = newElements;
	}
	
public:
	MinHeap() : elements(nullptr), capacity(0), size(0) {}
	
	~MinHeap(){
		delete[] elements;
	}
	
	void insert(const T& element){
		if(size == capacity){
			resize();
		}
		elements[size++] = element;
	}
	
	T extractMin(){
		T element = elements[0];
		size_t j = 0;
		
		for(size_t i = 0; i < size; ++i){
			if(element > elements[i]){
				element = elements[i];
				j = i;
			}
		}
		//cout << "\nElement to be removed : "<< elements[j] << endl;
		remove(elements[j]);
		return element;
	}
	
	bool remove(const T& element){
		for(size_t i = 0; i < size; ++i){
			if(elements[i] == element) {
				for (size_t j = i; j < size - 1; ++j) {
					elements[j] = elements[j + 1];
				}
				--size;
				return true;
			}
		}
		return false;
	}
	
	bool loadFromFile(const string& filename){
		ifstream file(filename);
		if(!file.is_open()){
			cerr << "Unable to open file for reading.\n";
			return false;
		}
		
		T element;
		while(file >> element){
			insert(element);
		}
		
		file.close();
		return true;
	}
	
	void print(){
		T element = elements[0];
		size_t currSize = size;
		
		for(size_t i = 0; i < currSize - 1; ++i){
			element = extractMin();
			cout << element << ",";
		}
		cout << elements[0] << endl;
	}
};


int main()
{
	MinHeap<int> heap;
	MinHeap<string> letters;
	
	if(heap.loadFromFile("numbers.txt")){
		//INSERT TEST CODE HERE
		heap.print();
	}
	
	if(letters.loadFromFile("words.txt")){
		//INSERT TEST CODE HERE
		letters.print();
	}
	
	/*heap.insert(39);
	heap.insert(34);
	heap.insert(51);
	heap.insert(7);
	heap.insert(6);
	heap.insert(65);
	heap.insert(59);
	heap.insert(49);
	heap.insert(82);
	heap.insert(80);
	heap.insert(96);
	heap.insert(85);
	heap.insert(34);
	heap.insert(41);
	heap.insert(55);
	heap.insert(93);
	heap.insert(5);
	heap.insert(9);
	heap.insert(83);
	heap.insert(71);
	heap.print();
	
	letters.insert("Hallo");
	letters.insert("there");
	letters.print();*/
	
	return 0;
	
}
