#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

#define MINIJSON_IMPLEMENTATION
#include "minijson.h"

using namespace minijson;

int main(int argc, char** argv) {
  if (argc > 1) {
    std::ifstream ifs(argv[1]);
    if (!ifs) {
      std::cerr << "file not found or open file failed: " << argv[1] << "\n";
      return -1;
    }

    std::stringstream buf;
    buf << ifs.rdbuf();
    std::string s = buf.str();

    const char* startp = s.c_str();
    const char* p = s.c_str();
    value v;
    error e = parse(p, v);
    if (e != no_error) {
      std::cerr << errstr(e) << "(" << int(p - startp) << "):" << p << std::endl;
      return 1;
    }
    std::cout << v.str() << std::endl;
    return 0;
  }
  const char* foo = R"(
{"empty":{"":[]}, "foo":
3.2, "bar": "baz", "baz": true,"hoge":{"a":"あい\nうおえ"}, "moge": null, "zz": 255
, "rrr":[[2,"3"], "4"], "fuba": 1e9}
)";
  const char* p = foo;
  value v;
  error e = parse(p, v);
  if (e != no_error) {
    std::cerr << errstr(e) << "(" << int(p - foo) << "):" << p << std::endl;
    return 1;
  }
  std::cout << v.str() << std::endl;
  while (*p && strchr("\r\n \t", *p)) {
    p++;
  }
  if (*p) {
    std::cerr << "invalid token: " << p << std::endl;
    return 1;
  }

  if (object* po = v.as<object>()) {
    po->insert("momo", "3.0");

    if (po->count("rrr")) {
      value av;
      if (po->at("rrr", &av)) {
        if (array* pa = av.as<array>()) {
          pa->push_back("3.0");
          pa->push_back(null_t());
          po->insert("rrr", *pa);

          po->erase("foo");
        }
      }
    }
  }

  {
    std::string utf8_escaped = "{\"key\": \"\u3042\\n\"}";
    const char* up = utf8_escaped.c_str();
    error e = parse(up, v);
    if (e != no_error) {
      std::cerr
          << "Parsing JSON which contains unicode escape sequences failed.\n";
      std::cerr << errstr(e) << "(" << int(p - foo) << "):" << p << std::endl;
      return -1;
    } else {
      std::cout << v.str() << std::endl;
    }
  }
  return 0;
}
