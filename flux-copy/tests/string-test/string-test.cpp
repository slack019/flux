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
#include <gtest/gtest.h> 

TEST(String, String_length) {
  fl::containers::string string {"Hello!"};
  size_t string_length_expected {6};

  ASSERT_EQ(string_length_expected, string.length());
  ASSERT_EQ('\0', string[string.capacity()]);
}

TEST(String, String_capacity) {
  fl::containers::string string {"Hello!"};
  size_t string_capacity_expected {7};

  ASSERT_EQ(string_capacity_expected, string.capacity());
  ASSERT_EQ('\0', string[string.capacity()]);
}

TEST(String, String_methods_front) {
  const fl::containers::string const_string {"Hello!"};
  fl::containers::string string {"Hello!"};
  char string_character_expected_after_edit {'G'};
  char const_string_character_expected {'H'};

  string.front() = 'G';
  
  ASSERT_EQ(string_character_expected_after_edit, string.front());
  ASSERT_EQ(const_string_character_expected, const_string.front());
}

TEST(String, String_methods_back) {
  const fl::containers::string const_string {"Hello!"};
  fl::containers::string string {"Hello!"};
  char string_character_expected_after_edit {'?'};
  char const_string_character_expected {'!'};

  string.back() = '?';

  ASSERT_EQ(string_character_expected_after_edit, string.back());
  ASSERT_EQ(const_string_character_expected, const_string.back());
}

TEST(String, String_methods_at) {
  const fl::containers::string const_string {"Hello!"};
  fl::containers::string string {"Hello!"};
  char const_string_character_expected {'H'};
  char string_character_expected_after_edit {'G'};

  string.at(0) = 'G';
  
  ASSERT_EQ(string_character_expected_after_edit, string.at(0));
  ASSERT_EQ(const_string_character_expected, const_string.at(0));
  ASSERT_ANY_THROW(string.at(7) = ' ');
}

TEST(String, String_methods_clear) {
  fl::containers::string string {"Hello!"};
  fl::containers::string string_after_clear_method {""};

  string.clear();

  ASSERT_EQ(string_after_clear_method, string);
}

TEST(String, String_methods_shrink_to_fit) {
  fl::containers::string string {"Hello!"};
  size_t expected_capacity {0};

  string.shrink_to_fit();
  
  ASSERT_EQ(expected_capacity, string.capacity());
  ASSERT_TRUE(string.empty());
} 

TEST(String, String_methods_resize) { 
  fl::containers::string string {"Hello!"}; 
  fl::containers::string expected_string_after_method {"Hello!JJJJ"};
  size_t string_size_after_method {10};
  size_t string_capacity_after_method {11};

  string.resize(10, 'J');

  ASSERT_EQ(string_size_after_method, string.length());
  ASSERT_EQ(string_capacity_after_method, string.capacity());
  ASSERT_EQ(expected_string_after_method, string);
}

TEST(String, String_methods_reserve) {
  fl::containers::string string {"Hello"};
  fl::containers::string string_second {"Hello"};
  fl::containers::string string_after_reserve_method {"Hello"};
  size_t string_capacity_after_method {6};
  
  string.reserve(4);
  string_second.reserve(10);

  ASSERT_EQ(string_capacity_after_method, string.capacity());
  ASSERT_EQ(string_after_reserve_method, string);
  ASSERT_EQ(10, string_second.capacity());
}

TEST(String, String_methods_empty) {
  fl::containers::string string;
  bool expected_value {true};

  ASSERT_TRUE(string.empty() == expected_value);
}

// TODO operator>> 

TEST(String, String_operators_operator_plus) {
  fl::containers::string string_first {"Hello"};
  fl::containers::string string_second {", World!"};
  fl::containers::string expected_string {"Hello, World!"};

  string_first = string_first + string_second;
  string_second = string_second + " xD";

  ASSERT_EQ(string_first, expected_string);
  ASSERT_EQ(string_second, ", World! xD");
}

TEST(String, String_operators_operator_plus_eq) {
  fl::containers::string string_first {"Hello!"};
  fl::containers::string string_second {" World!"};
  
  string_first += string_second;
  string_second += " xD";

  ASSERT_EQ(string_first, "Hello! World!");
  ASSERT_EQ(string_second, " World! xD");
}

TEST(String, String_operators_operator_equal) {
  fl::containers::string string;
  fl::containers::string string_first {"Hello World!"};

  string = string_first;

  ASSERT_EQ(string, string_first);
}

TEST(String, String_operators_operator_index) {
  fl::containers::string string {"Hello!"};

  string[0] = 'G';

  ASSERT_EQ(string, "Gello!");
}

TEST(String, String_operators_operator_equal_equal) {
  fl::containers::string string {"Hello"};
  fl::containers::string string_another {"Hello"};  

  ASSERT_TRUE(string == string_another);
}

TEST(String, String_operators_operator_n_eq) {
  fl::containers::string string {"Hello!"};
  fl::containers::string string_another {"Hi!"};

  ASSERT_TRUE(string != string_another);
}
