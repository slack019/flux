// MIT License
// 
// Copyright (c) 2025 @slack019
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <flux/containers/vector.hpp> 

namespace fl::containers { 
  
  template <typename T> 
  vector<T>::vector() 
      : m_size(0)
      , m_capacity(0) 
      , m_buffer(nullptr) {} 
  
  template <typename T>
  vector<T>::vector(const vector<T>& vector_object) 
      : m_size(vector_object.m_size)
      , m_capacity(vector_object.m_capacity) { 
        
        m_buffer = new T[m_capacity];
          
        memcpy(m_buffer, vector_object.m_buffer, m_size); 
      }
  
  template <typename T> 
  vector<T>::vector(const size_t& size_of_array)
      : m_size(size_of_array)
      , m_capacity(size_of_array) { 
  
        m_buffer = new T[m_capacity];   
      }

  template <typename T> 
  vector<T>::vector(const size_t& size_of_array, const T& initial)
      : m_size(size_of_array)
      , m_capacity(size_of_array) { 
        
        m_buffer = new T[m_capacity];
        
        memset(m_buffer, initial, m_size); 
      }
  
  template <typename T> 
  vector<T>::vector(std::initializer_list<T> initializer_list)
      : m_size(initializer_list.size())
      , m_capacity(initializer_list.size()) { 

        m_buffer = new T[m_capacity];
        
        
        std::copy(initializer_list.begin(), initializer_list.end(), m_buffer);
      }

  template <typename T> 
  vector<T>::~vector() { 
    delete[] m_buffer; 
  }

  template <typename T> 
  size_t vector<T>::capacity() const { 
    return m_capacity;
  }
  
  template <typename T>
  size_t vector<T>::size() const {
    return m_size; 
  }
  
  template <typename T> 
  bool vector<T>::empty() const { 
    if(m_buffer != nullptr) {
      return false; 
    }
    return true; 
  }

  template <typename T> 
  typename vector<T>::iterator vector<T>::begin() { 
    return m_buffer; 
  }

  template <typename T> 
  typename vector<T>::iterator vector<T>::end() { 
    return m_buffer + size(); 
  }

  template <typename T> 
  T& vector<T>::front() { 
    return m_buffer[0]; 
  }
  
  template <typename T> 
  const T& vector<T>::front() const { 
    return m_buffer[0];
  }

  template <typename T> 
  T& vector<T>::back() { 
    return m_buffer[m_size - 1];
  }

  template <typename T> 
  const T& vector<T>::back() const {
    return m_buffer[m_size - 1];  
  }
  
  template <typename T> 
  T& vector<T>::at(const size_t& index_of_element) { 
    if(index_of_element >= m_size) {
      throw std::out_of_range("Out of range!");
    }

    return m_buffer[index_of_element];
  }

  template <typename T> 
  const T& vector<T>::at(const size_t& index_of_element) const {
    if(index_of_element >= m_size) {
      throw std::out_of_range("Out of range!");
    }

    return m_buffer[index_of_element];
  }

  template <typename T> 
  void vector<T>::push_back(const T& element_of_array) {
    if(m_size >= m_capacity) { 
      reserve(m_capacity + 5);
    }

    m_buffer[++m_size] = element_of_array;
  }  

  template <typename T> 
  void vector<T>::pop_back() { 
    --m_size;
  }
  
  template <typename T> 
  void vector<T>::reserve(const size_t& new_size) { 
    if(new_size <= m_capacity) { 
      return;
    }

    T* buffer {new T[m_capacity]};

    if(m_buffer != nullptr) {
      memcpy(buffer, m_buffer, m_size);
      delete[] m_buffer; 
    }

    m_capacity = new_size; 
    m_size = new_size; 
    m_buffer = new T[m_capacity]; 

    memcpy(m_buffer, buffer); 

    delete[] buffer;
  }
  
  template <typename T> 
  void vector<T>::resize(const size_t& new_size, char fill_character) { 
    if(new_size <= m_size) {
      m_size = new_size; 
      memmove(m_buffer, m_buffer, m_size);    
      return; 
    }

    T* buffer {new T[m_capacity]};
    size_t buf_length {m_size};  

    memcpy(buffer, m_buffer, m_size);
  
    delete[] m_buffer;
    
    m_size = new_size;
    m_capacity = new_size;
    m_buffer = new T[m_capacity];
    
    memcpy(m_buffer, buffer, buf_length); 

    memset(m_buffer + buf_length, fill_character, m_size - buf_length);

    delete[] buffer;
  }

  template <typename T> 
  vector<T>& vector<T>::operator=(const vector<T>& vector_object) {
    if(this == &vector_object) {
      return *this; 
    }

    if(m_buffer != nullptr) { 
      delete[] m_buffer; 
    }
  
    m_size = vector_object.m_size; 
    m_capacity = vector_object.m_capacity; 
    m_buffer = new T[m_capacity]; 

    memcpy(m_buffer, vector_object.m_buffer); 

    return *this; 
  }

  template <typename T> 
  T& vector<T>::operator[](const size_t& index_of_element) {
    return m_buffer[index_of_element];
  }
    
  template <typename T> 
  const T& vector<T>::operator[](const size_t& index_of_element) const {
    return m_buffer[index_of_element];
  }
  
}
