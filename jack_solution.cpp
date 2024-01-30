#include <iostream>
#include <vector>

std::string maxSubArray(std::vector<int>& input) {
    long theMax = -2147, tempSum = 0;
    int start = 0, end = 0, tempStart = 0;
    for (int i = 0; i < input.size(); i++) {
        tempSum += input[i];
        if (tempSum > theMax) {
            theMax = tempSum;
            start = tempStart;
            end = i;
        }
        if (tempSum < 0) {
            tempSum = 0;
            tempStart = i + 1;
        }
    }
    return std::to_string(theMax) + ", Subarray Indices = [" + std::to_string(start) + "," + std::to_string(end) + "]";
}

int main() {
    std::vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    std::cout << "Maximum subarray sum is: " << maxSubArray(nums) << std::endl;
    return 0;
}
