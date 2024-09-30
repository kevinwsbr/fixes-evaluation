// Read the profiles from files
StringInfo *exifProfile = ReadProfile("exif.profile");
StringInfo *bimProfile = ReadProfile("bim.profile");

// Synchronize the profiles
MagickBooleanType success = SyncImageProfiles(image, exifProfile, bimProfile);

// Check for errors
if (success == MagickFalse) {
  // Handle errors
}
