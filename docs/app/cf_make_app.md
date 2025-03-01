# cf_make_app | [app](https://github.com/RandyGaul/cute_framework/blob/master/docs/app/README.md) | [cute_app.h](https://github.com/RandyGaul/cute_framework/blob/master/include/cute_app.h)

Use this function to construct an instance of your application window and (optionally) initialize graphics.

```cpp
CF_Result cf_make_app(const char* window_title, int x, int y, int w, int h, int options, const char* argv0);
```

Parameters | Description
--- | ---
window_title | The title of the window in utf8 encoding.
x | The x position of the window.
y | The y position of the window.
w | The width of the window in pixels.
h | The height of the window in pixels.
options | 0 by default; a bitmask of [app_options](https://github.com/RandyGaul/cute_framework/blob/master/docs/app/app_options.md) flags.
argv0 | The first argument passed to your main function in the `argv` parameter.

## Return Value

Returns any errors on failure as a [CF_Result](https://github.com/RandyGaul/cute_framework/blob/master/docs/utility/cf_result.md).

## Code Example

> Creating a basic 640x480 window for your game.

```cpp
#include <cute.h>
using namespace cute;

int main(int argc, const char argv)
{
    // Create a window with a resolution of 640 x 480, along with a DirectX 11 context.
    app_make("Fancy Window Title", 50, 50, 640, 480, CUTE_APP_OPTIONS_D3D11_CONTEXT, argv[0]);
    
    while (app_is_running())
    {
        app_update();
        // All your game logic and updates go here...
        app_draw_onto_screen();
    }
    
    app_destroy();
    
    return 0;
}
```

## Remarks

The options parameter is an enum from [app_options](https://github.com/RandyGaul/cute_framework/blob/master/docs/app/app_options.md). Different options can be OR'd together.
Parameters `w` and `h` are ignored if the window is initialized to fullscreen mode with `APP_OPTIONS_FULLSCREEN`.

## Related Pages

[cf_app_is_running](https://github.com/RandyGaul/cute_framework/blob/master/docs/app/cf_app_is_running.md)  
[cf_app_signal_shutdown](https://github.com/RandyGaul/cute_framework/blob/master/docs/app/cf_app_signal_shutdown.md)  
[cf_destroy_app](https://github.com/RandyGaul/cute_framework/blob/master/docs/app/cf_destroy_app.md)  
