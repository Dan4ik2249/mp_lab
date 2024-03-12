#include <iostream>
#include <cstring>

template<typename T>
class Queue{
	private:
		T *mass;
		int MaxSize;
		int HeapSize;
	private:
		void swap(T &x, T &y){
			T tmp = x;
			x = y;
			y = tmp;
		}

		void heap_sort(int ind){
			int right = 2*ind + 2;
			int left = 2*ind + 1;
			
			if (right < HeapSize){
				if(mass[right]>mass[left] && mass[right] > mass[ind]){
					swap(mass[right], mass[ind]);
					heap_sort(right);
				}
			}
			if (left < HeapSize){
				if (mass[right]<mass[left] && mass[left] > mass[ind]){
					swap(mass[left], mass[ind]);
					heap_sort(left);
				}	
			}

			/*if (right < HeapSize){
				if (mass[right] > mass[ind]){
					swap(mass[right], mass[ind]);
					heap_sort(right);
				}
			}
			if (left < HeapSize){
				if (mass[left] > mass[ind]){
					swap(mass[left], mass[ind]);
					heap_sort(left);
				}
			}*/
		}
		void extend_mass(){
			T *temp = new T[MaxSize*2+10];
			memcpy(temp, mass, HeapSize);
			mass = temp;
		}

	public:
		Queue(int MaxSize){
			this->MaxSize = MaxSize;
			mass = new T[MaxSize];
			HeapSize = 0;
		}
	
		void outHeap() {
			for (int i = 0; i < HeapSize; i++) { std::cout << mass[i] << " ";}
			std::cout << std::endl;
		}

		void add(T item){
			mass[HeapSize] = item;
			int i = HeapSize;
			int par_ind = (HeapSize - 1)/2;

			if (HeapSize == MaxSize) extend_mass();

			while(par_ind >= 0 && i > 0){
				if (mass[i] > mass[par_ind]){
					swap(mass[i], mass[par_ind]);
					i = par_ind;
					par_ind = (i-1)/2;
				}
				else break;
			}
			HeapSize++;
		}

		T del(){
			T item = mass[0];
			mass[0] = mass[HeapSize-1];
			HeapSize--;
			heap_sort(0);
			return item;
		}

		int empty() {return (HeapSize==0)?1:0;}
		
		int get_size() {return HeapSize;}

		int get_max_item() {return (HeapSize==0)?0:mass[0];}

		~Queue(){
			HeapSize = 0;
			MaxSize = 0;
			delete [] mass;
			mass = NULL;
		}

};
