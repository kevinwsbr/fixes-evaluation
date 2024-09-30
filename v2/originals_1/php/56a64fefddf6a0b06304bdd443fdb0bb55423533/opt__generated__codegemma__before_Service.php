// Assuming $cartProduct is a Model_CartProduct object
$productDiscountCalculator = new ProductDiscountCalculator();
$discountData = $productDiscountCalculator->cartProductToApiArray($cartProduct);

// Display the discount data
echo json_encode($discountData);
