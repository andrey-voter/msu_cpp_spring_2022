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

void Allocator :: makeAllocator(size_t maxSize)
{
    if(maxSize <= 0)
	{
		return;
	}
	if (this->ptr == NULL)
    {
        // std :: cout << "makeAllocator initialised" << std :: endl;
        this->ptr = new char[maxSize];
    }
    else
    {
        delete[] this->ptr;
        this->ptr = new char[maxSize];
    }
    this->free_space = maxSize;
	this->offset = 0;
}

char* Allocator :: alloc(size_t size)
{
	if(size <= 0)
	{
		return nullptr;
	}
	
    if (size > this->free_space)
    {
        // std :: cout << "attempted to get more memory than allocated in makeAllocator" << std :: endl;
        return nullptr;
    }
    this->free_space -= size;
    this->offset += size;
    // std :: cout << "memory allocated" << std :: endl;
    return (this->ptr + this->offset);
}

void Allocator :: reset()
{
	this->free_space += this->offset;
    this->offset = 0;
}
   
