  ccp_reverse_get_dm_area(&dst, 0, ecc->u.pm.result.x, 0, CCP_ECC_MODULUS_BYTES);
  dst.address += CCP_ECC_OUTPUT_SIZE;
  ccp_reverse_get_dm_area(&dst, 0, ecc->u.pm.result.y, 0, CCP_ECC_MODULUS_BYTES);
  dst.address += CCP_ECC_OUTPUT_SIZE;
  