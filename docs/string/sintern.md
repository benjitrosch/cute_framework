# sintern | [string](https://github.com/RandyGaul/cute_framework/blob/master/docs/string/README.md) | [cute_string.h](https://github.com/RandyGaul/cute_framework/blob/master/include/cute_string.h)

Stores unique, static copy of a string in a global string interning table.

```cpp
#define sintern(s) cf_sintern(s)
```

Parameters | Description
--- | ---
s | The string to insert into the global table.

## Return Value

Returns a static, unique, stable, read-only copy of the string. The pointer is stable until [sinuke](https://github.com/RandyGaul/cute_framework/blob/master/docs/string/sinuke.md) is called.

## Remarks

Only one copy of each unique string is stored. The purpose is primarily a memory optimization to reduce duplicate strings.
You can not modify this string in any way. It is 100% immutable. Some major benefits come from placing strings into this
table.

- You can hash returned pointers directly into hash tables (instead of hashing the entire string).
- You can simply compare pointers for equality, as opposed to comparing the string contents, as long as both strings came from this function.
- You may optionally call [sinuke](https://github.com/RandyGaul/cute_framework/blob/master/docs/string/sinuke.md) to free all resources used by the global string table.
- This function is very fast if the string was already stored previously.

## Related Pages

[sinuke](https://github.com/RandyGaul/cute_framework/blob/master/docs/string/sinuke.md)  
[sintern_range](https://github.com/RandyGaul/cute_framework/blob/master/docs/string/sintern_range.md)  
[sivalid](https://github.com/RandyGaul/cute_framework/blob/master/docs/string/sivalid.md)  
[silen](https://github.com/RandyGaul/cute_framework/blob/master/docs/string/silen.md)  
