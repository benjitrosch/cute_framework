# sappend_UTF8 | [string](https://github.com/RandyGaul/cute_framework/blob/master/docs/string/README.md) | [cute_string.h](https://github.com/RandyGaul/cute_framework/blob/master/include/cute_string.h)

Appends a UTF32 codepoint (as `uint32_t`) encoded as UTF8 onto the string.

```cpp
#define sappend_UTF8(s, codepoint) cf_string_append_UTF8(s, codepoint)
```

Parameters | Description
--- | ---
s | The string. Can be `NULL`.
codepoint | An `int` codepoint in UTF32 form.

## Code Example

> Example of suggested way to use this function within a loop.

```cpp
char s = NULL;
while (has_codepoint()) {
    sappend_UTF8(s, get_codepoint());
}
sfree(s);
```

## Remarks

The UTF8 bytes are appended onto the string.

Each UTF32 codepoint represents a single character. Each character can be encoded from 1 to 4
bytes. Therefor, this function will push 1 to 4 bytes onto the string.

If an invalid codepoint is found the "replacement character" 0xFFFD will be appended instead, which
looks like question mark inside of a dark diamond.

## Related Pages

[cf_decode_UTF16](https://github.com/RandyGaul/cute_framework/blob/master/docs/string/cf_decode_utf16.md)  
[cf_decode_UTF8](https://github.com/RandyGaul/cute_framework/blob/master/docs/string/cf_decode_utf8.md)  
