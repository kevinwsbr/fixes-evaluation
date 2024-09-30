// Create a polygon primitive with 5 points
PrimitiveInfo polygon_primitive;
polygon_primitive.points = { ... };

// Trace the polygon with closed path
PrimitiveInfo stroke_polygon = TracePolygon(polygon_primitive, true);

// Render the line segments of the polygon
// ...
