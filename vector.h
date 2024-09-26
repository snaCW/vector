#ifndef VECTOR_H
#define VECTOR_H

#include <string>
#include <stdexcept>
#include <typeinfo>

template <class T>
class vector
{
    public: class iterator
    {
        protected:
            T* pointer = nullptr;
            vector* _vector = nullptr;

        public:
            iterator() {}
            iterator(T* pointer, vector* _vector)
            {
                this->pointer = pointer;
                this->_vector = _vector;
            }
            iterator& operator++()
            {
                ++pointer;
                return *this;
            }
            iterator operator++(int)
            {
                iterator it = *this;
                ++pointer;
                return it;
            }
            iterator& operator--()
            {
                --pointer;
                return *this;
            }
            iterator operator--(int)
            {
                iterator it = *this;
                --pointer;
                return it;
            }
            bool operator==(const iterator& it)
            {
                if (pointer == it.pointer)
                    return true;
                return false;
            }
            bool operator!=(const iterator& it)
            {
                if (pointer != it.pointer)
                    return true;
                return false;
            }
            T& operator*()
            {
                int length = _vector->length;
                T* begin = _vector->array;
                T* end = _vector->array + length;
                if (pointer < begin || pointer >= end)
                {
                    throw std::invalid_argument("out of range");
                }
                return *pointer;
            }
            int operator-(const iterator& it) const
            {
                return pointer - it.pointer;
            }
            iterator operator-(int i) const
            {
                return iterator(pointer - i, _vector);
            }
            iterator operator+(int i) const
            {
                return iterator(pointer + i, _vector);
            }
            int distance(const iterator& it)
            {
                return pointer - it.pointer;
            }
    };
    public: class reverse_iterator : public iterator
    {
        public:
            reverse_iterator() : iterator() {}
            reverse_iterator(T* pointer) : iterator(pointer) {}
            reverse_iterator& operator++()
            {
                --(this->pointer);
                return *this;
            }
            reverse_iterator operator++(int)
            {
                reverse_iterator it = *this;
                --(this->pointer);
                return it;
            }
            reverse_iterator& operator--()
            {
                ++(this->pointer);
                return *this;
            }
            reverse_iterator operator--(int)
            {
                reverse_iterator it = *this;
                ++(this->pointer);
                return it;
            }
            bool operator==(const reverse_iterator& it)
            {
                if (this->pointer == it.pointer)
                    return true;
                return false;
            }
            bool operator!=(const reverse_iterator& it)
            {
                if (this->pointer != it.pointer)
                    return true;
                return false;
            }
            T& operator*()
            {
                int length = this->_vector->length;
                T* begin = this->_vector->array;
                T* end = this->_vector->array + length;
                if (this->pointer < begin || this->pointer >= end)
                {
                    throw std::invalid_argument("out of range");
                }
                return *this->pointer;
            }
            int operator-(const reverse_iterator& it) const
            {
                return it.pointer - this->pointer;
            }
            reverse_iterator operator-(int i) const
            {
                return reverse_iterator(this->pointer + i, this->_vector);
            }
            reverse_iterator operator+(int i) const
            {
                return reverse_iterator(this->pointer - i, this->_vector);
            }
            int distance(const reverse_iterator& it)
            {
                return it.pointer - this->pointer;
            }
    };

    private:
        T* array = new T[1];
        int length;
        int allocation_size;

    public:
        vector()
        {
            length = 0;
            allocation_size = 1;
        }
        vector(int allocation_size)
        {
            length = allocation_size;
            this->allocation_size = getTheNextPowerOf2(allocation_size);
            array = new T[this->allocation_size];
            
            for (int i = 0; i < length; i++)
            {
                array[i] = T();
            }
        }
        vector(int allocation_size, const T& initial_value)
        {
            length = allocation_size;
            this->allocation_size = getTheNextPowerOf2(allocation_size);;
            array = new T[this->allocation_size];
            
            for (int i = 0; i < length; i++)
            {
                array[i] = initial_value;
            }
        }
        vector(const vector& v)
        {
            array = v.array;
            length = v.length;
            allocation_size = v.allocation_size;
        }
        void push_back(const T& value)
        {
            if (length + 1 > allocation_size)
            {
                resize();
            }
            array[length] = value;
            length++;
        }
        void pop_back()
        {
            length--;
        }
        void clear()
        {
            array = new T[1];
            length = 0;
            allocation_size = 1;
        }
        T& back()
        {
            if (length == 0)
            {
                throw std::invalid_argument("out of range");
            }
            return array[length - 1];
        }
        T& front()
        {
            if (length == 0)
            {
                throw std::invalid_argument("out of range");
            }
            return array[0];
        }
        int size()
        {
            return length;
        }
        iterator begin()
        {
            return iterator(array, this);
        }
        reverse_iterator rbegin()
        {
            return reverse_iterator(array + length - 1, this);
        }
        iterator end()
        {
            return iterator(array + length, this);
        }
        reverse_iterator rend()
        {
            return reverse_iterator(array - 1, this);
        }
        void assign(const iterator& begin, const iterator& end)
        {
            length = end - begin;
            allocation_size = getTheNextPowerOf2(length);
            array = new T[allocation_size];
            
            int index = 0;
            for (iterator it = begin; it != end; it++)
            {
                array[index++] = *it;
            }
        }
        T& at(int index)
        {
            if (index >= length)
                throw std::invalid_argument("out of range");
            return array[index];
        }
        bool empty()
        {
            return (length == 0);
        }
        T& operator[](int index)
        {
            if (index >= length)
                throw std::invalid_argument("out of range");
            return array[index];
        }

    
    private:
        void resize()
        {
            T* array = new T[allocation_size * 2];
            for (int i = 0; i < allocation_size; i++)
            {
                array[i] = this->array[i];
            }
            allocation_size *= 2;
            this->array = array;
        }
        int getTheNextPowerOf2(int length)
        {
            int result = 1;
            while (result < length)
            {
                result *= 2;
            }
            return result;
        }
};

#endif