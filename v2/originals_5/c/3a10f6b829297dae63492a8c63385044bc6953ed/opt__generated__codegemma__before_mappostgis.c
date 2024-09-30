// Enable paging for a PostGIS layer
msPostGISEnablePaging(layerObj, 1);

// Get the paging status
int pagingStatus = msPostGISGetPaging(layerObj);
