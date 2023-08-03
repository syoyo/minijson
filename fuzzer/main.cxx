#include <algorithm>
#include <iostream>
#include <string>

#include "minijson.h"
using namespace minijson;

static int parse_json(const uint8_t* data, size_t size) {
	if (size < 2) {
		return - 1;
	}

	value v;
	std::string s(data, data + size);

	const char* ptr = s.c_str();
	error e = parse(ptr, v);
	(void)e;

	return 0;
}

extern "C" int LLVMFuzzerTestOneInput(std::uint8_t const* data,
				      std::size_t size) {
	int ret = parse_json(data, size);
	return ret;
}
