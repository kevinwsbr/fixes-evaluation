// Create a new metadata record for the target class
const metadataRecord = resolveMetadataRecord(target, context, false);

// Add a new meta entry to the record
metadataRecord.push(resolveEntry(targetContext, context, 'author', 'John Doe'));

// Run initialization callbacks for the target
runIniCallbacks(targetContext, initializationCallbacks);
