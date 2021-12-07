#include "../system/system_methods.ipp"
#include "__service.ipp"

template <typename T>
std::vector<int> resize_test(std::vector<T> vector) {
    std::vector<int> v;
    vector.assign(99000000, 1);
    g_start1 = timer();
    vector.resize(50000000);
    vector.reserve(50000000);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    vector.resize(70000000);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    vector.resize(153000000, T());
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    v.push_back(vector[65]);
    g_end1 = timer();
	// {
	// 	std::cout << "size: " << v.size() << std::endl;
	// 	for (unsigned i = 0; i < v.size(); ++i)
	// 		std::cout << v[i] << ' ';
	// 	std::cout << std::endl;
	// }
    return v;
}

template <typename T>
std::vector<int> resize_test(_vector<T> vector) {
    std::vector<int> v;
    vector.assign(99000000, 1);
    g_start2 = timer();
    vector.resize(50000000);
    vector.reserve(50000000);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    vector.resize(70000000);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    vector.resize(153000000, T());
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    v.push_back(vector[65]);
    g_end2 = timer();
	// {
	// 	std::cout << "size: " << v.size() << std::endl;
	// 	for (unsigned i = 0; i < v.size(); ++i)
	// 		std::cout << v[i] << ' ';
	// 	std::cout << std::endl;
	// }
    return v;
}

int main() {

    exit(run_vector_unit_test<int>("resize()", resize_test, resize_test));
}