#include <algorithm>
#include <iostream>
#include <string>

#include "minijson.h"
using namespace minijson;

static void parse_json(const uint8_t* data, size_t size) {
	value v;
	std::string s(data, data + size);

	const char* ptr = s.c_str();
	error e = parse_string(ptr, v);
	(void)e;

	return;
}

extern "C" int LLVMFuzzerTestOneInput(std::uint8_t const* data,
				      std::size_t size) {
	parse_json(data, size);
	return 0;
}
