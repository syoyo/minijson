# minijson

minimal JSON parser

## Limitation

* Duplicated key is not allowed

## Usage

```cpp
const char* foo = R"(
{"empty":{"":[]}, "foo":
3.2, "bar": "baz", "baz": true,"hoge":{"a":"あい\nうおえ"}, "moge": null, "zz": 255
, "rrr":[[2,"3"], "4"], "fuba": 1e9}
)";
minijson::error e = minijson::parse(p, v);
```

The pointer p will be shift to the end of token. So it is the caller's responsibility to check whether the extra tokens are treated as errors.

## License

MIT

### Third party licenses

* from_chars Apache 2.0 license.
* to_chars MIT license
* parse escaped characters: nlohmann json. MIT license. https://github.com/nlohmann/json

## Author

Yasuhiro Matsumoto

Modification by Syoyo Fujita.

## TODO

* [x] Unicode escape sequence and other escape characters.
  * Thanks to nlohmann json's scan_string()
* [ ] Harden parse() API
  * Only allow string with length parameter
* [ ] Write robust JSON writer
  * [ ] Escape unicode character

