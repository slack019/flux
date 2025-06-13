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

#ifndef FLUX_STRING_ASSET_HPP
#define FLUX_STRING_ASSET_HPP

#define FLUX_STATIC_DEFINE 1

#include <initializer_list> // for std::initializer_list
#include <algorithm> // for std::min, std::max
#include <utility> // for std::swap, std::move
#include <compare> // for std::strong_ordering
#include <istream> 
#include <ostream> 

#include <cstddef> 
#include <cstring> 

#include <flux/export-flux.hpp>

namespace fl::containers { 
  
  class string final { 
  private: 
    char* m_ascii_string;
    size_t m_size;
    size_t m_capacity;
  public: 
    string(); 
    string(const char*);
    string(const string&);
    string(std::initializer_list<char>);
    ~string();
  public: 
    size_t length() const; 
    size_t capacity() const; 
    char& front();
    const char& front() const;
    char& back();
    const char& back() const;
    char& at(const size_t&);
    const char& at(const size_t&) const;
    void clear();
    void shrink_to_fit();
    void resize(const size_t&, char = 0);
    void reserve(const size_t& = 0);
    bool empty() const;
  public: 
    friend std::ostream& operator<<(std::ostream&, const string&);
    friend std::istream& operator>>(std::istream&, string&);
    friend string operator+(const string&, const string&);
    friend string operator+(const string&, const char*); 
    string& operator+=(const string&); 
    string& operator+=(const char*);
    string& operator=(const string&) &;
    char& operator[](const size_t&);
    const char& operator[](const size_t&) const;
    bool operator==(const string&) const;
    bool operator!=(const string&) const;
  };
  
} // fl::containers 

#endif
