# cf_mesh_update_index_data | [graphics](https://github.com/RandyGaul/cute_framework/blob/master/docs/graphics/README.md) | [cute_graphics.h](https://github.com/RandyGaul/cute_framework/blob/master/include/cute_graphics.h)

Overwrites the index data of a mesh.

```cpp
void cf_mesh_update_index_data(CF_Mesh mesh, uint32_t* indices, int count);
```

Parameters | Description
--- | ---
mesh | The mesh.
indices | A pointer to index data.
count | Number of bytes in `data`.

## Remarks

The mesh must have been created with `CF_USAGE_TYPE_DYNAMIC` or `CF_USAGE_TYPE_STREAM` in order to call this function more
than once. For `CF_USAGE_TYPE_IMMUTABLE` this function can only be called once. For dynamic/stream cases you can only call
this function once per frame.

## Related Pages

[CF_Mesh](https://github.com/RandyGaul/cute_framework/blob/master/docs/graphics/cf_mesh.md)  
[cf_make_mesh](https://github.com/RandyGaul/cute_framework/blob/master/docs/graphics/cf_make_mesh.md)  
[cf_destroy_mesh](https://github.com/RandyGaul/cute_framework/blob/master/docs/graphics/cf_destroy_mesh.md)  
[cf_mesh_set_attributes](https://github.com/RandyGaul/cute_framework/blob/master/docs/graphics/cf_mesh_set_attributes.md)  
[cf_mesh_update_vertex_data](https://github.com/RandyGaul/cute_framework/blob/master/docs/graphics/cf_mesh_update_vertex_data.md)  
[cf_mesh_update_instance_data](https://github.com/RandyGaul/cute_framework/blob/master/docs/graphics/cf_mesh_update_instance_data.md)  
