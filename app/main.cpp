#include <iostream>
#include <vector>

// SHESTERIKOV BORIS 6213: 0 2 2

using namespace std;


struct stats{
	size_t comparison_count = 0;
	size_t copy_count = 0;
};


stats bubble_sort(std::vector<int>& vector) {
	stats stats;

	int length = vector.size();
	for (int i = 0; i < length - 1; i++) {
		for (int j = 0; j < length - i - 1; j++) {
			if (vector[j] > vector[j + 1]) {
				int tmp = vector[j];
				vector[j] = vector[j + 1];
				vector[j + 1] = tmp;

				stats.copy_count += 3;
			}
			stats.comparison_count++;
		}
	}
	return stats;
}

std::ostream& operator<<(std::ostream& stream, const stats& stats) {
	stream << "Comparison count: " << stats.comparison_count << std::endl;
	stream << "Copy count: " << stats.copy_count << std::endl;

	return stream;
}

int main(){
	return 0;
}