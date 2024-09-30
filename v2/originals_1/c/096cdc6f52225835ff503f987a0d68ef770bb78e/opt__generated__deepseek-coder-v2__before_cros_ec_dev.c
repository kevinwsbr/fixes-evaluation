  class_register(&cros_class); // Register character device class
  alloc_chrdev_region(&dev, 0, CROS_MAX_DEV, CROS_EC_DEV_NAME); // Allocate major numbers for devices
  platform_driver_register(&cros_ec_dev_driver); // Register the platform driver
  