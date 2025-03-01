# cf_on_timestamp | [time](https://github.com/RandyGaul/cute_framework/blob/master/docs/time/README.md) | [cute_time.h](https://github.com/RandyGaul/cute_framework/blob/master/include/cute_time.h)

Returns true for one frame where a specific timestamp (relative to program start) occurs.

```cpp
bool cf_on_timestamp(double timestamp);
```

Parameters | Description
--- | ---
timestamp | The timestamp.

## Remarks

This function is super useful for general purpose gameplay implementation where you want an event to fire at N seconds
(since program start). Simply place this within an if-statement!

## Related Pages

[cf_on_interval](https://github.com/RandyGaul/cute_framework/blob/master/docs/time/cf_on_interval.md)  
[cf_between_interval](https://github.com/RandyGaul/cute_framework/blob/master/docs/time/cf_between_interval.md)  
