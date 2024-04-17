#pragma once
template <typename TElem>
class IteratorVectorT;

template <typename TElem>
class List{

private:
    /* aici e reprezentarea */
    int max_size;
    int size;
    TElem *elems;
    void redim();

public:
    List();

    int getSize() const;

    TElem& element(int i) const;

    void update(int i, TElem& e);

    void append(TElem& e);

    void insert(int i, TElem&  e);

    TElem remove(int i);
    //equal operator overloading
    List& operator=(const List& other);
    //cpoy constructor
    List(const List& other);

    friend class IteratorVectorT<TElem>;
    //functii care creaza iteratori
    IteratorVectorT<TElem> begin();
    IteratorVectorT<TElem> end();

    ~List();
};

//Description : This is the constructor of the iterator
//Input : a reference to the list
//Output : -
template<typename ElementT>
IteratorVectorT<ElementT> List<ElementT>::begin()
{
    return IteratorVectorT<ElementT>(*this);
}

//Description : This is the constructor of the iterator
//Input : a reference to the list, an integer representing the position
//Output : -
template<typename ElementT>
IteratorVectorT<ElementT> List<ElementT>::end()
{
    return IteratorVectorT<ElementT>(*this, size);
}


//Description : This function resizes the list
//Input : -
//Output : -
template <typename TElem>
void List<TElem>::redim() {
    auto *eNou = new TElem[2 * max_size];
    for (int i = 0; i < max_size; i++)
        eNou[i] = elems[i];
    max_size *= 2;
    delete[] elems;
    elems = eNou;
}

//Description : This is the constructor of the list
//Input : -
//Output : -
template <typename TElem>
List<TElem>::List() : max_size(10), size(0), elems(new TElem[10]) {
}


//Description : This is the destructor of the list
//Input : -
//Output : -
template <typename TElem>
List<TElem>::~List() {
    delete[] elems;
}

//Description : This function returns the size of the list
//Input : -
//Output : an integer representing the size of the list
template <typename TElem>
int List<TElem>::getSize() const{
    return this->size;
}

//Description : This function returns the element at a given position
//Input : an integer representing the position of the element
template <typename TElem>
TElem& List<TElem>::element(int i) const{
    return elems[i];
}

//Description : This function adds an element to the list
//Input : a reference to the element
//Output : -
template <typename TElem>
void List<TElem>::append(TElem& e) {
    if(size==max_size)
        redim();
    this->elems[size++] = e;
}

//Description : This function inserts an element at a given position
//Input : an integer representing the position, a reference to the element
//Output : -
template <typename TElem>
void List<TElem>::insert(int i, TElem& e) {
    if(size==max_size)
        redim();
    for(int j = size; j > i; j--)
        this->elems[j] = this->elems[j-1];
    this->elems[i] = e;
    size++;
}

//Description : This function updates an element at a given position
//Input : an integer representing the position, a reference to the element
//Output : -
template <typename TElem>
void List<TElem>::update(int i, TElem& e) {
    this->elems[i] = e;
}

//Description : This function removes an element at a given position
//Input : an integer representing the position
//Output : the removed element
template <typename TElem>
TElem List<TElem>::remove(int i) {
    TElem old;
    old = this->elems[i];
    for(int j = i; j < size; j++)
        this->elems[j] = this->elems[j+1];
    if (size>0)
        size--;
    return old;}

//Description : This is the equal operator overloading
//Input : a reference to another list
//Output : a reference to the current list
template <typename TElem>
List<TElem>& List<TElem>::operator=(const List<TElem>& other) {
    if (this == &other)
        return *this;
    delete[] elems;
    elems = new TElem[other.max_size];
    size = other.size;
    max_size = other.max_size;
    for (int i = 0; i < size; i++)
        elems[i] = other.elems[i];
    return *this;
}

//Description : This is the copy constructor
//Input : a reference to another list
//Output : -
template <typename TElem>
List<TElem>::List(const List<TElem>& other) : max_size(other.max_size), size(other.size), elems(new TElem[other.max_size]) {
    for (int i = 0; i < size; i++)
        elems[i] = other.elems[i];
}



template<typename ElementT>
class IteratorVectorT {
private:
    const List<ElementT>& v;
    int poz = 0;
public:
    IteratorVectorT(const List<ElementT>& v) noexcept;
    IteratorVectorT(const List<ElementT>& v, int poz)noexcept;
    bool valid()const;
    ElementT& element() const;
    void next();
    ElementT& operator*();
    IteratorVectorT& operator++();
    bool operator==(const IteratorVectorT& ot)noexcept;
    bool operator!=(const IteratorVectorT& ot)noexcept;
};

//Description : This is the constructor of the iterator
//Input : a reference to the list
//Output : -
template<typename ElementT>
IteratorVectorT<ElementT>::IteratorVectorT(const List<ElementT>& v) noexcept:v{ v } {}

//Description : This is the constructor of the iterator
//Input : a reference to the list, an integer representing the position
//Output : -
template<typename ElementT>
IteratorVectorT<ElementT>::IteratorVectorT(const List<ElementT>& v, int poz)noexcept : v{ v }, poz{ poz } {}

//Description : This function checks if the iterator is valid
//Input : -
//Output : a boolean value
template<typename ElementT>
bool IteratorVectorT<ElementT>::valid()const {
    return poz < v.lg;
}

//Description : This function returns the element at the current position
//Input : -
//Output : a reference to the element
template<typename ElementT>
ElementT& IteratorVectorT<ElementT>::element() const {
    return v.elems[poz];
}

//Description : This function moves the iterator to the next position
//Input : -
//Output : -
template<typename ElementT>
void IteratorVectorT<ElementT>::next() {
    poz++;
}

template<typename ElementT>
ElementT& IteratorVectorT<ElementT>::operator*() {
    return element();
}

template<typename ElementT>
IteratorVectorT<ElementT>& IteratorVectorT<ElementT>::operator++() {
    next();
    return *this;
}

template<typename ElementT>
bool IteratorVectorT<ElementT>::operator==(const IteratorVectorT<ElementT>& ot) noexcept {
    return poz == ot.poz;
}

template<typename ElementT>
bool IteratorVectorT<ElementT>::operator!=(const IteratorVectorT<ElementT>& ot)noexcept {
    return !(*this == ot);
}