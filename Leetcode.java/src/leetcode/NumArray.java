package leetcode;
import java.util.*;
import java.util.stream.Collectors;

public class NumArray {
	private ArrayList<Integer> nums;
	private ArrayList<Integer> forwardSums;
	private ArrayList<Integer> backwardSums;
	private int total;
	
	public NumArray(int[] nums) {
		this.nums = Arrays.stream(nums).boxed()
			.collect(ArrayList<Integer>::new, 
				ArrayList<Integer>::add,
				ArrayList<Integer>::addAll);
		memoize();
	}
	
	private void memoize( )	{
		total = nums.stream().mapToInt(Integer::intValue).sum();
		forwardSums = new ArrayList<>();
		backwardSums = new ArrayList<>();
		forwardSums.add(0);
		backwardSums.add(0);
		int forward = 0;
		int backward = 0;
		for (int i = 0; i < nums.size(); ++i) {
			forward += nums.get(i);
			backward += nums.get(nums.size() - 1 - i);
			forwardSums.add(forward);
			backwardSums.add(backward);
		}
		Collections.reverse(backwardSums);
	}
	
	public int sumRange(int i, int j) {
		return total - forwardSums.get(i) - backwardSums.get(j+1);
	}
}