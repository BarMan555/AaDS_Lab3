#include <iostream>
#include <vector>

// SHESTERIKOV BORIS 6213: 0 2 2

using namespace std;


struct stats{
	size_t comparison_count = 0;
	size_t copy_count = 0;
};


stats bubble_sort(std::vector<int>& arr) {
	stats stats;

	int length = arr.size();
	for (int i = 0; i < length - 1; i++) {
		for (int j = 0; j < length - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;

				stats.copy_count += 3;
			}
			stats.comparison_count++;
		}
	}
	return stats;
}

// Функция быстрой сортировки
stats quick_sort(vector<int>& arr, int left, int right) {
	static stats stats;
	int i = left, j = right;
	int tmp;
	int main_element = arr[left];

	do {
		while (arr[i] < main_element)
			i++;
		while (arr[j] > main_element)
			j--;
		if (i <= j) {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;

			stats.copy_count += 3;
		}

		stats.comparison_count += 4;
	} while (i <= j);

	if (left < j)
		quick_sort(arr, left, j);
	if (i < right)
		quick_sort(arr, i, right);

	return stats;
}

std::ostream& operator<<(std::ostream& stream, const stats& stats) {
	stream << "Comparison count: " << stats.comparison_count << std::endl;
	stream << "Copy count: " << stats.copy_count << std::endl;

	return stream;
}

int main(){
	std::vector<int> vec {0, 2, 1, 3, 4, 6, 5, 7 };
	cout << quick_sort(vec, 0, vec.size() - 1) << endl;

	for (int i = 0; i < vec.size(); i++) {
		cout << vec[i] << " ";
	}


	return 0;
}