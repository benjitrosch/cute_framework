# cf_make_mesh | [graphics](https://github.com/RandyGaul/cute_framework/blob/master/docs/graphics/README.md) | [cute_graphics.h](https://github.com/RandyGaul/cute_framework/blob/master/include/cute_graphics.h)

Returns a [CF_Mesh](https://github.com/RandyGaul/cute_framework/blob/master/docs/graphics/cf_mesh.md).

```cpp
CF_Mesh cf_make_mesh(CF_UsageType usage_type, int vertex_buffer_size, int index_buffer_size, int instance_buffer_size);
```

Parameters | Description
--- | ---
usage_type | Distinguish between per-vertex or per-attribute stepping. See [CF_UsageType](https://github.com/RandyGaul/cute_framework/blob/master/docs/graphics/cf_usagetype.md).
vertex_buffer_size | The size of the mesh's vertex buffer.
index_buffer_size | The size of the mesh's index buffer. Set to 0 if you're not using indices.
instance_buffer_size | The size of the mesh's instance buffer. Set to 0 if you're not using instancing.

## Related Pages

[CF_Mesh](https://github.com/RandyGaul/cute_framework/blob/master/docs/graphics/cf_mesh.md)  
[cf_mesh_update_index_data](https://github.com/RandyGaul/cute_framework/blob/master/docs/graphics/cf_mesh_update_index_data.md)  
[cf_destroy_mesh](https://github.com/RandyGaul/cute_framework/blob/master/docs/graphics/cf_destroy_mesh.md)  
[cf_mesh_set_attributes](https://github.com/RandyGaul/cute_framework/blob/master/docs/graphics/cf_mesh_set_attributes.md)  
[cf_mesh_update_vertex_data](https://github.com/RandyGaul/cute_framework/blob/master/docs/graphics/cf_mesh_update_vertex_data.md)  
[cf_mesh_update_instance_data](https://github.com/RandyGaul/cute_framework/blob/master/docs/graphics/cf_mesh_update_instance_data.md)  
