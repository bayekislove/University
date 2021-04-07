#include<iostream>
#include<thread>

template<typename T, int size>
void print(T const(& array)[size]) 
{
	std::cout << "[";
  	for(int i=0; i < size - 1; i++)
	{
		std::cout << array[i] << ", ";
	}
	std::cout << array[size - 1] << "]" << std::endl;
}

template<typename T>
void merge(T arr[], int l, int m, int r)
{
    int x = m - l + 1;
    int y = r - m;
 
    int left_tab[x], right_tab[y];
 
    for (int i = 0; i < x; i++)
        left_tab[i] = arr[l + i];
    for (int j = 0; j < y; j++)
        right_tab[j] = arr[m + 1 + j];
 

    int i = 0;
    int j = 0;
 
    int k = l;
 
    while (i < x && j < y) {
        if (left_tab[i] <= right_tab[j]) {
            arr[k] = left_tab[i];
            i++;
        }
        else {
            arr[k] = right_tab[j];
            j++;
        }
        k++;
    }

    while (i < x) {
        arr[k] = left_tab[i];
        i++;
        k++;
    }
 
    while (j < y) {
        arr[k] = right_tab[j];
        j++;
        k++;
    }
}

template<typename T>
void merge_sort(T arr[], int l, int r){
    if(l >= r) return;

    int m = ( l + r - 1) / 2;

    std::thread thread1{ merge_sort<T>, arr, l, m };
	thread1.join();

    std::thread thread2{ merge_sort<T>, arr, m+1, r };
	thread2.join();

    std::thread thread3{ merge<T>, arr, l, m, r };
    thread3.join();
}

int main()
{
    int arr[5]{1, 2, 5, 0, 3};
    merge_sort<int>(arr, 0, 5);
    print<int>(arr);
}