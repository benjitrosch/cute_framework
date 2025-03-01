# cf_kv_last_error | [serialization](https://github.com/RandyGaul/cute_framework/blob/master/docs/serialization/README.md) | [cute_kv.h](https://github.com/RandyGaul/cute_framework/blob/master/include/cute_kv.h)

Returns the error state of the kv instance.

```cpp
CF_Result cf_kv_last_error(CF_KeyValue* kv);
```

Parameters | Description
--- | ---
kv | The kv instance.

## Remarks

You can use this try and get a more useful description of what may have went wrong. These errors are not fatal.
For example if you search for a key with [cf_kv_key](https://github.com/RandyGaul/cute_framework/blob/master/docs/serialization/cf_kv_key.md) and it's non-existent a potentially useful error message may be
generated, but you can still keep going and look for other keys freely.

## Related Pages

TODO_KV_TUTORIAL_LINK  
[CF_KeyValue](https://github.com/RandyGaul/cute_framework/blob/master/docs/serialization/cf_keyvalue.md)  
[cf_kv_read](https://github.com/RandyGaul/cute_framework/blob/master/docs/serialization/cf_kv_read.md)  
[cf_kv_write](https://github.com/RandyGaul/cute_framework/blob/master/docs/serialization/cf_kv_write.md)  
[cf_kv_key](https://github.com/RandyGaul/cute_framework/blob/master/docs/serialization/cf_kv_key.md)  
