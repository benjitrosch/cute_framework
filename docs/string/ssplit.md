# ssplit | [string](https://github.com/RandyGaul/cute_framework/blob/master/docs/string/README.md) | [cute_string.h](https://github.com/RandyGaul/cute_framework/blob/master/include/cute_string.h)

Splits a string about the character `ch`, scanning from left-to-right.

```cpp
#define ssplit(s, ch) cf_string_split(s, ch)
```

Parameters | Description
--- | ---
s | The string.
ch | A character to split about.

## Return Value

Returns a dynamic array of all delimited strings (see [dyna](https://github.com/RandyGaul/cute_framework/blob/master/docs/array/dyna.md)).

## Code Example

> Splitting a string about '.'.

```cpp
char s = NULL;
sset(s, "split.here.in.a.loop");
const char splits_expected[] = {
    "split",
    "here",
    "in",
    "a",
    "loop",
};
char array_of_splits = ssplit(s, '.');
for (int i = 0; i < alen(array_of_splits); ++i) {
    const char split = array_of_splits[i];
    CUTE_TEST_ASSERT(sequ(split, splits_expected[i]));
    sfree(split);
}
afree(array_of_splits);
```

## Remarks

`s` is not modified. You must call [sfree](https://github.com/RandyGaul/cute_framework/blob/master/docs/string/sfree.md) on the returned strings and [afree](https://github.com/RandyGaul/cute_framework/blob/master/docs/array/afree.md) on the returned array.

## Related Pages

[ssplit_once](https://github.com/RandyGaul/cute_framework/blob/master/docs/string/ssplit_once.md)  
