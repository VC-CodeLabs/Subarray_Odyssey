public class jeffr_solution {
    public static int maxSubArray(int[] nums) {
        // kadane's algorithm
        int sub_start = 0, sub_end = nums.length - 1;
        int max_so_far = Integer.MIN_VALUE, max_ending_here = 0;
        for (int i = 0; i < nums.length; i++) {
            max_ending_here += nums[i];
            if (max_so_far < max_ending_here) {
                sub_end = i;
                max_so_far = max_ending_here;
            }
            if (max_ending_here < 0) {
                sub_start = i + 1;
                max_ending_here = 0;
            }
        }

        if( sub_start > sub_end ) {
            sub_start = sub_end;
        }

        System.out.println("Sum = " + max_so_far + " @ [" + sub_start + "]...[" + sub_end + "]");
        
        return max_so_far;
    }

    public static void main(String[] args) {
        int[] nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4}; // == 6 @ [3]...[6]
        // int[] nums = {5, -12, 3, 2, 9, -10, 4}; // == 14 @ [2]...[4]
        // int[] nums = {-2, -3, 4, -1, -2, 1, 5, -3}; // == 7 @ [2]...[6]
        // int[] nums = {-2, -3, 4, -1, -2, 1, 5, -3, 4}; // == 8 @ [2]...[8]
        // int[] nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4, 50}; // == 55 @ [3]...[9]
        // int[] nums = {-2, 1, -3, 4, -1, 2, 1, -6, 4, 50}; // == 54 @ [8]...[9] (-OR- [3]...[9])
        // int[] nums = {-2, 1, -3, 4, -1, 2, 1, -100, 4, 20}; // == 24 @ [8]...[9]
        // int[] nums = {1, 2, 3, -2, 5}; // == 9 (entire array)
        // int[] nums = {-1,-2,-3,-4}; // == -1 @ [0]...[0]
        // int[] nums = {-3,-4,-1,-2}; // == -1 @ [2]...[2]
        // int[] nums = {-3,-2,-1,5,-10,10}; // == 10 @ [5]...[5]
        // int[] nums = {-3,-2,-1,20,-10,10}; // == 20 @ [3]...[3]
        // int[] nums = {-3,-2,-1,20,-10,11}; // == 21 @ [3]...[5]
        // int[] nums = {-2147,0,2147}; // == 2147 @ [1]...[2]
        // int[] nums = {2147,0,-2147}; // == 2147 @ [0]...[0]
        System.out.println("Maximum subarray sum is: " + maxSubArray(nums));
    }
}
