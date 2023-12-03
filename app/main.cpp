#include <iostream>
#include <vector>
#include <random>
#define SIZE 1000
// SHESTERIKOV BORIS 6213: 0 2 2

using namespace std;

struct stats{
	size_t comparison_count = 0;
	size_t copy_count = 0;

	friend stats operator+(const stats& left, const stats& right);
};

// Оператор + для struct
stats operator+(const stats& left, const stats& right) {
	stats stats;
	stats.comparison_count = left.comparison_count + right.comparison_count;
	stats.copy_count = left.copy_count + right.copy_count;
	return stats;
}

// Генератор сортированного вектора размера n
vector<int> generate_sorted_vector(const int n) {
	vector<int> result;
	for (int i = 0; i < n; ++i) {
		result.push_back(i);
	}
	return result;
}

// Генератор обратно сортированного вектора размера n
vector<int> generate_inverted_vector(const int n) {
	vector<int> result;
	for (int i = n - 1; i >= 0; --i) {
		result.push_back(i);
	}
	return result;
}

// Генератор случайного вектора размера n
vector<int> generate_random_vector(const int n) {
	vector<int> result;
	for (int i = 0; i < n; ++i) {
		result.push_back(rand() % n);
	}
	return result;
}

// Функция сортировки пузырьком
stats bubble_sort(std::vector<int>& arr) {
	stats stats;

	size_t length = arr.size();
	for (size_t i = 0; i < length - 1; i++) {
		for (size_t j = 0; j < length - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(arr[i], arr[j]);
				stats.copy_count += 1;
			}
			stats.comparison_count++;
		}
	}
	return stats;
}

// Функция быстрой сортировки
stats quick_sort(std::vector<int>& arr, int left, int right) {
	stats stats;
	int i = left, j = right;
	int main_element = arr[left];

	while (i <= j) {
		while (arr[i] < main_element) {
			stats.comparison_count++;
			i++;
		}
		while (arr[j] > main_element) {
			stats.comparison_count++;
			j--;
		}
		if (i <= j) {
			swap(arr[i], arr[j]);
			i++;
			j--;

			stats.copy_count += 1;
		}
	}

	if (left < j)
		stats = stats + quick_sort(arr, left, j);
	if (i < right)
		stats = stats + quick_sort(arr, i, right);

	return stats;
}

// Процедура для преобразования в двоичную кучу поддерева с корневым узлом i, что является
// индексом в arr[]. size - размер кучи

void heapify(std::vector<int>& arr, int size, int i, stats& stats)
{
	// Инициализируем наибольший элемент как корень
	size_t largest = i;

	int left = 2 * i + 1; // левый = 2*i + 1
	int right = 2 * i + 2; // правый = 2*i + 2

	// Если левый дочерний элемент больше корня
	if (left < size && arr[left] > arr[largest]) {
		largest = left;
		stats.comparison_count++;
	}

	// Если правый дочерний элемент больше, чем самый большой элемент на данный момент
	if (right < size && arr[right] > arr[largest]) {
		largest = right;
		stats.comparison_count++;
	}

	// Если самый большой элемент не корень
	if (largest != i)
	{
		swap(arr[i], arr[largest]);
		stats.copy_count += 1;
		// Рекурсивно преобразуем в двоичную кучу затронутое поддерево
		heapify(arr, size, largest, stats);
	}
}

// Пирамидальная сортировка
stats heap_sort(std::vector<int>& arr)
{
	stats stats;
	int size = arr.size();

	// Построение кучи (перегруппируем массив)
	for (int i = size / 2 - 1; i >= 0; i--)
		heapify(arr, size, i, stats);

	// Один за другим извлекаем элементы из кучи
	for (int i = size - 1; i >= 0; i--)
	{
		// Перемещаем текущий корень в конец
		swap(arr[0], arr[i]);
		stats.copy_count += 1;
		// вызываем процедуру heapify на уменьшенной куче
		heapify(arr, i, 0, stats);
	}

	return stats;
}

template<class Iterator>
stats bubble_sort(Iterator begin, Iterator end) {
	stats stats;
	for (Iterator i = begin; i != end; ++i)
		for (Iterator j = begin; j < i; ++j) {
			if (*i < *j) {
				std::iter_swap(i, j);
				stats.copy_count += 1;
			}
			stats.comparison_count += 1;
		}
	return stats;
}

template<class Iterator>
stats quick_sort(Iterator begin, Iterator end) {
	stats stats;
	if (end <= begin) return stats;
	Iterator main_element = begin, middle = begin + 1;
	for (Iterator i = begin + 1; i < end; ++i) {
		if (*i < *main_element) {
			std::swap(*i, *middle);
			++middle;
			stats.copy_count += 1;
		}
		stats.comparison_count += 1;
	}
	std::swap(*begin, *(middle - 1));
	stats = stats + quick_sort(begin, middle - 1, stats);
	stats = stats + quick_sort(middle, end, stats);

	return stats;
}

// Вывод для struct
std::ostream& operator<<(std::ostream& stream, const stats& stats) {
	stream << "Comparison count: " << stats.comparison_count << std::endl;
	stream << "Copy count: " << stats.copy_count << std::endl;

	return stream;
}

template<class Iterator>
void heapify(Iterator begin, Iterator end, int i, stats& stats)
{
	size_t largest = i, size = end-begin;

	// Инициализируем наибольший элемент как корень
	size_t left = 2 * i + 1; // левый = 2*i + 1
	size_t right = 2 * i + 2; // правый = 2*i + 2

	// Если левый дочерний элемент больше корня
	if (left < size && *(begin+left) > *(begin+largest)) {
		largest = left;
		stats.comparison_count++;
	}

	// Если правый дочерний элемент больше, чем самый большой элемент на данный момент
	if (right < size && *(begin + right) > *(begin + largest)) {
		largest = right;
		stats.comparison_count++;
	}

	// Если самый большой элемент не корень
	if (largest != i)
	{
		swap(*(begin+i), *(begin+largest));
		stats.copy_count += 1;
		// Рекурсивно преобразуем в двоичную кучу затронутое поддерево
		heapify(begin, end, largest, stats);
	}
}

// Пирамидальная сортировка
template<class Iterator>
stats heap_sort(Iterator begin, Iterator end)
{
	stats stats;
	int size = end - begin;

	// Построение кучи (перегруппируем массив)
	for (int i = size / 2 - 1; i >= 0; i--)
		heapify(begin, end, i, stats);

	// Один за другим извлекаем элементы из кучи
	for (int i = size - 1; i >= 0; i--)
	{
		// Перемещаем текущий корень в конец
		std::swap(*begin, *(begin+i));
		stats.copy_count += 1;
		// вызываем процедуру heapify на уменьшенной куче
		heapify(begin, begin+i, 0, stats);
	}

	return stats;
}

int main() {
	vector<int> vector;
	cout << "-----* SORTED ARRAY *-----" << endl;

	size_t sum_copy = 0, sum_comparison = 0;
	for (int i = 0; i < 100; ++i) {
		srand(i);
		vector = generate_sorted_vector(SIZE);
		stats tmp;
		tmp = bubble_sort(vector);
		sum_copy += tmp.copy_count;
		sum_comparison += tmp.comparison_count;
	}
	cout << "Sort: Bubble sort\nSize Arr: " << SIZE << "\nAverage copy count: " << sum_copy / 100
		<< "\nAverage comprassion count: " << sum_comparison / 100 << endl << endl;

	sum_copy = 0, sum_comparison = 0;
	for (int i = 0; i < 100; ++i) {
		srand(i);
		vector = generate_sorted_vector(SIZE);
		stats tmp = quick_sort(vector, 0, vector.size() - 1);
		sum_copy += tmp.copy_count;
		sum_comparison += tmp.comparison_count;
	}
	cout << "Sort: Quick sort\nSize Arr: " << SIZE << "\nAverage copy count: " << sum_copy / 100
		<< "\nAverage comprassion count: " << sum_comparison / 100 << endl << endl;

	sum_copy = 0, sum_comparison = 0;
	for (int i = 0; i < 100; ++i) {
		srand(i);
		vector = generate_sorted_vector(SIZE);
		stats tmp = heap_sort(vector);
		sum_copy += tmp.copy_count;
		sum_comparison += tmp.comparison_count;
	}
	cout << "Sort: Heap sort\nSize Arr: " << SIZE << "\nAverage copy count: " << sum_copy / 100
		<< "\nAverage comprassion count: " << sum_comparison / 100 << endl << endl;


	cout << "-----* INVERTED ARRAY *-----" << endl;

	sum_copy = 0, sum_comparison = 0;
	for (int i = 0; i < 100; ++i) {
		vector = generate_inverted_vector(SIZE);
		stats tmp = bubble_sort(vector);
		sum_copy += tmp.copy_count;
		sum_comparison += tmp.comparison_count;
	}
	cout << "Sort: Bubble\nSize Arr: " << SIZE << "\nAverage copy count: " << sum_copy / 100
		<< "\nAverage comprassion count: " << sum_comparison / 100 << endl << endl;

	sum_copy = 0, sum_comparison = 0;
	for (int i = 0; i < 100; ++i) {
		vector = generate_inverted_vector(SIZE);
		stats tmp = quick_sort(vector, 0, vector.size() - 1);
		sum_copy += tmp.copy_count;
		sum_comparison += tmp.comparison_count;
	}
	cout << "Sort: Quick sort\nSize Arr: " << SIZE << "\nAverage copy count: " << sum_copy / 100
		<< "\nAverage comprassion count: " << sum_comparison / 100 << endl << endl;

	sum_copy = 0, sum_comparison = 0;
	for (int i = 0; i < 100; ++i) {
		vector = generate_inverted_vector(SIZE);
		stats tmp = heap_sort(vector);
		sum_copy += tmp.copy_count;
		sum_comparison += tmp.comparison_count;
	}
	cout << "Sort: Heap sort\nSize Arr: " << SIZE << "\nAverage copy count: " << sum_copy / 100
		<< "\nAverage comprassion count: " << sum_comparison / 100 << endl << endl;


	cout << "-----* RANDOM ARRAY *-----" << endl;

	sum_copy = 0, sum_comparison = 0;
	for (int i = 0; i < 100; ++i) {
		vector = generate_random_vector(SIZE);
		stats tmp = bubble_sort(vector);
		sum_copy += tmp.copy_count;
		sum_comparison += tmp.comparison_count;
	}
	cout << "Sort: Bubble\nSize Arr: " << SIZE << "\nAverage copy count: " << sum_copy / 100
		<< "\nAverage comprassion count: " << sum_comparison / 100 << endl << endl;

	sum_copy = 0, sum_comparison = 0;
	for (int i = 0; i < 100; ++i) {
		vector = generate_random_vector(SIZE);
		stats tmp = quick_sort(vector, 0, vector.size() - 1);
		sum_copy += tmp.copy_count;
		sum_comparison += tmp.comparison_count;
	}
	cout << "Sort: Quick sort\nSize Arr: " << SIZE << "\nAverage copy count: " << sum_copy / 100
		<< "\nAverage comprassion count: " << sum_comparison / 100 << endl << endl;

	sum_copy = 0, sum_comparison = 0;
	for (int i = 0; i < 100; ++i) {
		vector = generate_random_vector(SIZE);
		stats tmp = heap_sort(vector);
		sum_copy += tmp.copy_count;
		sum_comparison += tmp.comparison_count;
	}
	cout << "Sort: Heap sort\nSize Arr: " << SIZE << "\nAverage copy count: " << sum_copy / 100
		<< "\nAverage comprassion count: " << sum_comparison / 100 << endl << endl;
	return 0;
}