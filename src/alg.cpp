// Copyright 2021 NNTU-CS
#include <algorithm>
// Реализация с полным перебором всех сумм (O(n^2))
int countPairs1(int *arr, int len, int value) {
    int count = 0;
    for (int i = 0; i < len; ++i) {
        for (int j = i + 1; j < len; ++j) {
            if (arr[i] + arr[j] == value) {
                count++;
            }
        }
    }
    return count;
}

// Реализация с движением с двух концов (O(n))
int countPairs2(int *arr, int len, int value) {
    int count = 0;
    int left = 0;
    int right = len - 1;
    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum == value) {
            if (arr[left] == arr[right]) {
                // Все элементы между left и right одинаковы
                int n = right - left + 1;
                count += n * (n - 1) / 2;
                break;
            } else {
                int left_val = arr[left];
                int right_val = arr[right];
                int left_count = 0;
                int right_count = 0;
                while (left < len && arr[left] == left_val) {
                    left++;
                    left_count++;
                }
                while (right >= 0 && arr[right] == right_val) {
                    right--;
                    right_count++;
                }
                count += left_count * right_count;
            }
        } else if (sum < value) {
            left++;
        } else {
            right--;
        }
    }
    return count;
}

// Вспомогательная функция для бинарного поиска
int binarySearch(int *arr, int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

// Реализация с бинарным поиском (O(n log n))
int countPairs3(int *arr, int len, int value) {
    int count = 0;
    for (int i = 0; i < len; ++i) {
        int target = value - arr[i];
        if (target < arr[i]) {
            continue; // чтобы избежать дублирования пар
        }
        // Ищем первое вхождение target
        int j = std::lower_bound(arr + i + 1, arr + len, target) - arr;
        if (j < len && arr[j] == target) {
            // Нашли хотя бы одно вхождение, теперь ищем последнее
            int last = std::upper_bound(arr + j, arr + len, target) - arr;
            count += last - j;
        }
    }
    return count;
}
