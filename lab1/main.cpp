#include <iostream>
#include "priority_queue.h"

int main(){
	Queue<int> heap(100);

	for (int i = 0; i < 15; i++) 
		heap.add(i);

	std::cout << heap.empty() << std::endl;
	std::cout << heap.get_size() << std::endl;
	std::cout << heap.get_max_item() << std::endl;
	heap.outHeap();
	return 0;
}
