# CF_RenderState | [graphics](https://github.com/RandyGaul/cute_framework/blob/master/docs/graphics/README.md) | [cute_graphics.h](https://github.com/RandyGaul/cute_framework/blob/master/include/cute_graphics.h)

A bag of rendering related settings.

Struct Members | Description
--- | ---
`CF_CullMode cull_mode` | Controls whether or not to cull triangles based on their winding order. See [CF_CullMode](https://github.com/RandyGaul/cute_framework/blob/master/docs/graphics/cf_cullmode.md).
`CF_BlendState blend` | Controls how the GPU blends pixels together during compositing. See [CF_BlendState](https://github.com/RandyGaul/cute_framework/blob/master/docs/graphics/cf_blendstate.md).
`CF_CompareFunction depth_compare` | Defines how to perform depth-testing. See [CF_CompareFunction](https://github.com/RandyGaul/cute_framework/blob/master/docs/graphics/cf_comparefunction.md).
`bool depth_write_enabled` | Must be true to enable depth-testing and use of the depth buffer.
`CF_StencilParams stencil` | Sets up how to perform (if at all) stencil testing. See [CF_StencilParams](https://github.com/RandyGaul/cute_framework/blob/master/docs/graphics/cf_stencilparams.md).

## Remarks

The [CF_RenderState](https://github.com/RandyGaul/cute_framework/blob/master/docs/graphics/cf_renderstate.md) is a big collection of various rendering settings, such as culling mode,
blending operations, depth and stencil settings, etc. Altering these on a material always means
increasing your draw call count. It's best to try and set these once and leave them alone, though
this is not always possible.

## Related Pages

[CF_BlendState](https://github.com/RandyGaul/cute_framework/blob/master/docs/graphics/cf_blendstate.md)  
[CF_CullMode](https://github.com/RandyGaul/cute_framework/blob/master/docs/graphics/cf_cullmode.md)  
[CF_StencilParams](https://github.com/RandyGaul/cute_framework/blob/master/docs/graphics/cf_stencilparams.md)  
[cf_material_set_render_state](https://github.com/RandyGaul/cute_framework/blob/master/docs/graphics/cf_material_set_render_state.md)  
