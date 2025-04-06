// Copyright 2021 NNTU-CS
int countPairs1(int *arr, int len, int value) {
  int totalPairs = 0;
  for (int idx1 = 0; idx1 < len; ++idx1) {
    for (int idx2 = idx1 + 1; idx2 < len; ++idx2) {
      if (arr[idx1] + arr[idx2] == value) {
        totalPairs++;
      }
    }
  }
  return totalPairs;
}

int countPairs2(int *arr, int len, int value) {
  int totalPairs = 0;
  int upperLimit = len - 1;
  while (upperLimit > 0 && arr[upperLimit] > value) {
    upperLimit--;
  }
  for (int lowerIdx = 0; lowerIdx < len; lowerIdx++) {
    for (int upperIdx = upperLimit;
      upperIdx > lowerIdx; upperIdx--) {
        if (arr[lowerIdx] + arr[upperIdx] == value) {
          totalPairs++;
        }
      }
  }
  return totalPairs;
}

int searchBound(int* dataArr, int startIdx, int endIdx, int searchKey, bool findFirst) {
  int foundPos = -1;
  while (startIdx <= endIdx) {
    int midIdx = startIdx + (endIdx - startIdx) / 2;
    if (dataArr[midIdx] == searchKey) {
      foundPos = midIdx;
      if (findFirst) {
        endIdx = midIdx - 1;
      } else {
        startIdx = midIdx + 1;
      }
    } else if (dataArr[midIdx] < searchKey) {
      startIdx = midIdx + 1;
    } else {
      endIdx = midIdx - 1;
    }
  }
  return foundPos;
}

int countPairs3(int *arr, int len, int value) {
  int pairCounter = 0;
  for (int idx = 0; idx < len; idx++) {
    int diffValue = value - arr[idx];
    int firstOccur = searchBound(arr, idx + 1, len - 1, diffValue, true);
    if (firstOccur != -1) {
      int lastOccur = searchBound(arr, idx + 1, len - 1, diffValue, false);
      pairCounter += (lastOccur - firstOccur + 1);
    }
  }
  return pairCounter;
}
