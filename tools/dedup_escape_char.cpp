#include <string>
#include <iostream>
#include <sstream>

std::string DedupEscapeCharacters(const std::string& source) {
  std::string dest;
  for (size_t i = 0; i < source.length(); i++) {
    if (source[i] != '\\') {
      dest += source[i];
      continue;
    } else if (source[i] == '\\' && (i + 1) < source.length() && source[i + 1] == 'n') {
      dest += '\n';
      i += 1;
    } else {
      dest += source[i];
    }
  }
  return dest;
}

int main(void) {
  std::string b = "slice_size : 300\\ntime_out : 25\\nservice_list :\\n  - trpc.Serving.\\qqnewsPEAnne1ServerPE.PEService\\t";
  std::string c = DedupEscapeCharacters(b);

  std::cout << b << std::endl;
  std::cout << "===" << std::endl;
  std::cout << c << std::endl;

  return 0;
}
