```
[PYTHON]
import tensorflow as tf

def split(input_tensor, num_or_size_splits=None, axis=0, num=None):
    """Split a tensor into sub tensors.

    Args:
        input_tensor: A tensor to split.
        num_or_size_splits: Either indicate how many splits or provide a sizes of splits for each dimension.
            If using the argument, `axis` should also be specified.
        axis: The dimension along which to split. Default is 0.
        num: Deprecated in favor of num_or_size_splits.
    Returns:
        A list of sub tensors.
    Raises:
        ValueError: If the given tensor can not be split using the arguments.
    """

    if axis < 0:
        axis += len(input_tensor.shape)

    if num is not None:
        deprecation_warning("num", "num_or_size_splits")
        if num_or_size_splits is not None:
            raise ValueError("num and num_or_size_splits are mutually exclusive.")
        num_or_size_splits = num

    if num_or_size_splits is not None and isinstance(num_or_size_splits, int):
        # Split into equal sized splits.
        return tf.split(input_tensor, num_or_size_splits, axis)
    elif num_or_size_splits is not None and isinstance(num_or_size_splits, (list, tuple)):
        # Split into specified sizes for each dimension.
        return tf.split(input_tensor, num_or_size_splits, axis)
    else:
        raise ValueError("num_or_size_splits must be an int or a list of ints.")
[/PYTHON]
