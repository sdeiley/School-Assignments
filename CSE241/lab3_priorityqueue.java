/**
 * The goal of Lab 3 was to implement a Priority Queue
 * of an arbitrary type T using binary heaps.  
 * 
 * Completed December 2013
 * Shane Deiley
 * CSE 241: Data Structures and Algorithms
 * Professor Kunal Agarwal
 */

package lab3;

import java.util.ArrayList;

/**
 * A priority queue class
 */
class PriorityQueue<T> {
	public ArrayList<PQNode<T>> queue;
	public int size;

    /**
     * Constructor
     */
    public PriorityQueue() {
    	ArrayList<PQNode<T>> queue = new ArrayList<PQNode<T>>();
    	this.queue = queue;
    	int size = 0; 
    	this.size = size;
    }

    /**
     * @return true iff the queue is empty.
     */
    public boolean isEmpty() {
    	if(size == 0){
    		return true;
    	} else {
    		return false;
    	}
    }

    /**
     * Insert a (key, value) pair into the queue.
     *
     * @return a Handle to this pair so that we can find it later.
     */
    Handle insert(int key, T value) {
    	// Make PQNode to insert
    	size++;
    	Handle h = new Handle(size-1, this);
    	PQNode<T> toInsert = new PQNode<T>(Integer.MAX_VALUE, value, h);
    	
    	queue.add(toInsert);
    	decreaseKey(h, key);
    	
    	return h;
    }

    /**
     * @return the min key in the queue.
     */
    public int min() {
       return (queue.get(0)).key;
    }

    /**
     * Find and remove the smallest (key, value) pair in the queue.
     *
     * @return the value associated with the smallest key
     */
    public T extractMin() {
    	// Check size
    	if(this.isEmpty()){
    		return null;
    	}
    	
    	T value = queue.get(0).value;
    	swap(queue.get(0), queue.get(size-1));
    	
    	queue.get(size-1).handle.index = -1;
    	queue.get(size-1).handle = null;
    	queue.remove(size-1); size--;
    	
    	minHeapify(queue.get(0).handle);
    	
    	return value;
    }


    /**
     * Decrease the key to the newKey associated with the Handle.
     *
     * If the pair is no longer in the queue, or if its key <= newKey,
     * do nothing and return false.  Otherwise, replace the key with newkey,
     * fix the ordering of the queue, and return true.
     *
     * @return true if we decreased the key, false otherwise.
     */
    public boolean decreaseKey(Handle h, int newKey) {
    	if(h.index == -1 || h.equals(null)){
    		return false;
    	}
    	if(newKey >= handleGetKey(h)){
    		return false;	
    	}
    
    	queue.get(h.index).key = newKey;
    	while(h.index > 0 && queue.get(h.parentIndex()).key > queue.get(h.index).key){
    		swap(queue.get(h.parentIndex()), queue.get(h.index));
    	}
    	return true;
    	
    }

    /**
     * @return the key associated with the Handle.
     */
    public int handleGetKey(Handle h) {
    	if(h.index == -1 || h.equals(null)){
    		throw new IllegalArgumentException("PQNode not in queue, so it has no key");
    	}
       return queue.get(h.index).key;
    }

    /**
     * @return the value associated with the Handle.
     */
    public T handleGetValue(Handle h) {
    	if(h.index == -1 || h.equals(null)){
    		throw new IllegalArgumentException("PQNode not in queue anymore, so it has no value");
    	}
       return queue.get(h.index).value;
    }
    
    /*
     * Take in two PQNode<T>s and swap all their information
     */
    public void swap(PQNode<T> one, PQNode<T> two){
    	// swap handles
    	int tempHandleIndex = one.handle.index;
    	one.handle.index = two.handle.index;
    	two.handle.index = tempHandleIndex;
    	
    	queue.set(one.handle.index, one);
    	queue.set(two.handle.index, two);
    }
    
    /*
     * Fix the broken heap to make it a valid min heap
     */
    public void minHeapify(Handle h) {
    	if(this.size > (h.index)*2 + 2){
    		PQNode<T> parent = queue.get(h.index);
        	PQNode<T> left = queue.get(2*h.index + 1);
        	PQNode<T> right = queue.get(2*h.index + 2);
        	PQNode<T> smallest;
        	
        	if(left.key < parent.key){
        		smallest = left;
        	} else {
        		smallest = parent;
        	}
        	if(right.key < smallest.key){
        		smallest = right;
        	}
        	
        	if( !(smallest.equals(parent)) ){
        		swap(smallest, parent);
        		minHeapify(parent.handle);
        	}
    	}
    }

    /**
     * Print every element of the queue in the order in which it appears
     * (i.e. the array representing the heap)
     */
    public String toString() {
    	String s = "";
    	for(int i = 0; i < this.size; i++){
    		s += "(" + i + ", " + queue.get(i).key + ", " + queue.get(i).value + ")\n";
    	}
    	return s;
    }
}
