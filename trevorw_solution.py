def max_sub_array(nums):
    # Your implementation goes here
    return max([{"Sum": sum(nums[a: b + 1]), "Subarray Indices": [a, b]} for a in range(len(nums)) for b in range(len(nums)) if a <= b], key=lambda item: item["Sum"])

if __name__ == "__main__":
    nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4]
    print(f"Maximum subarray sum is: {max_sub_array(nums)}")
