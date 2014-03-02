/**
 * The Goal of Lab 1 was to code a stable version
 * of MergeSort and utilize it in a Divide and Conquer
 * Algorithm that finds the closest pair of points
 * 
 * This file contains the code for MergeSort
 */

package lab1;

public class Sort {

    //================================= sort =================================
    //
    // Input: array A of XYPoints refs 
    //        lessThan is the function used to compare points
    //
    // Output: Upon completion, array A is sorted in nondecreasing order
    //         by lessThan.
    //
    //=========================================================================
    public static void msort(XYPoint[] A, Comparator lessThan) {
    	helpmsort(A, 0, A.length-1, lessThan);
    }
    
    public static void helpmsort(XYPoint[] A, int indexStart, int indexFinish, Comparator lessThan){
    	if(indexStart < indexFinish){
    		int middleIndex = (int)Math.floor((indexFinish + indexStart)/2);
    		helpmsort(A, indexStart, middleIndex, lessThan);
    		helpmsort(A, middleIndex + 1, indexFinish, lessThan);
    		merge(A, indexStart, middleIndex, indexFinish, lessThan);
    	}
    }
    
    public static void merge(XYPoint[] A, int indexStart, int middleIndex, int indexFinish, Comparator lessThan){
    	// Define Split Sizes
    	int leftSize = middleIndex - indexStart + 1;
    	int rightSize = indexFinish - middleIndex;
    	
    	// Establish arrays of size + 1 for sentinels
    	XYPoint left[] = new XYPoint[leftSize + 1];
    	XYPoint right[] = new XYPoint[rightSize + 1];
    	
    	for(int i = 0; i < leftSize; i++){
    		left[i] = A[indexStart + i];	
    	}
    	for(int j = 0; j < rightSize; j++){
    		right[j] = A[middleIndex + 1 + j];
    	}
    	// These are the sentinels (to ensure that when one "side" runs out, the other side will cycle through inputting values
    	XYPoint leftSentinel = new XYPoint((int)java.lang.Double.POSITIVE_INFINITY,(int)java.lang.Double.POSITIVE_INFINITY);
    	XYPoint rightSentinel = new XYPoint((int)java.lang.Double.POSITIVE_INFINITY,(int)java.lang.Double.POSITIVE_INFINITY);
    	
    	left[leftSize] =  leftSentinel;
    	right[rightSize] = rightSentinel;
    	
    	// Merges sides
    	int i = 0; int j = 0;
    	for(int k = indexStart; k < indexFinish + 1; k++){
    		if(lessThan.comp(left[i], right[j])){
    			A[k] = left[i];
    			i++;
    		} else {
    			A[k] =right[j];
    			j++;
    		}
    	}
    }
}
