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

    TElem& update(int i, TElem& e);

    void append(TElem& e);

    void insert(int i, TElem&  e);

    TElem remove(int i);
    //equal operator overloading
    List& operator=(const List& other);

    ~List();
};

template <typename TElem>
void List<TElem>::redim() {
    auto *eNou = new TElem[2 * max_size];
    for (int i = 0; i < max_size; i++)
        eNou[i] = elems[i];
    max_size *= 2;
    delete[] elems;
    elems = eNou;
}

template <typename TElem>
List<TElem>::List() {
    elems = new TElem[10];
    max_size = 10;
    size = 0;
}

template <typename TElem>
List<TElem>::~List() {
    delete[] elems;
}


template <typename TElem>
int List<TElem>::getSize() const{
    return this->size;
}


template <typename TElem>
TElem& List<TElem>::element(int i) const{
    return elems[i];
}


template <typename TElem>
void List<TElem>::append(TElem& e) {
    if(size==max_size)
        redim();
    this->elems[size++] = e;
}

template <typename TElem>
void List<TElem>::insert(int i, TElem& e) {
    if(size==max_size)
        redim();
    for(int j = size; j > i; j--)
        this->elems[j] = this->elems[j-1];
    this->elems[i] = e;
    size++;
}

template <typename TElem>
TElem& List<TElem>::update(int i, TElem& e) {
    TElem old = this->elems[i];
    this->elems[i] = e;
    return old;
}

template <typename TElem>
TElem List<TElem>::remove(int i) {
    TElem old = this->elems[i];
    for(int j = i; j < size; j++)
        this->elems[j] = this->elems[j+1];
    if (size>0)
        size--;
    return old;}

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