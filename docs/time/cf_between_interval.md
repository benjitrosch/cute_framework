# cf_between_interval | [time](https://github.com/RandyGaul/cute_framework/blob/master/docs/time/README.md) | [cute_time.h](https://github.com/RandyGaul/cute_framework/blob/master/include/cute_time.h)

Returns true for one interval of seconds, every other interval.

```cpp
bool cf_between_interval(float interval, float offset);
```

Parameters | Description
--- | ---
interval | Number of seconds between each interval.
offset | An offset of seconds used to offset within the interval of [0,interval]. This gets mathematically mod'd,
           so it can be any number of seconds.

## Remarks

This function is super useful for general purpose gameplay implementation where you want an event to fire for N seconds,
and then _not_ fire for N seconds, flipping back and forth periodically. Simply place this within an if-statement!

## Related Pages

[cf_on_interval](https://github.com/RandyGaul/cute_framework/blob/master/docs/time/cf_on_interval.md)  
[cf_on_timestamp](https://github.com/RandyGaul/cute_framework/blob/master/docs/time/cf_on_timestamp.md)  
