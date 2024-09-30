#include <stdint.h>
#include <string.h>
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/internal/reference/reference_ops.h"
#include "tensorflow/lite/kernels/internal/tensor.h"
#include "tensorflow/lite/kernels/internal/tensor_ctypes.h"
#include "tensorflow/lite/kernels/kernel_util.h"

namespace tflite {
namespace ops {
namespace builtin {
namespace expand_dims {

TfLiteStatus ExpandTensorDim(TfLiteContext* context, const TfLiteTensor& input, int axis, TfLiteTensor* output) {
  const TfLiteIntArray& input_dims = *input.dims;
  // Adjust negative axis value
  if (axis < 0) {
    axis += input_dims.size + 1;
  }
  // Check if axis is within valid range
  TF_LITE_ENSURE(context, axis >= 0 && axis <= input_dims.size);

  TfLiteIntArray* output_dims = TfLiteIntArrayCreate(input_dims.size + 1);
  for (int i = 0; i < output_dims->size; ++i) {
    if (i < axis) {
      output_dims->data[i] = input_dims.data[i];
    } else if (i == axis) {
      output_dims->data[i] = 1;
    } else {
      output_dims->data[i] = input_dims.data[i - 1];
    }
  }
  // Rest of the function...
}
// Rest of the code...
