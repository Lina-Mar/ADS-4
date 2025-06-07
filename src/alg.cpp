// Copyright 2021 NNTU-CS
#include <algorithm>

// 1. Полный перебор (O(n²))
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

// 2. Два указателя (O(n))
int countPairs2(int *arr, int len, int value) {
    int count = 0;
    int left = 0;
    int right = len - 1;

    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum == value) {
            if (arr[left] == arr[right]) {
                // Все оставшиеся элементы одинаковы
                int n = right - left + 1;
                count += n * (n - 1) / 2;
                break;
            }
            // Подсчитываем количество дубликатов слева и справа
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
        } else if (sum < value) {
            left++;
        } else {
            right--;
        }
    }
    return count;
}

// 3. Бинарный поиск (O(n log n))
int countPairs3(int *arr, int len, int value) {
    int count = 0;
    for (int i = 0; i < len; ++i) {
        int target = value - arr[i];
        if (target < arr[i]) {
            continue; // избегаем дублирования пар
        }
        // Ищем первое вхождение target
        int left = i + 1;
        int right = len - 1;
        int first_pos = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] >= target) {
                first_pos = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        if (first_pos != -1 && arr[first_pos] == target) {
            // Ищем последнее вхождение target
            left = first_pos;
            right = len - 1;
            int last_pos = first_pos;
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (arr[mid] <= target) {
                    last_pos = mid;
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            count += last_pos - first_pos + 1;
        }
    }
    return count;
}
