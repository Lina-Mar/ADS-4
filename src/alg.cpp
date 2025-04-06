// Copyright 2021 NNTU-CS
// Вспомогательная функция для бинарного поиска
int binarySearch(int *arr, int left, int right, int value) {
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (arr[mid] == value) {
      return mid;
    }
    if (arr[mid] < value) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return -1;
}

int countPairs1(int *arr, int len, int value) {
  int count = 0;
  for (int i = 0; i < len - 1; i++) {
    for (int j = i + 1; j < len; j++) {
      if (arr[i] + arr[j] == value) {
        count++;
      }
    }
  }
  return count; 
}

int countPairs2(int *arr, int len, int value) {
  int count = 0;
  int left = 0;
  int right = len - 1;
  while (left < right) {
    int sum = arr[left] + arr[right];
    if (sum == value) {
      if (arr[left] == arr[right]) {
        int num = right - left + 1;
        count += num * (num - 1) / 2;
        break;
      }
      int left_val = arr[left];
      int left_count = 0;
      while (arr[left] == left_val && left < right) {
        left++;
        left_count++;
      }
      int right_val = arr[right];
      int right_count = 0;
      while (arr[right] == right_val && right >= left) {
        right--;
        right_count++;
      }
      count += left_count * right_count;
    }
    else if (sum < value) {
      left++;
    }
    else {
      right--;
    }
  }
  return count;
}

int countPairs3(int *arr, int len, int value) {
  int count = 0;
  for (int i = 0; i < len - 1; i++) {
    int complement = value - arr[i];
    int pos = binarySearch(arr, i + 1, len - 1, complement);
    if (pos != -1) {
      count++;
      int j = pos - 1;
      while (j > i && arr[j] == complement) {
        count++;
        j--;
      }
      j = pos + 1;
      while (j < len && arr[j] == complement) {
        count++;
        j++;
      }
    }
  }
  return count;
}
