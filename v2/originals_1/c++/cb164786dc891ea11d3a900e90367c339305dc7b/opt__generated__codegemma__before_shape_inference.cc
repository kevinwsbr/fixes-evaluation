bool InferenceContext::MergeHandleShapesAndTypes(
    const std::vector<ShapeAndType>& shapes_and_types1,
    std::vector<ShapeAndType>* to_update) {
  if (shapes_and_types1.size() != to_update->size()) {
    return false;
  }
  std::vector<ShapeAndType> new_values(shapes_and_types1.size());
  for (int i = 0, end = shapes_and_types1.size(); i < end; ++i) {
    const ShapeAndType& s1 = shapes_and_types1[i];
    const ShapeAndType& s2 = (*to_update)[i];
    if (s1.dtype != s2.dtype) {
      if (s2.dtype != DT_INVALID) {
        return false;
      } else {
        new_values[i].dtype = s1.dtype;
      }
    } else {
      new_values[i].dtype = s2.dtype;
    }
    Relax(s2.shape, s1.shape, &new_values[i].shape);
  }
  to_update->swap(new_values);
  return true;
}
