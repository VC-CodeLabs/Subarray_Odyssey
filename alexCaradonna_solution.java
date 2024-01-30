public class alexCaradonna_solution {
    public static int[] maxSubArray(int[] nums) {
        int maxSum = Integer.MIN_VALUE;
        int currentSum = 0;
        int start = 0;
        int end = -1;
        int tempStart = 0;

        for (int i = 0; i < nums.length; i++) {
            currentSum += nums[i];

            if (currentSum > maxSum) {
                maxSum = currentSum;
                start = tempStart;
                end = i;
            }

            if (currentSum < 0) {
                currentSum = 0;
                tempStart = i + 1;
            }
        }

        if (end == -1) {
            int maxElement = Integer.MIN_VALUE;
            for (int num : nums) {
                maxElement = Math.max(maxElement, num);
            }
            return new int[]{maxElement};
        } else {
            return Arrays.copyOfRange(nums, start, end + 1);
        }
    }

    public static void main(String[] args) {
        int[] nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
        int[] maxSubarray = maxSubArray(nums);

        System.out.println("Maximum subarray sum is: " + maxSubArraySum(maxSubarray));
        System.out.print("Maximum subarray is: [");
        for (int i = 0; i < maxSubarray.length; i++) {
            System.out.print(maxSubarray[i]);
            if (i < maxSubarray.length - 1) {
                System.out.print(", ");
            }
        }
        System.out.println("]");
    }

    public static int maxSubArraySum(int[] arr) {
        int maxSum = 0;
        int currentSum = 0;

        for (int num : arr) {
            currentSum = Math.max(num, currentSum + num);
            maxSum = Math.max(maxSum, currentSum);
        }

        return maxSum;
    }
}
