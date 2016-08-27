package leetcode;
import java.util.*;

public class NumArrayN2 {
	private ArrayList<Integer> nums;
	private ArrayList<ArrayList<Integer>> sums;
	
	public NumArrayN2(int[] nums) {
		this.nums = Arrays.stream(nums).boxed()
			.collect(ArrayList<Integer>::new, 
				ArrayList<Integer>::add,
				ArrayList<Integer>::addAll);
		memoize();
	}
	
	public int sumRange(int i, int j) {
		return sumRangeMemoize(i, j);
	}
	
	private void memoize( ) {
		//sums = new ArrayList<ArrayList<Integer>>(nums.size());
		sums = new ArrayList<ArrayList<Integer>>();
		
		for (int i = 0; i < nums.size(); ++i) {
			sums.add(new ArrayList<>());
			sums.get(i).add(nums.get(i));
		}
		for (int offset = 1; offset < nums.size(); ++offset) {
			for (int i = 0; i < nums.size(); ++i) {
				if (i + offset < nums.size()) {
					int entry = sums.get(i).get(offset - 1)
						+ nums.get(i + offset);
					sums.get(i).add(entry);
				}
			}
		}
	}
	
	private int sumRangeMemoize(int i, int j) {
		int res = sums.get(i).get(j - i);
		return res;
	}
	
	private int sumRangeNaive(int i, int j) {
		int res = 0;
		for (int it = i; it <= j; ++it) {
			res += this.nums.get(it);
		}
		return res;
	}
}