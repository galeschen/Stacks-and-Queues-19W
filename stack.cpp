
/**
 * @file stack.cpp
 * Implementation of the Stack class.
 *
 */

/**
 * Default constructor. Remember to initialize any variables you need
 * and allocate any required memory. The initial size of `items` should
 * be DEFAULTCAPACITY defined in stack.h.
 *
 */
template <class T> Stack<T>::Stack()
{
    /**
     * @todo Your code here!
     */
    max_items = DEFAULTCAPACITY;
    num_items = 0; // set num items in array = 0
    items = new T[max_items]; // instantiate array
}

/**
 * Destructor. Remember to free any memory allocated.
 *
 */
template <class T> Stack<T>::~Stack()
{
    /**
     * @todo Your code here!
     */
    if (items != NULL) {
        delete[] items; // delete array
    }
}

/**
 * Adds the parameter object to the top of the Stack. That is, the
 * retval should go at the beginning of the list. If the dynamic array
 * holding the stack retvals is full the array should be resized. Resize should be
 * called by multiplying  current capacity EXPANSIONFACTOR defined in stack.h.
 * To be clear resize should happen before adding the retval to the stack and only
 * when the stack is completely full.
 *
 * @param value The object to be added to the Stack.
 */
template <class T>
void Stack<T>::push(const T &newItem){
    /**
     * @todo Your code here!
     */
    if (num_items == max_items) {
        resize(max_items*EXPANSIONFACTOR);
    }
    items[num_items] = newItem; // else add new item
    num_items++; // increment the number of items we have
};

/**
 * Removes the object on top of the Stack, and returns it. That is, remove
 * the retval at the beginning of the list. You may assume this function
 * is only called when the Stack is not empty. If the size of the stack changes
 * to strictly less than 1 / SHRINKRATE (where SHRINKRATE is defined in stack.h)
 * after the item is removed the Stack should be resized to 1 / EXPANSIONFACTOR.
 *
 * @return The retval that used to be at the top of the Stack.
 */
template <class T>
T Stack<T>::pop(){
    /**
     * @todo Your code here!
     */
    // assumed not empty
    num_items--;
    T retval = items[num_items];
    // items[num_items] = NULL;
    if (num_items < (max_items/SHRINKRATE)) {
        resize(max_items/EXPANSIONFACTOR);
    }
    return retval;
};

/**
 * Adds an retval to the ordering structure.
 *
 * @see OrderingStructure::add()
 */
template <class T> void Stack<T>::add(const T &theItem)
{
    /**
     * @todo Your code here! Hint: this should call another Stack function
     *  to add the retval to the Stack.
     */
    push(theItem);
}

/**
 * Removes an retval from the ordering structure.
 *
 * @see OrderingStructure::remove()
 */
template <class T> T Stack<T>::remove()
{
    /**
     * @todo Your code here! Hint: this should call another Stack function
     * to remove an retval from the Stack and return it.
     */
    T res = peek();
    pop();
    return res;
}

/**
 * Finds the object on top of the Stack, and returns it to the caller.
 * Unlike pop(), this operation does not alter the Stack itself. It should
 * look at the beginning of the list. You may assume this function is only
 * called when the Stack is not empty.
 *
 * @return The retval at the top of the Stack.
 */
template <class T>
T Stack<T>::peek(){
    /**
     * @todo Your code here!
     */
    return items[num_items - 1];
};

/**
 * Determines if the Stack is empty.
 *
 * @return Whether or not the stack is empty (bool).
 */
template <class T>
bool Stack<T>::isEmpty() const {
    return (num_items == 0);
};

/**
 * Return the maximum number of items the stack can hold.
 *
 * Note: This is an implementation detail we would normally hide.
 * We include it here for testing purposes.
 *
 * @return Maximum number of items the stack can hold (int)
 */
template <class T>
size_t Stack<T>::capacity() const {
    /**
     * @todo Your code here!
     */
    return max_items;
};

/**
 * Return the number of items on the stack.
 *
 * @return Number of items on the stack (int)
 */
template <class T>
size_t Stack<T>::size() const {
    /**
     * @todo Your code here!
     */
    return items->size;
};

/**
 * Resize the the member variable `items`.
 * Don't forget to free up any memory that is no longer used.
 *
 * @param n The size of the stack after resizing
 */
template <class T>
void Stack<T>::resize(size_t n){
    /**
     * @todo Your code here!
     */
    if (n < DEFAULTCAPACITY) {
        n = DEFAULTCAPACITY;
    }

    T * newitems = new T[n];
    for (int i = 0; i < (int) num_items; i++) {
        newitems[i] = items[i];
    }

    delete[] items;
    items = newitems;
    
    max_items = n;
};