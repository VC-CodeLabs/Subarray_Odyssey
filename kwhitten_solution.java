import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.Random;
import java.util.stream.IntStream;
import java.util.stream.Stream;

class Main {
    public static String maxSubArray(int[] nums) {
        class SubarrayStats {
            int startingIndex;
            int endingIndex;
            int sum;

            SubarrayStats(int startingIndex, int endingIndex, int sum) {
                this.startingIndex = startingIndex;
                this.endingIndex = endingIndex;
                this.sum = sum;
            }
        }
        List<SubarrayStats> contiguousSubarrays = new ArrayList<>();
        // Create an array of SubarrayStats that contains the sum, startingIndex, and endingIndex of
        // every possible contiguous subarray. We'll skip any arrays that would begin with an element less than 1,
        // and we won't include trailing elements less than 1.
        IntStream.range(0, nums.length).forEach(startIndex -> {
            if (nums[startIndex] > 0) {
                IntStream.range(startIndex, nums.length).forEach(endIndex -> {
                    if (nums[endIndex] > 0) {
                        contiguousSubarrays.add(new SubarrayStats(startIndex, endIndex, Arrays.stream(Arrays.copyOfRange(nums, startIndex, endIndex + 1)).sum()));
                    }
                });
            }
        });

        // for (int startIndex = 0; startIndex < nums.length; startIndex++) {
        //     if (nums[startIndex] > 0) {
        //         for(int endIndex = startIndex; endIndex < nums.length; endIndex++) {
        //             if (nums[endIndex] > 0) {
        //                 int[] subarray = Arrays.copyOfRange(nums, startIndex, endIndex + 1);
        //                 contiguousSubarrays.add(new SubarrayStats(startIndex, endIndex, Arrays.stream(subarray).sum()));
        //             }
        //         }
        //     }
        // }

        SubarrayStats maxSubarray = contiguousSubarrays.stream()
        .max(Comparator.comparing(s -> s.sum))
        .orElse(new SubarrayStats(0, 0, 0));

        return String.format("%2d. Beginning Index: %2d, Ending Index: %2d. Array length was: %2d", maxSubarray.sum, maxSubarray.startingIndex, maxSubarray.endingIndex, nums.length);
    }

    public static void main(String[] args) {
        List<int[]> testArrays = List.of(
            new int[]{-2, 1, -3, 4, -1, 2, 1, -5, 4},
            new int[]{5, -12, 3, 2, 9, -10, 4},
            new Random().ints((long) Math.pow(10, 6), -2147, 2147).toArray()
        );

        for (int[] i : testArrays){
            System.out.println("Maximum subarray sum is: " + maxSubArray(i));
        }
    }
}
