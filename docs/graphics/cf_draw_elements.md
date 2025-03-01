# cf_draw_elements | [graphics](https://github.com/RandyGaul/cute_framework/blob/master/docs/graphics/README.md) | [cute_graphics.h](https://github.com/RandyGaul/cute_framework/blob/master/include/cute_graphics.h)

Draws all elements within the last applied mesh.

```cpp
void cf_draw_elements();
```

## Remarks

If the mesh is a static mesh with usage `CF_USAGE_TYPE_IMMUTABLE` the number of elements drawn will always be consistent with the mesh's
initial data. For `USAGE_TYPE_DYNAMIC` and `CF_USAGE_TYPE_STREAM` the number of elements will always match the previous call to
`cf_mesh_update_` or `cf_mesh_append_`.

## Related Pages

[CF_Mesh](https://github.com/RandyGaul/cute_framework/blob/master/docs/graphics/cf_mesh.md)  
cf_create_mesh  
[cf_apply_shader](https://github.com/RandyGaul/cute_framework/blob/master/docs/graphics/cf_apply_shader.md)  
[cf_apply_canvas](https://github.com/RandyGaul/cute_framework/blob/master/docs/graphics/cf_apply_canvas.md)  
