# cf_atomic_ptr_get | [atomic](https://github.com/RandyGaul/cute_framework/blob/master/docs/atomic/README.md) | [cute_multithreading.h](https://github.com/RandyGaul/cute_framework/blob/master/include/cute_multithreading.h)

Atomically fetches the value at `atomic`.

```cpp
void* cf_atomic_ptr_get(void** atomic);
```

Parameters | Description
--- | ---
atomic | The pointer to fetch from.

## Remarks

Atomics are an advanced topic. You've been warned! Beej has a [good article on atomics](https://beej.us/guide/bgc/html/split/chapter-atomics.html).

## Related Pages

[cf_atomic_zero](https://github.com/RandyGaul/cute_framework/blob/master/docs/atomic/cf_atomic_zero.md)  
[cf_atomic_add](https://github.com/RandyGaul/cute_framework/blob/master/docs/atomic/cf_atomic_add.md)  
[cf_atomic_set](https://github.com/RandyGaul/cute_framework/blob/master/docs/atomic/cf_atomic_set.md)  
[cf_atomic_get](https://github.com/RandyGaul/cute_framework/blob/master/docs/atomic/cf_atomic_get.md)  
[cf_atomic_cas](https://github.com/RandyGaul/cute_framework/blob/master/docs/atomic/cf_atomic_cas.md)  
[cf_atomic_ptr_set](https://github.com/RandyGaul/cute_framework/blob/master/docs/atomic/cf_atomic_ptr_set.md)  
[cf_atomic_ptr_cas](https://github.com/RandyGaul/cute_framework/blob/master/docs/atomic/cf_atomic_ptr_cas.md)  
