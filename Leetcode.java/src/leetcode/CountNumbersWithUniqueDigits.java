package leetcode;

import java.util.Arrays;

/**
Counts the numbers with unique digits from [0, 10**n).
 */
public class CountNumbersWithUniqueDigits {
	private long cap;
	private int[] stash;
	
	public CountNumbersWithUniqueDigits()
	{
		stash = new int[11];
		Arrays.fill(stash, -1);
	}
	
    public int countNumbersWithUniqueDigits(int n) {
    	//return solveByBacktracking(n);
    	//return solveByCounting(n);
    	return solveByDP(n);
    }
    
    private int solveByCounting(int n)
    {
    	if (n == 0)
    		return 1;
    	n = Math.min(n, 10);
    	
		// For single digit, we have 10 numbers with unique digits
		int totalUnique = 10;
		// After first digit, the choice for first digit is only 9 digits,
		int prevMultiplier = 9;
		for (int i = 1; i < n; i++) {
			prevMultiplier *= (10 - i);
			totalUnique += prevMultiplier;
		}
		return totalUnique;
    }
    
    private int solveByDP(int n)
    {
    	if (n == 0)
    		return 1;
    	
    	n = Math.min(n,  10);
    	if (stash[n] == -1) {
	    	// stash[k] = number of numbers with up to k unique digits
	    	stash[1] = 10;
			int total = 9; // number of ways to choose a nonzero leading digit
	    	for (int i = 1; i < 10; ++i) {
	    		// number of ways to choose the next digit
	    		total *= (10 - i);
	    		
	    		// here, total counts number of numbers with exactly (i+1) unique digits
	    		stash[i+1] = stash[i] + total;
	    	}
    	}
    	
    	return stash[n];
    }
    
    private int solveByBacktracking(int n) {
    	n = Math.min(n, 10);
    	if (stash[n] == -1) {
    		cap = (long) Math.pow(10, n);
    		stash[n] = doCount(n, 0, 0, 0);
    	}
    	return stash[n];
    }
    
    private int doCount(int n, int i, long num, int mask) {
    	if (num < 0L || num > cap) {
    		return 0;
    	}
    	if (i == n) {
    		return 1;
    	}
    	int total = 1;
    	for (int k = (i == 0)? 1 : 0; k < 10; ++k) {
    		if ((mask & (1 << k)) == 0) {
    			total += doCount(n, i + 1, 10L * num + k, mask | (1 << k));
    		}
    	}
    	return total;
    }
    
	public static void main(String[] args) {
		CountNumbersWithUniqueDigits sol = new CountNumbersWithUniqueDigits();
		for (int i = 0; i <= 11; ++i)
			System.out.println(sol.countNumbersWithUniqueDigits(i));
	}
}
