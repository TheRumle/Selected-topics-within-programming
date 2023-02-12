#include <iostream>
#include <vector>
#include <cstring>
#include <chrono>

using namespace std::chrono;



void swap_ends(int nums[], int size);

void swap_ends(std::vector<int> &nums);

void measure_static();

void measure_stack();

void measure_dynamic();

void swap_ends_str_dyn();

void swap_ends_str_stat();

void exersice1();

int main() {
    exersice1();
    return 0;
}

void swap_ends(int nums[], int size) {
    for (int i = size / 2 - 1, j = size - 1; i >= 0; --i, --j)
        std::swap(nums[i], nums[j]);


    for (int i = 0; i < size; ++i) {
        std::cout << nums[i];
    }
}

void swap_ends(std::vector<int> &nums) {
    for (int i = nums.size() / 2 - 1, j = nums.size() - 1; i >= 0; --i, --j) {
        std::swap(nums[i], nums[j]);
    }

    for (int i = 0; i < nums.size(); ++i) {
        std::cout << nums[i];
    }

}

void measure_static() {
    static constexpr int arr_size = 10'000'000;

    std::cout << "Static alloc\n";
    auto t0 = high_resolution_clock::now();
    static int c_arr[arr_size];
    swap_ends(c_arr, arr_size);
    auto t1 = high_resolution_clock::now();
    std::cout << duration<double, std::milli>(t1 - t0).count() << "ms for array\n";


    t0 = high_resolution_clock::now();
    static std::vector<int> vec(arr_size);
    swap_ends(vec);
    t1 = high_resolution_clock::now();
    std::cout << duration<double, std::milli>(t1 - t0).count() << "ms for vector\n";
}

void measure_stack() {
    constexpr int arr_size = 10'00'00;

    std::cout << "Stack alloc\n";
    auto t0 = high_resolution_clock::now();
    int c_arr[arr_size];
    swap_ends(c_arr, arr_size);
    auto t1 = high_resolution_clock::now();
    std::cout << duration<double, std::milli>(t1 - t0).count() << "ms for array\n";


    t0 = high_resolution_clock::now();
    std::vector<int> vec(arr_size);
    swap_ends(vec);
    t1 = high_resolution_clock::now();
    std::cout << duration<double, std::milli>(t1 - t0).count() << "ms for vector\n";
}


void measure_dynamic() {
    constexpr int arr_size = 10'000'000;

    std::cout << "Heap alloc\n";
    auto t0 = high_resolution_clock::now();
    auto c_arr = new int[arr_size];
    swap_ends(c_arr, arr_size);
    auto t1 = high_resolution_clock::now();
    std::cout << duration<double, std::milli>(t1 - t0).count() << "ms for array\n";


    t0 = high_resolution_clock::now();
    auto *vec = new std::vector<int>(arr_size);
    swap_ends(*vec);
    t1 = high_resolution_clock::now();
    std::cout << duration<double, std::milli>(t1 - t0).count() << "ms for vector\n";
    delete vec;
}

void swap_ends_str_dyn() {
    constexpr int size = 10;
    auto arr = new int[size]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto t0 = high_resolution_clock::now();

    int half[size / 2];
    memcpy(half, &arr[size / 2], sizeof half); //flip using memcpy
    memcpy(&arr[size / 2], arr, sizeof half);
    memcpy(arr, half, sizeof half);
    delete[] arr;

    auto t1 = high_resolution_clock::now();
    std::cout << duration<double, std::milli>(t1 - t0).count() << "ms for dynamic\n";

}


void swap_ends_str_stat() {
    auto t0 = high_resolution_clock::now();

    static constexpr int size = 10;
    static int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    static int half[size / 2];
    memcpy(half, &arr[size / 2], sizeof half); //flip using memcpy
    memcpy(&arr[size / 2], arr, sizeof half);
    memcpy(arr, half, sizeof half);

    auto t1 = high_resolution_clock::now();
    std::cout << duration<double, std::milli>(t1 - t0).count() << "ms for static\n";
}

void exersice1() {
    measure_stack();
    measure_static(); // They are equivalent in speed (almost). Stack is not large.
    measure_dynamic();
    swap_ends_str_dyn();
    swap_ends_str_stat();
}
