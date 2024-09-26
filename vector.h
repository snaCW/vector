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

        public:
            iterator() {}
            iterator(T* pointer)
            {
                this->pointer = pointer;
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
                return *pointer;
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
    };

    private:
        T* array = new T[20];
        int length;
        int allocation_size;

    public:
        vector()
        {
            length = 0;
            allocation_size = 20;
        }
        vector(int allocation_size)
        {
            length = allocation_size;
            this->allocation_size = allocation_size;
            delete array;
            array = new T[length];
            
            T default_value = getDefaultValue();
            for (int i = 0; i < length; i++)
            {
                array[i] = default_value;
            }
        }
        vector(int allocation_size, T initial_value)
        {
            length = allocation_size;
            this->allocation_size = allocation_size;
            delete array;
            array = new T[length];
            
            for (int i = 0; i < length; i++)
            {
                array[i] = initial_value;
            }
        }
        vector(const vector& v)
        {
            delete array;
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
            delete array;
            array = new T[20];
            length = 0;
            allocation_size = 20;
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
            return iterator(array);
        }
        reverse_iterator rbegin()
        {
            return reverse_iterator(array + length - 1);
        }
        iterator end()
        {
            return iterator(array + length);
        }
        reverse_iterator rend()
        {
            return reverse_iterator(array - 1);
        }
        void assign(iterator& begin, iterator& end)
        {
            delete array;
            length = (end.pointer - begin.pointer) / sizeof(T*);
            array = new T[length];
            
            int index = 0;
            for (iterator it = begin; it != end; it++)
            {
                array[index++] = *(it.pointer);
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
        T getDefaultValue()
        {
            switch (typeid(T))
            {
                case typeid(bool):
                case typeid(short):
                case typeid(unsigned short):
                case typeid(int):
                case typeid(unsigned int):
                case typeid(float):
                case typeid(double):
                case typeid(long):
                case typeid(unsigned long):
                case typeid(long long):
                case typeid(unsigned long long): return 0;
                
                case typeid(std::string): return "";
                default: return T();
            }
        }
        void resize()
        {
            T* array = new T[allocation_size * 2];
            for (int i = 0; i < allocation_size; i++)
            {
                array[i] = this->array[i];
            }
            delete this->array;
            this->array = array;
        }
};


#endif