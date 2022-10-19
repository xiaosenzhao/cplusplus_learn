#include <iostream>
#include <string_view>
#include <vector>

std::vector<std::string_view> Split(const std::string_view& s, char delim, bool keep_empty = false);
std::vector<std::string_view> Split(const std::string_view& s, const std::string_view& delim, bool keep_empty = false);

std::vector<std::string_view> Split(const std::string_view& s, char delim, bool keep_empty) {
  return Split(s, std::string_view(&delim, 1), keep_empty);
}

std::vector<std::string_view> Split(const std::string_view& s, const std::string_view& delim, bool keep_empty) {
  std::vector<std::string_view> splited;
  if (s.empty() || delim.empty()) {
    return splited;
  }

  auto current = s;
  while (true) {
    auto pos = current.find(delim);
    if (pos != 0 || keep_empty) {
      splited.emplace_back(current.substr(0, pos));
    }
    if (pos == std::string_view::npos) {
      break;
    }
    current = current.substr(pos + delim.size());
    if (current.empty()) {
      if (keep_empty) {
        splited.emplace_back("");
      }
      break;
    }
  }
  return splited;
}

int main()
{
  std::string s = "hello world";
  std::vector<std::string_view> tokens = Split(s, ' ');
  for (const auto& token : tokens) {
    std::cout << token << std::endl;
  }

  return 0;
}
