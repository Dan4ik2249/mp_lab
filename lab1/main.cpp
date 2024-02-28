#include <iostream>
#include "priority_queue.h"

int main(){
	Queue<int> heap(100);

	for (int i = 1; i < 8; i++) 
		heap.add(i);

	std::cout << "is empty?: " << heap.empty() << std::endl;
	std::cout << "size: " << heap.get_size() << std::endl;
	std::cout << "max item: " << heap.get_max_item() << std::endl;
	heap.outHeap();
	heap.del();
	heap.outHeap();
	return 0;
}
