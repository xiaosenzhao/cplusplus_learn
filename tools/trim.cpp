#include <iostream>
#include <string>
#include <algorithm>
#include <regex>
#include <chrono>
//#include <boost/algorithm/string/trim.hpp>

namespace one {
// \n 换行
// \r 回车
// \f 换页
// \t 水平制表
// \v 垂直制表
const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string& s) {
  size_t start = s.find_first_not_of(WHITESPACE);
  return (start == std::string::npos) ? s : s.substr(start);
}

std::string rtrim(const std::string& s) {
  size_t end = s.find_last_not_of(WHITESPACE);
  return (end == std::string::npos) ? s : s.substr(0, end + 1);
}

std::string trim(const std::string& s) {
  return rtrim(ltrim(s));
}

} // namespace one

namespace two {
std::string& ltrim(std::string& s) {
  auto it = std::find_if(s.begin(), s.end(),
                         [](char c) {
                            return !std::isspace<char>(c, std::locale::classic());
                         });
  s.erase(s.begin(), it);
  return s;
}

std::string& rtrim(std::string& s) {
  auto it = std::find_if(s.rbegin(), s.rend(),
                         [](char c) {
                            return !std::isspace<char>(c, std::locale::classic());
                         });
  s.erase(it.base(), s.end());
  return s;
}

std::string& trim(std::string& s) {
  return ltrim(rtrim(s));
}

} // namespace two

namespace three {
std::string trim(const std::string& s) {
  auto start = s.begin();
  while (start != s.end() && std::isspace(*start)) {
    start++;
  }

  auto end = s.end();
  do {
    end--;
  } while (end != s.begin() && std::isspace(*end));

  return std::string(start, end + 1);
}
} // namespace three

namespace four {
std::string ltrim(const std::string& s) {
  return std::regex_replace(s, std::regex("^\\s+"), std::string(""));
}

std::string rtrim(const std::string& s) {
  return std::regex_replace(s, std::regex("\\s+$"), std::string(""));
}

std::string trim(const std::string& s) {
  return ltrim(rtrim(s));
}
} // namespace four

namespace five {

//boost::algorithm::trim(s);

} // namespace five

int main(void) {
  std::string s1 = "\n\t Hello World  \r\n";
  auto start1 = std::chrono::steady_clock::now();
  for (int i = 0; i < 10000; i++) {
    one::trim(s1);
  }
  auto end1 = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_seconds1 = end1 - start1;

  std::string s2 = "\n\t Hello World  \r\n";
  auto start2 = std::chrono::steady_clock::now();
  for (int i = 0; i < 10000; i++) {
    two::trim(s2);
  }
  auto end2 = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_seconds2 = end2 - start2;

  std::string s3 = "\n\t Hello World  \r\n";
  auto start3 = std::chrono::steady_clock::now();
  for (int i = 0; i < 10000; i++) {
    three::trim(s3);
  }
  auto end3 = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_seconds3 = end3 - start3;

  std::string s4 = "\n\t Hello World  \r\n";
  auto start4 = std::chrono::steady_clock::now();
  for (int i = 0; i < 10000; i++) {
    four::trim(s4);
  }
  auto end4 = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_seconds4 = end4 - start4;

  std::cout << "one: " << elapsed_seconds1.count() << std::endl;
  std::cout << "tow: " << elapsed_seconds2.count() << std::endl;
  std::cout << "three: " << elapsed_seconds3.count() << std::endl;
  std::cout << "four: " << elapsed_seconds4.count() << std::endl;

  return 0;
}

