#ifndef PHYSICS_PHYS_ALLOC_H_
#define PHYSICS_PHYS_ALLOC_H_

template <typename T, int TEntryCount>
struct PhysStaticArray
{
    int freeEntry;
    T entries[TEntryCount];
    
    void init( )
    {
        memset(entries, 0, sizeof(entries));
        freeEntry = -1;
        for(int i = TEntryCount -1; i >= 0; --i)
        {
            release(&entries[i]);
        }
    }
    
    T* allocate( )
    {
        if(freeEntry == -1)
        {
            return nullptr;
        }
        assert(freeEntry < TEntryCount);
        T* ptr = &entries[freeEntry];
        freeEntry = *(int*)ptr;
        return ptr;
    }
    
    void release(T *ptr)
    {
        assert(isMember((unsigned int)ptr));
        memset(ptr, 0, sizeof(T));
        *(int*)ptr = freeEntry;
        freeEntry = ptr - entries;
    }

    bool isMember(unsigned int u)
    {
        if ( u >= (unsigned int)&entries[0] && u < (unsigned int)&entries[TEntryCount] )
        {
            return true;
        }
        return false;
    }

    static constexpr int getMaxEntryCount()
    {
        return TEntryCount;
    }
};

#endif
