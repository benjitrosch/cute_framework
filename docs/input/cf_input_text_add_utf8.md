# cf_input_text_add_utf8 | [input](https://github.com/RandyGaul/cute_framework/blob/master/docs/input/README.md) | [cute_input.h](https://github.com/RandyGaul/cute_framework/blob/master/include/cute_input.h)

Adds a utf8 codepoint to the input buffer of the application.

```cpp
void cf_input_text_add_utf8(const char* text);
```

## Remarks

The input text functions are for dealing with text input. Not all text inputs come from a single key-stroke, as some are comprised of
multiple keystrokes, especially when dealing with non-Latin based inputs.

## Related Pages

[cf_input_text_clear](https://github.com/RandyGaul/cute_framework/blob/master/docs/input/cf_input_text_clear.md)  
[cf_input_text_pop_utf32](https://github.com/RandyGaul/cute_framework/blob/master/docs/input/cf_input_text_pop_utf32.md)  
[cf_input_text_has_data](https://github.com/RandyGaul/cute_framework/blob/master/docs/input/cf_input_text_has_data.md)  
