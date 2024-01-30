function maxSubArray(nums) {
    let maxSum = Number.MIN_SAFE_INTEGER;
    let currentSum = 0;
    let start = 0;
    let end = -1;
    let tempStart = 0;

    for (let i = 0; i < nums.length; i++) {
        currentSum += nums[i];

        if (currentSum > maxSum) {
            maxSum = currentSum;
            start = tempStart;
            end = i;
        }

        if (currentSum < 0) {
            tempStart = i + 1;
        }
    }

    if (end === -1) {
        let maxElement = Number.MIN_SAFE_INTEGER;
        for (let num of nums) {
            if (num > maxElement) {
                maxElement = num;
            }
        }
        return [maxElement];
    } else {
        return nums.slice(start, end + 1);
    }
}

function maxSubArraySum(arr) {
    let maxSum = 0;
    let currentSum = 0;

    for (let num of arr) {
        currentSum += num;
        if (currentSum > maxSum) {
            maxSum = currentSum;
        }
        if (currentSum < 0) {
            currentSum = 0;
        }
    }

    return maxSum;
}

const nums = [1, -2, 3, 4, -1, 2, 1, -5, 4, 2, -3, 1, 5, -6, 2, 7, -3, 2, 1, -2, 4];
console.log(`Maximum subarray sum is: ${maxSubArraySum(maxSubArray(nums))}`);
console.log(`Maximum subarray is: [${maxSubArray(nums).join(", ")}]`);
