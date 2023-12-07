#include "heap.h"

/**
 * A few notes!
 * in the array, 
 *  element i's parent is (i-1)/2
 *  element i's left child is 2i+1
 *  element i's right child is 2i+2
 */

int const HEAP_INF = 276447232;

//*******************************************************************************************************************************************************************
// @brief gets the maximum value in the heap
// @return the highest value integer in the heap
T Heap::getMax() const {
    return heaparray[0];       //mak-heap: max value is always at heaparray[0]
}

//*******************************************************************************************************************************************************************
// @brief default constructor. Construct an empty heap with initial capacity
Heap::Heap(int capacity) {
    //default capacity is 100
    this->count = 0;                //set count
    this->capacity = capacity;      //set cap
    heaparray = new T[capacity];    //init heap array
}

//*******************************************************************************************************************************************************************
// @brief destructor
Heap::~Heap() {
    count = 0;
    capacity = 0;
    delete[](heaparray);
    heaparray = nullptr;
}

/********************************************************************************************************************************************************************
 * @brief constructor to build a heap from an array of values
 * @param values array of values to be added to the heap
 * @param length the size of the array
 */
Heap::Heap(T *values, int length) {
    //assume that the array to be copied is completely full
    this->heaparray = new T[length * 2];    // init heaparray
    this->capacity = length * 2;            // set cap
    this->count = length;                   // set count

    //copy values into heaparray
    for(int i = 0; i < length; i++){
        this->heaparray[i] = values[i];     //copy values into heaparray
    }

    this->heapify();

}

/********************************************************************************************************************************************************************
 * @brief Copy constructor
 * @param other the heap to be copied
 */
Heap::Heap(const Heap &other) {
    this->count = other.count;
    this->capacity = other.capacity;
    this->heaparray = new T[capacity];

    for(int i = 0; i < this->count; i++){
        this->heaparray[i] = other.heaparray[i];
    }

}

// GETTERS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief getter for heaparray
 * 
 * @return heaparray
 */
T* Heap::get_heaparray() const{
    return this->heaparray;
}


/**
 * @brief getter for capacity
 * 
 * @return capacity
 */
int Heap::get_capacity() const{
    return this->capacity;
}

/**
 * @brief getter for count
 * 
 * @return count
 */
int Heap::get_count() const{
    return count;
}

// SETTERS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief setter for heaparray
 * 
 */
void Heap::set_heaparray(T* array){
    this->heaparray = array;
}

/**
 * @brief setter for capacity
 * 
 */
void Heap::set_capacity(int capacity){
    this->capacity = capacity;
}

/**
 * @brief setter for count
 * 
 */
void Heap::set_count(int count){
    this->count = count;
}

/********************************************************************************************************************************************************************
 * @brief checks if two Heaps are identical
 * @param other the heap to be checked
 * @return true if equal, else false
 */
bool Heap::is_equal(const Heap &other){
    if(this->capacity != other.capacity) return false;                  //if capacity different, false
    if(this->count != other.count) return false;                        //if count different, false

    for(int i = 0; i < this->count; i++){                               //if any element of the heap arrays are different false
        if(this->heaparray[i] != other.heaparray[i]) return false;
    }

    return true; // else same count, cap and heaparray true
}

/********************************************************************************************************************************************************************
* @brief Assignment operator
* @param other the heap to be copied
* @return Heap& a reference to the heap
*/
Heap & Heap::operator=(const Heap &other) {
    bool isEqual = this->is_equal(other);               // check if "a = a" case
    if(!isEqual){                                       // if not "a = a"
        this->count = other.count;                      //copy all of other's attributes into this
        this->capacity = other.capacity;
        for(int i = 0; i < this->count; i++){
            this->heaparray[i] = other.heaparray[i];    //copy all of other's heaparray into this->heaparray
        }

    }

    return *this;

}

/********************************************************************************************************************************************************************
 * @brief   organizes the values in the heap to satisfy heap property.
 */
void Heap::heapify() {
    if(this->count == 0) return; // heap only has root, no need to do anything

    int firstParent = ((count - 1) - 1) / 2;

    //index of heaparray starting with the parent of the last element in the heap
    for(int index = firstParent; index >= 0; index--){ // at each index try to percolate down
        percolateDown(index);
    }

}

/********************************************************************************************************************************************************************
 * @brief  Runs percolate down on the heap for the node stored in index.
 */
void Heap::percolateDown(int index) {
    // Run recursively until the current node is bigger than its children
    
    //at each level
    //  check leftchild
    //  check rightchild

    if(2 * index + 2 < count){ // index has two children

        // swap index with thegreatest of its children, if any
        if(this->heaparray[2 * index + 2] > this->heaparray[2 * index + 1]) {
            if(this->heaparray[index] > this->heaparray[2 * index + 2]){
                swap(index, 2 * index + 2);
                percolateDown(2 * index + 2);
            }
        }
        else if(this->heaparray[index] > this->heaparray[2 * index + 1]) {
            swap(index, 2 * index + 1);
            percolateDown(2 * index + 1);            
        }

    }else if(2 * index + 1 < count){ // index only has left child
        if(this->heaparray[index] > this->heaparray[2 * index + 1]) {
            swap(index, 2 * index + 1);
            percolateDown(2 * index + 1);            
        }
    }else return;  // return conditions:
                  //  if no children exist
                  //  if no child is greater than current node
                  //  implicitly, if index is greater than count, inherently 2 * index + 1 is greater than count(as is 2 * index + 2)

}

/********************************************************************************************************************************************************************
 * @brief  Runs percolate up on the heap for the node stored in index.
 */
void Heap::percolateUp(int index) {

    // run recursively until the current node is small than its parent
    //at each level
    //  check parent

    if((index - 1) / 2 >= 0 && this->heaparray[index] < this->heaparray[(index - 1) / 2]) {            // checks if parent exists in the heap
        swap(index, (index - 1) / 2);                                                                  //   and if parent is less than current node
        percolateUp((index - 1) / 2);                                                                  //   swap and try to percolate further
    } else return;  // return conditions:
                    //  if current is root
                    //  if parent is greater than current node
                    //  implicitly, if index is 0, inherently (index - 1) / 2 is less than 0
}

/********************************************************************************************************************************************************************
 * @brief resize heaparray
 *  
 */
void Heap::resize_heap(){
    T* new_arr = new T[this->get_capacity() * 2], // resized array
        *old_arr = this->heaparray;
    this->capacity *= 2; // increase cap

    for(int i = 0; i < this->count; i++){
        new_arr[i] = old_arr[i];    //copy old array into new array
    }
    delete old_arr;
    old_arr = nullptr;
    this->heaparray = new_arr;
}

/*******************************************************************************************************************************************************************
 * @brief  inserts a value into the heap
 *
 */
void Heap::insert(T value) {
    if(this->count + 1 > this->capacity) resize_heap(); // if inserting makes heaparray too big, resize it
    
    this->heaparray[count] = value; // insert value and increment count
    count++;

    percolateUp(count - 1); // try to percolate the new value up the heap
}

/********************************************************************************************************************************************************************
 * @brief  Removes the max value from the heap
 * @return the value that was removed
 */
T Heap::removeMin() {
    T max = this->heaparray[0];
    swap(0, count - 1);                     // swap max to back of array
    this->heaparray[count - 1].distance = HEAP_INF;   // nullify it
    count--;                                // reduce count
    percolateDown(0);                // percolate swapped value down heap

    return max;
}

//*******************************************************************************************************************************************************************
//@brief converts the heap into a string
string Heap::toString()
{
    string s = "[ ";
    for (int i = 0; i < count; i++)
    {
        s += heaparray[i].name + " ";
    }
    s += "]";
    return s;
}

/********************************************************************************************************************************************************************
 * @brief  Prints the values in the heap
 */
void Heap::printHeap() {
    cout << toString() << endl;
}

/**
 * @brief  Prints the values in an array
 */
void printArray(T values[], int length) {
    int i;
    cout << "[ ";
    for (i = 0; i < length; i++) {
        cout << values[i].name << " ";
    }
    cout << "]\n";
}

/********************************************************************************************************************************************************************
 * @brief  Swaps the values in the heap at index1 and index2
 */
void Heap::swap(int index1, int index2) {
    T box = this->heaparray[index1];
    this->heaparray[index1] = this->heaparray[index2];
    this->heaparray[index2] = box;
}

/********************************************************************************************************************************************************************
 * @brief  Sorts the values of an array by using the heap
 */
void heapSort(T values[], int length) {

    cout << "Array Before Sorting: \n";
    printArray(values, length);

    Heap sorter = Heap(values, length); // heap for sorting values, constructor auto heapifies
    
    while(sorter.get_count() > 1){  //while count is greater than 1
        sorter.swap(0, sorter.get_count() - 1);             //swap root with last element in array
        sorter.set_count(sorter.get_count() - 1);           //reduce count
        sorter.percolateDown(0);                            //percolate swapped value down heap
    }

    // values gets the sorted array's values
    for(int i = 0; i < length; i++){
        values[i] = sorter.get_heaparray()[i];
    }

    cout << "Array After Sorting: \n";
    printArray(values, length);

    return;
}

/********************************************************************************************************************************************************************
     * @brief Change the key of the element at position i to the new value.
     *        It maintains the heap property.
     * @param i the position of the element to be decreased
     * @param value the new value
     */
void Heap::changeKey(int i, double new_val) {
    
    this->heaparray[i].distance = new_val;   // change the element

    if(this->heaparray[i].distance < this->heaparray[(i - 1) / 2].distance) percolateUp(i); // if parent is greater than this node percolate up
    else percolateDown(i);

}
