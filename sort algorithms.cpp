
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
int getQuickSortMid(int arr[], int length)
{
	int value = arr[0], id = 0;
	int left = 0, right = length - 1;
	while (left < right) {
		while (left < right && arr[right] > value)
			--right;
		arr[id] = arr[right];
		id = right;
		while (left < right && arr[left] <= value)
			++left;
		arr[id] = arr[left];
		id = left;
	}
	arr[id] = value;
	return id;
}
void quickSortMain(int arr[], int length)
{
	if (length <= 1) return;
	int mid = getQuickSortMid(arr, length);
	quickSortMain(arr, mid);
	quickSortMain(arr + mid + 1, length - mid - 1);
}

template<class T>
void selectSort(T arr[], int n)
{
	for (int i = n - 1; i >= 1; i--) {
		int max = i;
		for (int j = 0; j < i; j++) {
			if (arr[j] > arr[max]) {
				max = j;
			}
		}
		std::swap(arr[i], arr[max]);
	}
}

void bubbleSort(int arr[], int n)
{
	for (int i = n-1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (arr[j] > arr[j + 1]) {
				arr[j] = arr[j] ^ arr[j + 1];
				arr[j + 1] = arr[j] ^ arr[j + 1];
				arr[j] = arr[j] ^ arr[j + 1];
			}
		}
	}
}

void insertSort(int arr[], int n)
{
	for (int i = 1; i < n; i++) {
		int  value = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j] > value) {
			arr[j + 1] = arr[j];
			--j;
		}
		arr[j+1] = value;

	}
}

void shellSort(int arr[], int n)
{
	int step = n / 2;
	for (; step >= 1; step = step / 2) {
		for (int i = step; i < n; i++) {
			
				int value = arr[i];
				int j = i - step;
				for(; j >= 0 && arr[j] > value; j = j-step) {
					arr[j + step] = arr[j];
					//j = j - step; (while)
				}
				arr[j + step] = value;
		}
	}
}

template <typename T>
void mergeSortRecursive(T arr[], T res[], int start, int end);

template < typename T>
void mergeSortRecursive<T>(T arr[], T res[], int start, int end)
{
	if (end <= start) return;
	int mid =  ((end - start)>>1)+start;//运算符优先级大于位移
	mergeSortRecursive(arr, res, start, mid);
	mergeSortRecursive(arr, res, mid + 1, end);
	int i = start, j = mid + 1, k = start;
	while (i <= mid && j <= end) {
		res[k++] = arr[i] < arr[j] ? arr[i++] : arr[j++];
	}
	while (i <= mid) {
		res[k++] = arr[i++];
	}
	while (j <= end) {
		res[k++] = arr[j++];
	}
	for (k = start; k <= end; k++)
		arr[k] = res[k];
}
template <class T>
void mergeSort(T arr[], const int n)
{
	T* res = new T[n];
	mergeSortRecursive<T>(arr, res, 0, n-1);
	delete []res;
}

template<typename T>
void heapSortMain(T arr[], int n, int id)
{
	int value = arr[id];
	int target = id;
	int left = id * 2 + 1;
	for (; left < n; left = left * 2 + 1) {
		if (left + 1 < n && arr[left] < arr[left + 1])
			left++;
		if (arr[left] <= value) break;
		//std::swap(arr[left], arr[target]);
		arr[target] = arr[left];
		target = left;
	}
	arr[target] = value;
}
template<typename T>
void HeapSort(T arr[], int n)
{
	for (int i = (n - 1) / 2; i >= 0; i--) {
		heapSortMain<T>(arr, n, i);
	}
	for (int j = n - 1; j >= 1; j--) {
		std::swap(arr[0], arr[j]);
		heapSortMain<T>(arr, j, 0);
	}
}
template<typename T>
void countSort(T arr[], int n)
{
	int count[100];
	for (int i = 0; i < 100; i++)
		count[i] = 0;
	for (int j = 0; j < n; j++)
		count[arr[j]]++;
	for (int i = 1; i < 100; i++)
		count[i] += count[i - 1];
	int k = 99;
	for (int i = n-1; i >= 0; i--) {
		while(k >= 0 && count[k] <= count[k - 1]) k--;
		
		arr[--count[k]] = k;
	}

}

template <class T>

void radixSort(T arr[], int n)
{
	int max = arr[0];
	for (int i = 1; i < n; i++) {
		if (arr[i] > max) max = arr[i];
	}
	int num = 1;
	T* tmp = new T[n];
	int count[10];
	while (max % 10 > 0) {
		max = max / 10;
		
		for (int i = 0; i < 10; i++) count[i] = 0;

		for (int j = 0; j < n; j++) count[arr[j]/num%10]++;
		for (int i = 1; i < 10; i++) count[i] += count[i - 1];

		for (int j = n-1; j >= 0; j--)
			tmp[--count[arr[j] / num%10]] = arr[j];
		for (int j = 0; j < n; j++)
			arr[j] = tmp[j];

		num = num * 10;
	}
	delete []tmp;
}
int main(int argc, char* argv[]) {
	int arr[] = { 12, 33,  4, 89, 0, 4, 77, 99, 21, 1, 89 };
	int n = sizeof(arr) / sizeof(int);
	//quickSortMain(arr, sizeof(arr) / sizeof(int));
	//bubbleSort(arr, n);
	//insertSort(arr, n);
	//shellSort(arr, n);
	//mergeSort<int>(arr, n);
	//selectSort(arr, n);
	//HeapSort<int>(arr, n);
	//countSort(arr, n);
	radixSort(arr, n);
	for (int i = 0; i < n; i++) {
		printf("%d  ", arr[i]);
	}
	system("pause");
	return 0;
}