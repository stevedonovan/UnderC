// ptr_cache.h
// Manages a cache of object pointers; if more are
// needed they'll be generated. This is a useful
// pattern if temporary objects are needed, and there
// are well-defined junctures at which they can be
// discarded.
#ifndef __PTR_CACHE_H
#define __PTR_CACHE_H
#include <list>

template <class T>
 class PtrCache {
    std::list<T*> m_ptr_list;
    std::list<T*>::iterator m_cursor;
 public:
    void reset()
    { m_cursor = m_ptr_list.begin(); }

    void clear(bool report = false)
    {
        reset();
        while (m_cursor != m_ptr_list.end()) {
            delete *m_cursor;
            m_cursor++;
        }
        if (report && m_ptr_list.size() > 0) 
            cerr << "Items left " << (int)m_ptr_list.size() << endl;
        m_ptr_list.clear();        
    }

    ~PtrCache()
    { clear(); }

    PtrCache()
    { reset(); } 

    T* alloc()
    {
        T* ptr;
        if (m_cursor == m_ptr_list.end()) {
            ptr = new T();
            m_ptr_list.push_back(ptr);
        } else
            ptr = *m_cursor++;
        return ptr;
    }
};

#endif

