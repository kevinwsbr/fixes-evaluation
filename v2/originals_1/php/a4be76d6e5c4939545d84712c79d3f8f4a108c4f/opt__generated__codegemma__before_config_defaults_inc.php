**Global Variables for Mantis Web Services Access Levels**

The code snippet defines global variables used to control access levels for Mantis web services. These variables are set to specific integer values corresponding to different access levels within MantisBT.

**Variable Name | Description | Value**
---|---|---
g_webservice_readonly_access_level_threshold | Minimum access level for read-only access | VIEWER
g_webservice_readwrite_access_level_threshold | Minimum access level for read/write access | REPORTER
g_webservice_admin_access_level_threshold | Minimum access level for administrator access | MANAGER
g_webservice_specify_reporter_on_add_access_level_threshold | Minimum access level to specify reporter name when adding an issue | DEVELOPER
g_webservice_priority_enum_default_when_not_found | Default enum ID when priority labels are not found | 0
g_webservice_severity_enum_default_when_not_found | Default enum ID when severity labels are not found | 0
g_webservice_status_enum_default_when_not_found | Default enum ID when status labels are not found | 0
g_webservice_resolution_enum_default_when_not_found | Default enum ID when resolution labels are not found | 0
g_webservice_projection_enum_default_when_not_found | Default enum ID when projection labels are not found | 0
g_webservice_eta_enum_default_when_not_found | Default enum ID when ETA labels are not found | 0
g_webservice_error_when_version_not_found | Flag to raise error when version is not found | ON
g_webservice_version_when_not_found | Default version when version is not found | ''

**Purpose:**

These variables are used by the Mantis web services to determine the access level of the user making the request. Based on the access level, the services can grant or deny access to specific operations.

**Additional Notes:**

* The access levels are defined in the MantisBT documentation.
* The default values for the enum ID variables can be customized based on the specific MantisBT installation.
* The g_webservice_error_when_version_not_found and g_webservice_version_when_not_found variables are used to handle cases where the requested version is not available.