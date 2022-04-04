#include "allocator.hpp"

void Allocator :: makeAllocator(size_t maxSize)
{
    if (maxSize <= 0)
	{
		return;
	}
	if (this->ptr != nullptr)
    {
        delete[] this->ptr;
    }
    this->ptr = new char[maxSize];
    this->free_space = maxSize;
	this->offset = 0;
}

char* Allocator :: alloc(size_t size)
{
	if (size <= 0)
	{
		return nullptr;
	}
	
    if (size > this->free_space)
    {
        // std :: cout << "attempted to get more memory than allocated in makeAllocator" << std :: endl;
        return nullptr;
    }
    if (this->ptr == nullptr)
    {
        return nullptr;
    }
    char* return_value = this->ptr + this->offset;
    this->free_space -= size;
    this->offset += size;
    // std :: cout << "memory allocated" << std :: endl;
    return return_value;
}

void Allocator :: reset()
{
	this->free_space += this->offset;
    this->offset = 0;
}