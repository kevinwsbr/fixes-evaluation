InferenceContext::ShapeManager shape_manager;
std::vector<DimensionHandle> dim1 = {shape_manager.MakeDim(3), shape_manager.MakeDim(4)};
ShapeHandle shape1 = shape_manager.MakeShape(dim1);

std::vector<ShapeAndType> initial_shapes_and_types = {{DT_FLOAT, dim1}};
InferenceContext context;
context.MergeOutputHandleShapesAndTypes(0, initial_shapes_and_types);
