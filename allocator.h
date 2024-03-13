#pragma once

#include <memory>

namespace efes
{

template<typename T, std::size_t BLOCK_SIZE = 1>
struct Block
{
    T* memory;
    std::unique_ptr<Block> next;

    std::size_t m_available;

    std::list<T*> freedPool;

    Block() : m_available(BLOCK_SIZE)
    {
        memory = (T*) std::malloc(BLOCK_SIZE * sizeof(T));
    }
    ~Block() 
    {
        std::free(memory);
    }

    inline T* getPiece(std::size_t n)
    {
        if(!freedPool.empty()) 
        {
            T* res = freedPool.back();
            freedPool.pop_back();
            return res;
        }

        if (m_available > 0)
        {
            T* res = (T*) &memory[BLOCK_SIZE - m_available];
            m_available--;
            return res;
        }

        if (next == nullptr) next = std::make_unique<Block>();

        return next->getPiece(n);
    }

    void freePiece(T* _p)
    {
        if ((_p >= &memory[0]) && (_p <= &memory[BLOCK_SIZE * sizeof(T) - 1]))
        {
            freedPool.push_back(_p);
            return;
        }

        if (next) next->freePiece(_p);
    }
};

template<typename T, std::size_t BLOCK_SIZE = 1>
struct allocator
{
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    std::unique_ptr<Block<T, BLOCK_SIZE> > mem;
    
    allocator() 
    {
        mem = std::make_unique<Block<T, BLOCK_SIZE> >();
    }
    ~allocator() = default;

    T *allocate(std::size_t n)
    {
        return reinterpret_cast<T*>(mem->getPiece(n));
    }

    void deallocate(T* p, std::size_t n)
    {
        mem->freePiece(p);
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args)
    {
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T *p)
    {
        p->~T();
    }

    template <typename U>
    struct rebind 
    {
        using other = allocator<U, BLOCK_SIZE>;
    };
};

template<typename N>
class list_iterator
{
public:
    N* _node;

    list_iterator(N* node) : _node(node)
    {}

    decltype(_node->value)& operator*() const
    { 
        return _node->value;
    }

    list_iterator<N>* operator++(int)
    {
        _node = _node->next;
        return this;
    }

    list_iterator<N>& operator++()
    {
	    _node = _node->next;
        return *this;
    }
};

template<typename T, typename Alloc = allocator<T, 1> >
class lcontainer 
{
public:
    //Alloc::rebind<T>::other _node_alloc;

    struct Node {
        Node* next;
        T value;

        Node(const T& val) : next(nullptr), value(val) {}
        ~Node() = default;
    };
    
    lcontainer() : _node(nullptr), _end(nullptr), _size(0)
    {}

    ~lcontainer()
    {
        Node* p     = _node;
        Node* pnext;
        while(p != nullptr)
        {   
            pnext = p->next;
            _nodealloc.destroy(p);
            _nodealloc.deallocate(p, sizeof(Node));
            p = pnext;
        }
    }

    void push_back(const T& elem)
    {
        if (_node == nullptr)
        {
            _node = _nodealloc.allocate(sizeof(Node));
            _nodealloc.construct(_node, elem);
            _end   = _node;
            _size++;
            return;
        }

        _end->next = _nodealloc.allocate(sizeof(Node));
        _nodealloc.construct(_end->next, elem);

        _end = _end->next;

        _size++;

        return;
    }

    friend std::ostream& operator<<(std::ostream& s, const lcontainer& l)
    {
        s << "{ ";
        Node* p = l._node;
        while(p != nullptr)
        {   
            s << p->value;
            if (p->next != nullptr)
                s << ", ";
            p = p->next;
        }
        s << " }";
        return s;
    }

    std::size_t size()
    { return _size; }

    bool empty()
    { return (_node == nullptr); }

    typedef T value_type;
    typedef list_iterator<Node> iterator;

    iterator begin()
    { return iterator(_node); }

    iterator end()
    { return iterator(_end->next); }

private:
    Node* _node;
    Node* _end;
    std::size_t _size;

    Alloc _alloc;
    
    typedef typename __gnu_cxx::__alloc_traits<Alloc>::template
	rebind<Node>::other _Node_allocator;

    _Node_allocator _nodealloc;
};


template<typename T>
bool operator==(const list_iterator<T>& __x, const list_iterator<T>& __y)
{ return (__x._node == __y._node); }

template<typename T>
bool operator!=(const list_iterator<T>& __x, const list_iterator<T>& __y)
{ return !(operator==(__x, __y)); }


};