# cf_draw_polyline | [draw](https://github.com/RandyGaul/cute_framework/blob/master/docs/draw/README.md) | [cute_draw.h](https://github.com/RandyGaul/cute_framework/blob/master/include/cute_draw.h)

Draws a chain of connected line segments.

```cpp
void cf_draw_polyline(CF_V2* points, int count, float thickness, bool loop, int bevel_count);
```

Parameters | Description
--- | ---
points | An array of line segment endpoints.
count | The number of points in the polyline.
thickness | The thickness of the line to draw.
loop | True to connect the first and last point to form a loop. False otherwise.
bevel_count | The number of edges used to smooth corners.

## Related Pages

[cf_draw_line](https://github.com/RandyGaul/cute_framework/blob/master/docs/draw/cf_draw_line.md)  
[cf_draw_line2](https://github.com/RandyGaul/cute_framework/blob/master/docs/draw/cf_draw_line2.md)  
[cf_app_draw_onto_screen](https://github.com/RandyGaul/cute_framework/blob/master/docs/app/cf_app_draw_onto_screen.md)  
[cf_draw_bezier_line](https://github.com/RandyGaul/cute_framework/blob/master/docs/draw/cf_draw_bezier_line.md)  
[cf_draw_bezier_line2](https://github.com/RandyGaul/cute_framework/blob/master/docs/draw/cf_draw_bezier_line2.md)  
cf_draw_to  
