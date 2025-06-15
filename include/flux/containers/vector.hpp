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

#ifndef FLUX_VECTOR_ASSET_HPP
#define FLUX_VECTOR_ASSET_HPP

#define FLUX_STATIC_DEFINE 1

#include <initializer_list>
#include <ostream> 
#include <istream> 
#include <algorithm>

#include <cstddef>  

#include <flux/export-flux.hpp> 

namespace fl::containers { 
  
  template <typename T> 
  class vector final { 
  private: 
    T* m_buffer; 
    size_t m_size; 
    size_t m_capacity; 
  public: 
    using iterator = T*;   

    vector(); 
    vector(const size_t&); 
    vector(const size_t&, const T&); 
    vector(const vector<T>&); 
    vector(std::initializer_list<T>); 
    ~vector(); 
  public: 
    size_t capacity() const; 
    size_t size() const; 
    bool empty() const; 
    iterator begin(); 
    iterator end(); 
    T& front(); 
    const T& front() const; 
    T& back(); 
    const T& back() const; 
    T& at(const size_t&);
    const T& at(const size_t&) const; 
    void push_back(const T&); 
    void pop_back();
    void reserve(const size_t&); 
    void resize(const size_t&, char = 0); 
  public: 
    vector<T>& operator=(const vector<T>&); 
    T& operator[](const size_t&); 
    const T& operator[](const size_t&) const; 
  };

}

#endif
