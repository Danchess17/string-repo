#include <cstring>
#include <iostream>

class String {
 public:
  String() : len_(0), capacity_(0), str_(nullptr) {}
  String(const char* s)
      : len_(strlen(s)), capacity_(len_), str_(new char[len_]) {
    memcpy(str_, s, len_);
  }
  String(size_t n, char c) : len_(n), capacity_(n), str_(new char[n]) {
    memset(str_, c, len_);
  }
  String(const String& s)
      : len_(s.len_), capacity_(s.capacity_), str_(new char[s.len_]) {
    memcpy(str_, s.str_, len_);
  }
  ~String() { delete[] str_; }
  String& operator=(const String& s) {
    String string(s);
    swap(string);
    return *this;
  }
  size_t length() const { return len_; }
  bool empty() const { return (len_ == 0); }
  const char& front() const { return str_[0]; }
  char& front() { return str_[0]; }
  const char& back() const { return str_[len_ - 1]; }
  char& back() { return str_[len_ - 1]; }
  void push_back(char c) {
    if (len_ == capacity_) {
      set_new_capacity(2 * capacity_);
    }
    str_[len_++] = c;
  }
  void pop_back() { len_--; }
  const char& operator[](size_t index) const { return str_[index]; }
  char& operator[](size_t index) { return str_[index]; }
  String& operator+=(const String& s) {
    set_new_capacity(len_ + s.length());
    memcpy(str_ + len_, s.str_, s.length());
    len_ += s.length();
    return *this;
  }
  String& operator+=(char c) {
    push_back(c);
    return *this;
  }
  bool is_substr(size_t start, size_t count, const String& s) const {
    return (memcmp(s.str_, str_ + start, count) == 0);
  }
  size_t find(const String& substring) const {
    for (size_t i = 0; i + substring.length() <= len_; ++i) {
      if (is_substr(i, substring.length(), substring)) {
        return i;
      }
    }
    return len_;
  }
  size_t rfind(const String& substring) const {
    for (int i = len_ - substring.length(); i >= 0; --i) {
      if (is_substr(i, substring.length(), substring)) {
        return static_cast<size_t>(i);
      }
    }
    return len_;
  }
  String substr(size_t start, size_t count) const {
    String substring(count, '0');
    memcpy(substring.str_, str_ + start, count);
    return substring;
  }
  void clear() {
    delete[] str_;
    str_ = nullptr;
    len_ = 0;
    capacity_ = 0;
  }
  bool operator==(const String& s) {
    if (len_ != s.length()) {
      return false;
    }
    return (memcmp(str_, s.str_, len_) == 0);
  }

 private:
  size_t len_;
  size_t capacity_;
  char* str_;
  void set_new_capacity(size_t new_capacity) {
    char* new_str = new char[new_capacity];
    memcpy(new_str, str_, len_);
    delete[] str_;
    capacity_ = new_capacity;
    str_ = new_str;
  }
  void swap(String& s) {
    std::swap(str_, s.str_);
    std::swap(len_, s.len_);
    std::swap(capacity_, s.capacity_);
  }
};
std::istream& operator>>(std::istream& in, String& str) {
  str.clear();
  char c;
  do {
    c = in.get();
  } while (isspace(c) != 0);
  while (!in.eof() && (isspace(c) == 0)) {
    str.push_back(c);
    c = in.get();
  }
  return in;
}
std::ostream& operator<<(std::ostream& out, const String& s) {
  for (size_t i = 0; i < s.length(); ++i) {
    out << s[i];
  }
  return out;
}
String operator+(const String& s1, const String& s2) {
  String res = s1;
  res += s2;
  return res;
}
String operator+(char c, const String& s) {
  String res = String(1, c);
  res += s;
  return res;
}
String operator+(const String& s, char c) {
  String res(s);
  res += c;
  return res;
}

