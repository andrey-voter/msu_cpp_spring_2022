#include <cstddef> 
class Allocator
{
    size_t offset = 0;
    
    public:
        char *ptr = nullptr;
        size_t free_space;

    public:
        void makeAllocator(size_t maxSize);
        char* alloc(size_t size);
        void reset();
        ~Allocator()
        {
            delete[] this->ptr;
        }
};


   
