package lab2;

/**
 * The goal of Lab 2 was to implement from scratch an Open-Addressing Hash table.
 * The effectiveness of our implementation was tested by utilizing it in the 
 * comparison of all common subsequences.  The lab was completed in ran in
 * a time expected such that the asymptotic expected running time was satisfied.
 * 
 * Completed November 2013
 * Shane Deiley
 * CSE 241: Data Structures and Algorithms
 * Professor Kunal Agarwal
 */
public class StringTable {

	public int size;
	public int exponent;
	public int records;
	public int testsize;
	public Record[] recordArray;
	
    /**
     * Create an empty table of size n
     *
     * @param n size of the table
     */
    public StringTable(int n) {
    	testsize = n;
    	
    	int i = 0;
    	while(Math.pow(2, i) < n){
    		i++;
    	}
    	this.exponent = i;
    	
    	this.size = (int)Math.pow(2, exponent);
    	
    	this.records = 0;
    	
    	this.recordArray = new Record[size];
    	for(int j = 0; j < size; j++){
    		recordArray[j] = null;
    	}
    }
 
    /**
     * Create an empty table.  You should use this construction when you are
     * implementing the doubling procedure.
     */
    public StringTable() {
    	this(4);
    }

    /**
     * Insert a Record r into the table.
     *
     * If you get two insertions with the same key value, return false.
     *
     * @param r Record to insert into the table.
     * @return boolean true if the insertion succeeded, false otherwise
     */
    public boolean insert(Record r) {    	
    	String toHashThisKey = r.getKey();
    	int hashThis = toHashKey(toHashThisKey);
    	int hashed = baseHash(hashThis);
    	
    	// Check to see if BaseHash found the right spot
    	if(recordArray[hashed] == null || recordArray[hashed].getKey().equals("DELETED") ){
    		recordArray[hashed] = r;
    		recordArray[hashed].keysInt = hashThis;
    		
    		records++;
    		double elements = this.records;
        	double possible = this.size;
        	double loadFactor = elements/possible;
        	if(loadFactor > .25){
        		this.doubleSize();
        	}
    		
    		return true;
    	}
    	
    	// StepHash through until spot found
    	int i = 0;
    	while(i != this.size){
    		hashed = (hashed + stepHash(hashed) + i) % this.size;
    		if(recordArray[hashed] == null || recordArray[hashed].getKey().equals("DELETED")){
    			recordArray[hashed] = r;
    			recordArray[hashed].keysInt = hashThis;
    			
    			records++;
    			double elements = this.records;
    	    		double possible = this.size;
    	    		double loadFactor = elements/possible;
    	    		if(loadFactor > .25){
    	    			this.doubleSize();
    	    		}
        		
        		return true;
    		}
    		
    		i++;
    	}
    	
    	return false;
    }

    /**
     * Delete a record from the table.
     *
     * Note: You'll have to find the record first unless you keep some
     * extra information in the Record structure.
     *
     * @param r Record to remove from the table.
     */
    public void remove(Record r) {
    	String keyToFind = r.getKey();
    	
    	if(find(keyToFind) != null){
    		int recordToRemovesSpot = hash(keyToFind);
    		
    		// Make dummy record with key = null
    		int positionSize = r.getPositionsCount();
        	String D = "DELETED";
        	Record dummy = new Record(D);
        	for(int j = 0; j < positionSize; j++){
        		dummy.addPosition(r.getPosition(j));
        	}
        	
        	recordArray[recordToRemovesSpot] = dummy;
        	
        	records--;
    	}
    	
    }

    /**
     * Find a record with a key matching the input.
     *
     * @param key to find
     * @return the matched Record or null if no match exists.
     */
    public Record find(String key) {
    	int keyToFindsInt = toHashKey(key);
    	int hashed = baseHash(keyToFindsInt);

    	if(recordArray[hashed] == null){
    		return null;
    	}
    	
    	// Find if the baseHash found the right Record
    	if( recordArray[hashed].getKey().equals(key) ){
    			return recordArray[hashed];
    	}
    	
    	
    	// StepHash each iteration, check to see if the hash functions' integer is equal to the 
    	// given key's toHashKey's integer.
    	// If the integer's match, check the actual keys.
    	// Return if they match, else stepHash in next iteration and repeat.
    	int i = 0;
    	while(i != size){
    		hashed = (hashed + stepHash(hashed) + i) % size;
    		
    		if(recordArray[hashed] == null){
    			return null;
    		}
    			if(recordArray[hashed].getKey().equals(key)){
    				return recordArray[hashed];
    			}
    		
    		i++;
    	}
    	
       return null;
    }
    
    /**
     * Method is called when the load factor exceeds .25 by means
     * insert.  Doubles the size of the current recordArray by 
     * using the paramaterized constructor
     */
    public void doubleSize(){
    	//Establish the new array
    	int currentSize = (int)Math.pow(2,exponent);
    	StringTable doubled = new StringTable(2*currentSize);
    	
    	//Rehash the records from the previous array, skipping the dummy nodes
    	for(int i = 0; i < currentSize; i++){
    		if( recordArray[i] != null && ( !(recordArray[i].getKey().equals("FUCKTHISLAB")) ) ){
    			doubled.insert(this.recordArray[i]);
    		}
    	}
    	
    	// Define the array being used to the established doubled array
    	this.size = doubled.size;
    	this.exponent = doubled.exponent;
    	this.testsize *= 2;
    	this.records = doubled.records;
    	this.recordArray = doubled.recordArray;
    }

    /**
     * Return the size of the hash table (i.e. the number of elements
     * this table can hold)
     *
     * @return the size of the table
     */
    public int size() {
       return this.testsize;
    }

    /**
     * Return the hash position of this key.  If it is in the table, return
     * the position.  If it isn't in the table, return the position it would
     * be put in.  This value should always be smaller than the size of the
     * hash table.
     *
     * @param key to hash
     * @return the int hash
     */
    public int hash(String key) {
    	int spotToFindsInt = toHashKey(key);
    	int hashed = baseHash(spotToFindsInt);
    	
    	if( (recordArray[hashed] == null) || (recordArray[hashed].getKey().equals(key)) ){
		return hashed;
	}
    	
    	int i = 0;
    	while(i != size){
    		hashed = (hashed + stepHash(hashed) +i) % size;
    		
    		if( (recordArray[hashed] == null) || (recordArray[hashed].getKey().equals(key)) ){
    			return hashed;
    		}
 
    		i++;
    	}
    	
    	return -1;
    }

    /**
     * Convert a String key into an integer that serves as input to hash functions.
     * This mapping is based on the idea of a linear-congruential pseuodorandom
     * number generator, in which successive values r_i are generated by computing
     *    r_i = (A * r_(i-1) + B) mod M   ****************************************************** This is the open addressing multiplication-fix function (Recursive)
     * A is a large prime number, while B is a small increment thrown in so that
     * we don't just compute successive powers of A mod M.
     *
     * We modify the above generator by perturbing each r_i, adding in the ith
     * character of the string and its offset, to alter the pseudorandom
     * sequence.
     *
     * @param s String to hash
     * @return int hash
     */
    int toHashKey(String s) {
        int A = 1952786893;
        int B = 367253;
        int v = B;

        for (int j = 0; j < s.length(); j++) {
            char c = s.charAt(j);
            v = A * (v + (int) c + j) + B;
        }

        if (v < 0) {
            v = -v;
        }
        return v;
    }

    /**
     * Computes the base hash of a hash key
     *
     * @param hashKey
     * @return int base hash
     */
    int baseHash(int hashKey) {
    	double A = (Math.sqrt(5.0) - 1)/2;
    	double irr = hashKey*A;
    	double rat = Math.floor(irr);
    	double dif = irr - rat;
    	double almost = size*(dif);
    	int n = (int) almost;
    	return confineToRange(n, 0, size);
    }

    /**
     * Computes the step hash of a hash key
     *
     * @param hashKey
     * @return int step hash
     */
    int stepHash(int hashKey) {
    	double A = (Math.sqrt(7) - 1.6)/2;
    	double irr = hashKey*A;
    	double rat = Math.floor(irr);
    	double dif = irr - rat;
    	double almost = size*(dif);
    	almost = Math.ceil(almost);
    	int n = (int) almost;
    	int h2k = confineToRange(n, 1, size);
    	if(h2k % 2 == 0){
    		return h2k + 1;
    	} else {
    		return h2k;
    	}
    }
    
    int confineToRange(int n, int min, int max){
    	return (n % (max-min)) + min;
    }
}