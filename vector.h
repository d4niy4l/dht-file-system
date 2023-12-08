#pragma once
/************************************************************************
TITLE: VECTOR
DESCRIPTION:
This class was made to serve as a
replacement for the static array in C++,
to efficiently grow the array and manage
dynamic memory.
REQUIREMENTS: COPY CONSTRUCTOR FOR THE TYPE MUST BE DEFINED
AUTHOR: DANIYAL AHMED [22I-1032]
COAUTHOR: MUHAMMAD AHMAD [22I-1056]
COAUTHOR: HAFIZA IQRA [22I-1299]
DATE: MONDAY 4-12-2023
LASTEDITBY: MUHAMMAD AHMAD
*************************************************************************/
#include <iostream>

using namespace std;

template <class T>
class Vector {
private:
	int _capacity;
	int _size;
	T* data;
public:  
	
    //  DEFAULT CONSTRUCTOR
    Vector (int s = 5) 
        :_capacity(s), _size(0), data(nullptr)
    {
		_capacity = s;
		_size = 0;
		data = new T[_capacity];
	}
	
    //  PARAMETERIZED CONSTRUCTOR
    Vector (int s, const T& val)
        :_capacity(s), _size(s)
    {
		data = new T[_capacity];
		for (int i = 0; i < s; i++)
			data[i] = val;
	}
	
    //  COPY CONSTRUCTOR
    Vector (const Vector<T>& v) {
        this->_capacity = v._capacity;
        this->_size = v._size;
        if (_capacity > 0) {
            this->data = new T[this->_capacity];
            for (int i = 0; i < v._capacity; i++) {
                this->data[i] = v.data[i];
            }
        }
    }

    //  DESTRUCTOR
    ~Vector() {
		delete[] data;
        data = nullptr;
	}    
    
    //  RESIZE
    void resize(int s, const T& val) {
		//  IF SAME _capacity RETURN
        if (s == _capacity) return;
		//  CLEAR IF RESIZE TO ZERO
        if (s == 0) {
            this->removeAll();
        }
        
        if (data != nullptr) {
            delete[] data;
            this->data = nullptr;
        }
		data = new T[s];
		_capacity = s;
		for (int i = 0; i < s; i++)
			data[i] = val;
	}
	
    //  PUSH_BACK AMORTIZED O(1)
    void push_back(const T& val) {
        /*
            @params: val - Value to be strored
            DESCRIPTION:
            Insert value at the end of the array
        */

       //   IF ABOVE CAPACITY THEN RESIZE
		if (_size >= _capacity) {
            
            //  MAKING AN ARRAY OF LARGER SIZE
			T* temp = data;
			data = new T[_capacity + 10];
			
            //  COPY PREVIOUS ELEMENTS TO NEW ELEMENTS
            for (int i = 0; i < _capacity; i++)
				data[i] = temp[i];

            //  RESETTING _capacity
			_capacity = _capacity + 10;
			
            //  DELETING PREVIOUS ARRAY
            delete[] temp;
            temp = nullptr; 
		}
        //  ELSE SIMPLY ADD
		data[_size] = val;
		_size++;
	}
	
    //  POP_BACK O(1)
    void pop_back() {
		if (_size > 0)
			_size--;
	}

    //  PUSH FRONT O(N)
	void push_front(const T& val) {
		T* temp = data;
		if (_size >= _capacity) {
			data = new T[_capacity + 10];
        }
		for (int i = _capacity-1; i >= 1; i--) {
			data[i] = temp[i - 1];
        }
        if (_size >= _capacity) {
            _capacity += 10;        
    		delete[] temp;
            temp = nullptr;
        }  
        data[0] = val;
        this->_size++;
	}
	
    //  POP FRONT O(N)
    void pop_front() {
		for (int i = 0; i < _capacity - 1; i++)
			data[i] = data[i + 1];
		_size--;
	}
	
    //  INSERT AT INDEX O(N)
    void insert_at_index(const T& val, int index) {
		if (index < 0 || index >= _capacity) 
            return;
        if (_size == _capacity) {
            T* newdata = new T[_capacity + 10];
            for (int i = 0; i < _capacity; i++) {
                newdata[i] = data[i];
            }
            _capacity += 10;
            delete data;
            data = nullptr;
            data = newdata;
        }
		for (int i = _capacity - 1; i > index; i--)
			data[i] = data[i - 1];

        data[index] = val; 
		_size++;
	}

    void set_at_index(const T& val, int index) {
        if (index >= _capacity || index < 0) {
            return;
        }else{
            this->data[index] = val;
            if (index >= _size) {
                _size = index + 1;
            }
        }
    }

    //  REMOVE AT INDEX O(N) 
    void remove_at_index(int idx) {
        if (idx < 0 || idx >= _size) {
            return;
        }
        for (int i = idx; i < _size; i++) {
            data[i] = data[ i + 1];
        }
        _size--;
    }

    //  REMOVE ALL
   	void removeAll() {
        if (this->data != nullptr) {
            delete[] data;
            data = nullptr;
            _capacity = 0;
            _size = 0;
        }
	}

    //  GETTERS
	int size() const {
		return this->_size;
	}
    int capacity() const {
		return this->_capacity;
	}
	

    //  OPERATOR OVERLOADING
    
	T& operator [] (int i) {
		if (i >= _capacity || i < 0) {
			cout << "OUT OF BOUNDS";
			exit(-1);
		}
		return data[i];
	}
	T& operator [] (int i) const {
		if (i >= _capacity || i < 0) {
			cout << "OUT OF BOUNDS";
				exit(-1);
		}
		return data[i];
	}
	

};
