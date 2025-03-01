# CF_Coroutine | [coroutine](https://github.com/RandyGaul/cute_framework/blob/master/docs/coroutine/README.md) | [cute_coroutine.h](https://github.com/RandyGaul/cute_framework/blob/master/include/cute_coroutine.h)

An opaque handle representing a coroutine.

## Remarks

A coroutine is a function that can be paused and resumed. Coroutines are often used as an alternative
way to implement state machines, or create gameplay-helper tools for control code logic/flow. Once a coroutine
is created with [cf_make_coroutine](https://github.com/RandyGaul/cute_framework/blob/master/docs/coroutine/cf_make_coroutine.md) call [cf_coroutine_resume](https://github.com/RandyGaul/cute_framework/blob/master/docs/coroutine/cf_coroutine_resume.md) to start running it. At any moment the coroutine
can pause itself with [cf_coroutine_yield](https://github.com/RandyGaul/cute_framework/blob/master/docs/coroutine/cf_coroutine_yield.md). Then, later, someone else can call [cf_coroutine_resume](https://github.com/RandyGaul/cute_framework/blob/master/docs/coroutine/cf_coroutine_resume.md). The coroutine
will then continue running just after the last call to [cf_coroutine_yield](https://github.com/RandyGaul/cute_framework/blob/master/docs/coroutine/cf_coroutine_yield.md). This makes a coroutine great for
preserving state between yield/resume calls, for example to perform some complex action over multiple frames.

## Related Pages

[cf_coroutine_currently_running](https://github.com/RandyGaul/cute_framework/blob/master/docs/coroutine/cf_coroutine_currently_running.md)  
[CF_CoroutineFn](https://github.com/RandyGaul/cute_framework/blob/master/docs/coroutine/cf_coroutinefn.md)  
[CF_CoroutineState](https://github.com/RandyGaul/cute_framework/blob/master/docs/coroutine/cf_coroutinestate.md)  
[cf_make_coroutine](https://github.com/RandyGaul/cute_framework/blob/master/docs/coroutine/cf_make_coroutine.md)  
[cf_destroy_coroutine](https://github.com/RandyGaul/cute_framework/blob/master/docs/coroutine/cf_destroy_coroutine.md)  
[cf_coroutine_state_to_string](https://github.com/RandyGaul/cute_framework/blob/master/docs/coroutine/cf_coroutine_state_to_string.md)  
[cf_coroutine_resume](https://github.com/RandyGaul/cute_framework/blob/master/docs/coroutine/cf_coroutine_resume.md)  
[cf_coroutine_yield](https://github.com/RandyGaul/cute_framework/blob/master/docs/coroutine/cf_coroutine_yield.md)  
[cf_coroutine_state](https://github.com/RandyGaul/cute_framework/blob/master/docs/coroutine/cf_coroutine_state.md)  
[cf_coroutine_get_udata](https://github.com/RandyGaul/cute_framework/blob/master/docs/coroutine/cf_coroutine_get_udata.md)  
[cf_coroutine_push](https://github.com/RandyGaul/cute_framework/blob/master/docs/coroutine/cf_coroutine_push.md)  
[cf_coroutine_pop](https://github.com/RandyGaul/cute_framework/blob/master/docs/coroutine/cf_coroutine_pop.md)  
[cf_coroutine_bytes_pushed](https://github.com/RandyGaul/cute_framework/blob/master/docs/coroutine/cf_coroutine_bytes_pushed.md)  
[cf_coroutine_space_remaining](https://github.com/RandyGaul/cute_framework/blob/master/docs/coroutine/cf_coroutine_space_remaining.md)  
