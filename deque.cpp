template <class Object>
Deque<Object>::Deque( ) {                          // the constructor
    front = back = NULL;
}

template <class Object>
Deque<Object>::Deque( const Deque &rhs ) {         // the copy constructor
    front = back = NULL;
    *this = rhs;
}

template <class Object>
Deque<Object>::~Deque( ) {                         // the destructor
    clear( );
}

template <class Object>
bool Deque<Object>::isEmpty( ) const {             // check if a deque is empty
    return front == NULL;
}

template <class Object>
int Deque<Object>::size( ) const {                 // retrieves # deque nodes
    int cnt = 0;
    for ( DequeNode *ptr = front; ptr != NULL; ptr = ptr->next ) // traverse que
        ++cnt;

    return cnt;
}

template <class Object>
const Object &Deque<Object>::getFront( ) const {   // retrieve the front node
    if ( isEmpty( ) )
        throw "empty queue";
    return front->item;
}

template <class Object>
const Object &Deque<Object>::getBack( ) const {    // retrieve the tail node
    if ( isEmpty( ) )
        throw "empty queue";
    return back->item;
}

template <class Object>
void Deque<Object>::clear( ) {          // clean up all entries.
    while ( !isEmpty( ) )                 // dequeue till the queue gets empty.
        removeFront( );
}

//adds new node to the front
template <class Object>
void Deque<Object>::addFront( const Object &obj ) {
    //creates a new DequeNode object
    DequeNode *newPtr = new DequeNode;
    //checks if newPtr is NULL
    if ( newPtr == NULL )
        cout << "out of memory" << endl;
    newPtr->item = obj; //newPtr.item set equal to obj
    newPtr->next = front; //set newPtr next pointer to front
    newPtr->prev = NULL; //set newPtr prev pointer to NULL

    //assigning pointers
    if ( isEmpty( ) )
        back = newPtr;
    else
        front->prev = newPtr;
    front = newPtr;
}

// add a new node to tail
template <class Object>
void Deque<Object>::addBack( const Object &obj ) {
    //create new DequeNode object
    DequeNode *newPtr = new DequeNode;
    if ( newPtr == NULL )
        throw "out of memory";
    newPtr->item = obj;
    newPtr->next = NULL;
    newPtr->prev = back;

    //assigning pointers
    if ( isEmpty( ) )
        front = newPtr;
    else
        back->next = newPtr;
    back = newPtr;
}

// remove the front node
template <class Object>
Object Deque<Object>::removeFront( ) {
    //copy front element to object variable
    Object frontItem = getFront( );
    DequeNode *old = front; // temporary pointer for deleting old node

    //if only one element exists currently, then remove the element by setting front and back equal to NULL
    if ( front == back )
        front = back = NULL;
    //else more than one element, then increment front pointer so that previous front element is dropped from deque
    else {
        front = front->next;
        front->prev = NULL;
    }
    delete old; //Delete old node
    // return the front object
    return frontItem;
}

// remove the tail node
template <class Object>
Object Deque<Object>::removeBack( ) {
    // copy front element to object variable
    Object backItem = getBack( );
    DequeNode *old = back; // temporary pointer for deleting old node
    //if only one element exists currently, then remove the element by setting front and back equal to NULL
    if ( front == back )
        front = back = NULL;
    //else more than one element, then decrement back pointer so that next back element is dropped from deque
    else {
        back = back->prev;
        back->next = NULL;
    }
    delete old; //Delete old node
    // return the back object
    return backItem;
}

//function overloading assign operator
//assumes self-assignment as possibility too
template <class Object>
const Deque<Object> &Deque<Object>::operator=( const Deque &rhs ) {
    clear( );
    for ( DequeNode *front_ptr = rhs.front; front_ptr != NULL; front_ptr = front_ptr->next )
        addBack( front_ptr->item );
    return *this;
}

