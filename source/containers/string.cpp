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

#include <flux/containers/string.hpp> 

namespace fl::containers {

  string::string()
      : m_ascii_string(nullptr)
      , m_size(0)
      , m_capacity(0) {}

  string::string(const char* ascii_string) 
      : m_size(strlen(ascii_string))
      , m_capacity(m_size + 1) { 

        m_ascii_string = new char[m_capacity]{};

        strcpy(m_ascii_string, ascii_string);
      }

  string::string(const string& string_object) 
      : m_size(string_object.m_size)
      , m_capacity(string_object.m_capacity) {

        m_ascii_string = new char[m_capacity]{};

        strcpy(m_ascii_string, string_object.m_ascii_string);
      }

  string::string(std::initializer_list<char> initializer_list) 
      : m_size(initializer_list.size())
      , m_capacity(m_size + 1) {
    
        m_ascii_string = new char[m_capacity]{};

        std::copy(initializer_list.begin(), initializer_list.end(), m_ascii_string);
      }
  
  string::~string() {
    delete[] m_ascii_string;
  }
  
  size_t string::length() const {
    return m_size;
  }

  size_t string::capacity() const { 
    return m_capacity;
  }

  char& string::front() {
    return m_ascii_string[0];
  }
  
  const char& string::front() const {
    return m_ascii_string[0];
  }

  char& string::back() {
    return m_ascii_string[m_size - 1];
  }

  const char& string::back() const {
    return m_ascii_string[m_size - 1];
  }
  
  char& string::at(const size_t& index_of_element) {
    if(index_of_element >= m_size) {
      throw std::out_of_range("Out of range!");
    }
    
    return m_ascii_string[index_of_element];
  }

  const char& string::at(const size_t& index_of_element) const {
    if(index_of_element >= m_size) {
      throw std::out_of_range("Out of range!");
    }
    
    return m_ascii_string[index_of_element];
  }

  bool string::empty() const {
    if(m_ascii_string != nullptr) {
      return false;
    }

    return true;
  }

  void string::clear() {
    if(m_ascii_string == nullptr) {
      return;
    }

    memset(m_ascii_string, 0, m_size);
  }

  void string::shrink_to_fit() {
    if(m_ascii_string != nullptr) {
      delete[] m_ascii_string;
    }
    
    m_ascii_string = nullptr;
    m_size = 0;
    m_capacity = 0;
  }
  
  void string::resize(const size_t& size_of_reallocated, char fill_character) {   
    if(size_of_reallocated <= m_size) {
      m_size = size_of_reallocated;
      memmove(m_ascii_string, m_ascii_string, size_of_reallocated);                    
      m_ascii_string[m_size] = '\0';
      return; 
    }
    
    char* buf {new char[m_capacity]{}};
    size_t buf_length {m_size};  

    strcpy(buf, m_ascii_string);

    shrink_to_fit();   
  
    m_size = size_of_reallocated;
    m_capacity = m_size + 1;
    m_ascii_string = new char[m_capacity]{};

    strcpy(m_ascii_string, buf);
  
    memset(m_ascii_string + buf_length, fill_character, m_size - buf_length); 
    
    delete[] buf; 
  }
  
  void string::reserve(const size_t& reserve_size) {
    if(reserve_size <= m_capacity) {
      return;  
    } 
    
    char* buf {new char[reserve_size]{}};

    if(m_ascii_string != nullptr) {
      strcpy(buf, m_ascii_string);
      delete[] m_ascii_string; 
    }
  
    m_capacity = reserve_size; 
    m_ascii_string = new char[m_capacity]{};
    
    strcpy(m_ascii_string, buf);

    delete[] buf; 
  }
  
  std::ostream& operator<<(std::ostream& ostream, const string& string_object) {
    return ostream << string_object.m_ascii_string;
  } 

  std::istream& operator>>(std::istream& istream, string& string_object) {
    // TODO
  }
  
  string operator+(const string& first_string_object, const string& second_string_object) {
    string copy {first_string_object};
    copy += second_string_object;
    return copy; 
  }
  
  string operator+(const string& string_object, const char* ascii_string) { 
    string copy {string_object}; 
    copy += ascii_string; 
    return copy;
  }
  
  string& string::operator+=(const char* ascii_string) {
    char* buf {new char[m_capacity]{}};

    if(m_ascii_string != nullptr) { 
      strcpy(buf, m_ascii_string); 
      delete[] m_ascii_string;
    }

    m_size += strlen(ascii_string); 
    m_capacity += (m_size + 1);

    m_ascii_string = new char[m_capacity]{};
    
    strcpy(m_ascii_string, buf);
    strcat(m_ascii_string, ascii_string);
  
    delete[] buf; 
   
    return *this;
  }

  string& string::operator+=(const string& string_object) {
    char* buf {new char[m_capacity]{}};
    
    if(m_ascii_string != nullptr) { 
      strcpy(buf, m_ascii_string);
      delete[] m_ascii_string;
    }
    
    m_size += string_object.m_size;
    m_capacity += string_object.m_capacity;
    
    m_ascii_string = new char[m_capacity]{};
      
    strcpy(m_ascii_string, buf);
    strcat(m_ascii_string, string_object.m_ascii_string);  
    
    delete[] buf; 
    
    return *this;
  }
  
  string& string::operator=(const string& string_object) & {
    if(this == &string_object) {
      return *this;
    }

    if(m_ascii_string != nullptr) {
      delete[] m_ascii_string; 
    }

    m_size = string_object.m_size;
    m_capacity = string_object.m_capacity;

    m_ascii_string = new char[m_capacity]{}; 
    
    strcpy(m_ascii_string, string_object.m_ascii_string);

    return *this;
  }

  char& string::operator[](const size_t& array_index) {
    return m_ascii_string[array_index];
  }

  const char& string::operator[](const size_t& array_index) const {
    return m_ascii_string[array_index];
  }

  bool string::operator==(const string& string_object) const { 
    return strcmp(m_ascii_string, string_object.m_ascii_string) == 0 ? true: false;
  }
  
  bool string::operator!=(const string& string_object) const { 
    return strcmp(m_ascii_string, string_object.m_ascii_string) == 0 ? false: true;
  }
  
} // fl::containers


