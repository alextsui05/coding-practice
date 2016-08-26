package leetcode;

import static org.junit.Assert.*;

import org.junit.Test;

public class NumArrayTest {

	@Test
	public void testSumRange() {
		int[] input = new int[] { -2, 0, 3, -5, 2, -1 };
		NumArray na = new NumArray(input);
		assertEquals(1, na.sumRange(0,  2));
		assertEquals(-1, na.sumRange(2,  5));
		assertEquals(-3, na.sumRange(0,  5));
	}

}
