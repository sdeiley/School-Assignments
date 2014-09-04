/**
 * The second part of Lab 1, within this class is the 
 * code utilizing MergeSort and finding the closest pair
 * of points in a two-dimensional plane using a divide-and-conquer
 * approach.
 * 
 * Completed September 2013
 * Shane Deiley
 * CSE 241: Data Structures and Algorithms
 * Professor Kunal Agarwal
 */

package lab1;


public class ClosestPair {

    public final static double INF = java.lang.Double.POSITIVE_INFINITY;

    /** 
     * Given a collection of points, find the closest pair of point and the
     * distance between them in the form "(x1, y1) (x2, y2) distance"
     *
     * @param pointsByX points sorted in nondecreasing order by X coordinate
     * @param pointsByY points sorted in nondecreasing order by Y coordinate
     * @return Result object containing the points and distance
     */
    
    static Result findClosestPair(XYPoint pointsByX[], XYPoint pointsByY[]) {
       // YOUR CODE GOES HERE
    	XYPoint middleX = pointsByX[(int)Math.floor(((double)pointsByX.length)/2)];
    	
    	//Error Check n<2
    	if(pointsByX.length < 2){
    		return  new Result(pointsByX[0], pointsByX[0], INF);
    	}
    	
    	//Base Case n==2
    	if(pointsByX.length == 2){
    		return new Result(pointsByX[0], pointsByX[1], pointsByX[0].dist(pointsByX[1]));
    	}
    	
    	//Compute XL, YL, XR, YR
    	XYPoint XL[] = new XYPoint[(int)Math.floor(((double)pointsByX.length)/2)];
    	XYPoint YL[] = new XYPoint[(int)Math.floor(((double)pointsByX.length)/2)];
    	XYPoint XR[] = new XYPoint[pointsByX.length - (int)Math.floor(((double)pointsByX.length)/2)];
    	XYPoint YR[] = new XYPoint[pointsByX.length - (int)Math.floor(((double)pointsByX.length)/2)];
    	
    	// XL and XR by taking sorted arrays and copying their halves
    	for(int i = 0; i < (int)Math.floor(((double)pointsByX.length)/2); i++){
    		XL[i] = pointsByX[i];
    	}
    	
    	for(int i = 0; i < (int)Math.ceil(((double)pointsByX.length)/2); i++){
    		XR[i] = pointsByX[i + (int)Math.floor(((double)pointsByX.length)/2)];
    	}
    	
    	// Sorts through Y arrays by comparing to first term in XR
    	int countL = 0;
    	int countR = 0;
    	for(int i = 0; i < pointsByY.length; i++){
    		if( pointsByY[i].isLeftOf(XR[0]) ){
    			YL[countL] = pointsByY[i];
    			countL++;
    		} else {
    			YR[countR] = pointsByY[i];
    			countR++;
    		}
    	}
    	
    	//Recursively run halves
    	Result leftMin = findClosestPair(XL, YL);
    	
    	Result rightMin = findClosestPair(XR, YR);
    	
    	Result recursionMin =  new Result(pointsByX[0], pointsByX[1], INF);
    	
    	//Consolidate the Halves Minimum
    	if(leftMin.dist < rightMin.dist){
    			recursionMin = leftMin;
    	}	else	{ 
    			recursionMin = rightMin;
    	}
    	
    	//Conquer - the combine algorithm that checks the
    	//"center lane" of points within a distance recursionMin
    	Result rMin = combine(pointsByY, middleX, recursionMin);
   
        return rMin;
    }
    
    static Result combine(XYPoint pointsByY[], XYPoint middleX, Result recursionMin){
    	double halfSpan = recursionMin.dist;
    	Result absMin = recursionMin;
    	
    	// Find the number of points in the column of width 2*span
    	int pointCountforStrip = 0;
    	for(int i = 0; i < pointsByY.length; i++){
    		if( (abs(pointsByY[i].x - middleX.x) ) <= halfSpan){
    			pointCountforStrip++;
    		}
    	}
    	
    	// Create array yStrip[] with established number pointCountforStrip
    	XYPoint yStrip[] = new XYPoint[pointCountforStrip];
    	int counter = 0;
    	for(int i = 0; i < pointsByY.length; i++){
    		if( (abs(pointsByY[i].x - middleX.x) ) <= halfSpan){
    			yStrip[counter] = pointsByY[i];
    			counter++;
    		}
    	}
    	
    	// Sort through blocks of side length = span to find minimum strip distance
    	for(int i = 0; i < pointCountforStrip; i++){
    		int j = i + 1;
    		
    		// The while loop will not iterate if the distance between any two strip points is <= to the
    		// previous minimum.  Thus this returns the absolute minimum.
    		while( (j < yStrip.length) && (yStrip[j].y - yStrip[i].y <= halfSpan) ){
    			double testDist = yStrip[j].dist(yStrip[i]);
    			if( testDist < halfSpan ){
    				halfSpan = testDist;
    				absMin = new Result(yStrip[i], yStrip[j], halfSpan);
    			}
    			j++;
    		}
    	}
    	
    	// Return the absolute minimum distance
    	return absMin;
    }
    
    static int abs(int x) {
        if (x < 0) {
            return -x;
        } else {
            return x;
        }
    }
}
