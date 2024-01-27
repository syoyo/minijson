#include <iostream>
#include <algorithm>

#define MINIJSON_IMPLEMENTATION
#include "minijson.h"

using namespace minijson;

int
main(int /*argc*/, char* /*argv*/[]) {
#ifdef __MINIJSON_LIBERAL
  const char* foo = R"(
{'empty':{"":[]}, "foo":
3.2, "bar": "baz", "baz": true,"hoge":{"a":"あい\nうお\2え"}, "moge": null, "zz": 0xff
, "rrr":[[2,"3"], "4"], "fuba": 1e9,}
)";
#else
  const char* foo = R"(
{"empty":{"":[]}, "foo":
3.2, "bar": "baz", "baz": true,"hoge":{"a":"あい\nうお\2え"}, "moge": null, "zz": 0xff
, "rrr":[[2,"3"], "4"], "fuba": 1e9}
)";
#endif
  const char* p = foo;
  value v;
  error e = parse(p, v);
  if (e != no_error) {
    std::cerr << errstr(e) << "(" << int(p - foo) << "):" << p << std::endl;
    return 1;
  }
  while (*p && strchr("\r\n \t", *p)) { p++; }
  if (*p) {
    std::cerr << "invalid token: " << p << std::endl;
    return 1;
  }

  if (object *po = v.as<object>()) {
    po->insert("momo", "3.0");

    if (po->count("rrr")) {
      value av;
      if (po->at("rrr", &av)) {
        if (array *pa = av.as<array>()) {
	  pa->push_back("3.0");
	  pa->push_back(null_t());
	  po->insert("rrr", *pa);

	  po->erase("foo");
	}
      }
    }
  }
  std::cout << v.str() << std::endl;
  return 0;
}
