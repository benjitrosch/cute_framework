# CF_PixelFormat | [graphics](https://github.com/RandyGaul/cute_framework/blob/master/docs/graphics/README.md) | [cute_graphics.h](https://github.com/RandyGaul/cute_framework/blob/master/include/cute_graphics.h)

The various supported pixel formats.

## Values

Enum | Description
--- | ---
PIXELFORMAT_DEFAULT | The default pixel format.
PIXELFORMAT_R8 | 8-bit red-only channel.
PIXELFORMAT_R8SN | 8-bit red-only channel, in signed normalized form.
PIXELFORMAT_R8UI | 8-bit red-only channel, in unsigned integer form.
PIXELFORMAT_R8SI | 8-bit red-only channel, in signed integer form.
PIXELFORMAT_R16 | 16-bit red-only channel.
PIXELFORMAT_R16SN | 16-bit red-only channel, in signed normalized form.
PIXELFORMAT_R16UI | 16-bit red-only channel, in unsigned integer form.
PIXELFORMAT_R16SI | 16-bit red-only channel, in signed integer form.
PIXELFORMAT_R16F | 16-bit red-only channel, in floating point form.
PIXELFORMAT_RG8 | 8-bit red/green channels, 16 bits total.
PIXELFORMAT_RG8SN | 8-bit red/green channels, in signed normalized form, 16 bits total.
PIXELFORMAT_RG8UI | 8-bit red/green channels, in unsigned integer form, 16 bits total.
PIXELFORMAT_RG8SI | 8-bit red/green channels, in signed integer form, 16 bits total.
PIXELFORMAT_R32UI | 32-bit red-only channel, in unsigned integer form.
PIXELFORMAT_R32SI | 32-bit red-only channel, in signed integer form.
PIXELFORMAT_R32F | 32-bit red-only channel, in floating point form.
PIXELFORMAT_RG16 | 16-bit red-green channels, 32 bits total.
PIXELFORMAT_RG16SN | 16-bit red-green channels, in signed normalized form, 32 bits total.
PIXELFORMAT_RG16UI | 16-bit red-green channels, in unsigned integer form, 32 bits total.
PIXELFORMAT_RG16SI | 16-bit red-green channels, in signed integer form, 32 bits total.
PIXELFORMAT_RG16F | 16-bit red-green channels, in floating point form, 32 bits total.
PIXELFORMAT_RGBA8 | 8-bit red-green-blue-alpha channels, 32 bits total.
PIXELFORMAT_RGBA8SN | 8-bit red-green-blue-alpha channels, in signed normalized form, 32 bits total.
PIXELFORMAT_RGBA8UI | 8-bit red-green-blue-alpha channels, in unsigned integer form, 32 bits total.
PIXELFORMAT_RGBA8SI | 8-bit red-green-blue-alpha channels, in signed integer form, 32 bits total.
PIXELFORMAT_BGRA8 | 8-bit blue-green-red-alpha channels, 32 bits total.
PIXELFORMAT_RGB10A2 | 10-bit red-green-blue channels, 2-bit alpha channel, 32 bits total.
PIXELFORMAT_RG11B10F | 11-bit red-green channels, 10-bit blue channel, in floating point form, 32 bits total.
PIXELFORMAT_RG32UI | 32-bit red-green channels, in unsigned integer form, 64 bits total.
PIXELFORMAT_RG32SI | 32-bit red-green channels, in signed integer form, 64 bits total.
PIXELFORMAT_RG32F | 32-bit red-green channels, in floating point form, 64 bits total.
PIXELFORMAT_RGBA16 | 16-bit red-green-blue-alpha channels, 64 bits total.
PIXELFORMAT_RGBA16SN | 16-bit red-green-blue-alpha channels, in signed normalized form, 64 bits total.
PIXELFORMAT_RGBA16UI | 16-bit red-green-blue-alpha channels, in unsigned integer form, 64 bits total.
PIXELFORMAT_RGBA16SI | 16-bit red-green-blue-alpha channels, in signed integer form, 64 bits total.
PIXELFORMAT_RGBA16F | 16-bit red-green-blue-alpha channels, in floating point form, 64 bits total.
PIXELFORMAT_RGBA32UI | 32-bit red-green-blue-alpha channels, in unsigned integer form, 128 bits total.
PIXELFORMAT_RGBA32SI | 32-bit red-green-blue-alpha channels, in signed integer form, 128 bits total.
PIXELFORMAT_RGBA32F | 32-bit red-green-blue-alpha channels, in floating point form, 128 bits total.
PIXELFORMAT_DEPTH | 32-bit red-green-blue-alpha channels, in floating point form, 128 bits total.
PIXELFORMAT_DEPTH_STENCIL | 24-bit depth channel, 8-bit stencil channel.
PIXELFORMAT_BC1_RGBA | Block Compression 1.
PIXELFORMAT_BC2_RGBA | Block Compression 2.
PIXELFORMAT_BC3_RGBA | Block Compression 3.
PIXELFORMAT_BC4_R | Block Compression 4.
PIXELFORMAT_BC4_RSN | Block Compression 4 (signed normalized).
PIXELFORMAT_BC5_RG | Block Compression 5.
PIXELFORMAT_BC5_RGSN | Block Compression 5 (signed normalized).
PIXELFORMAT_BC6H_RGBF | Block Compression 6.
PIXELFORMAT_BC6H_RGBUF | Block Compression 6 (unsigned).
PIXELFORMAT_BC7_RGBA | Block Compression 7.
PIXELFORMAT_PVRTC_RGB_2BPP | PVRTC compression 7.
PIXELFORMAT_PVRTC_RGB_4BPP | PVRTC red-green-blue 2-bits-per-pixel.
PIXELFORMAT_PVRTC_RGBA_2BPP | PVRTC red-green-blue 4-bits-per-pixel.
PIXELFORMAT_PVRTC_RGBA_4BPP | PVRTC red-green-blue-alpha 2-bits-per-pixel.
PIXELFORMAT_ETC2_RGB8 | PVRTC red-green-blue-alpha 4-bits-per-pixel.
PIXELFORMAT_ETC2_RGB8A1 | ETC2 red-green-blue 8-bit channels.
PIXELFORMAT_ETC2_RGBA8 | ETC2 red-green-blue 8-bit channels, 1-bit alpha channel.
PIXELFORMAT_ETC2_RG11 | ETC2 red-green-blue-alpha 8-bit channels.
PIXELFORMAT_ETC2_RG11SN | ETC2 red-green 11-bit channels.
PIXELFORMAT_COUNT | ETC2 red-green 11-bit channels, in signed-normalized form.

## Remarks

Not all types are supported on each backend. Be sure to check with [cf_query_pixel_format](https://github.com/RandyGaul/cute_framework/blob/master/docs/graphics/cf_query_pixel_format.md) if a particular pixel format
is available for your use-case. If unsure, just use `CF_PIXELFORMAT_DEFAULT` for red-green-blue-alpha, 8 bits per component (32 bits total),
which get mapped to 4 floats on the GPU from [0,1].

This table helps understand how to read the pixel format notation.

Notation | Description
--- | ---
RGBA | R stands for red, G stands for green, B stands for blue, A stands for alpha.
XX | A number, describes the number of bits used by the pixel format. For example `CF_PIXELFORMAT_R8` uses 8 bits, while `PIXELFORMAT_RG16F` uses 16 bits.
N | A normalized number from [0,1]. All the bits of the format will be treated as an integer. For example, `CF_PIXELFORMAT_R8` starts as an 8-bit value on the CPU, but is mapped from [0,255] to [0,1] as a float on the GPU.
UI | The GPU will interpret the bits of a pixel as an unsigned integer.
SI | The GPU will interpret the bits of a pixel as a signed integer.
F | The GPU will interpret the bits of a pixel as a floating point value.
N | Stands for "normalized". The pixel's bits are mapped from [0,2^##] to floating point [0,1] on the GPU.
SN | Signed-normalized. The same as N, but mapped to floating point [-1,1] on the GPU.

The other formats such as BC (Block Compression for DirectX), PVRTC (for iOS), and ETC2 (OpenGL ES and ARM devices) are common compression formats.
These can potentially save a lot of memory on the GPU, but are only good for certain games (mainly 3D games), and are only available on certain backends.

## Related Pages

[cf_query_pixel_format](https://github.com/RandyGaul/cute_framework/blob/master/docs/graphics/cf_query_pixel_format.md)  
[cf_pixel_format_to_string](https://github.com/RandyGaul/cute_framework/blob/master/docs/graphics/cf_pixel_format_to_string.md)  
[CF_PixelFormatOp](https://github.com/RandyGaul/cute_framework/blob/master/docs/graphics/cf_pixelformatop.md)  
