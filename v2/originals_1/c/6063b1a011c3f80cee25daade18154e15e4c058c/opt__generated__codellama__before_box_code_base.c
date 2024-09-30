This is the implementation of a `GF_DOVIConfigurationBox` structure, which is used to store information about the DOLBY Vision configuration in an ISO Base Media File. The structure contains several fields that define the version number, profile, and level of the Dolby Vision configuration, as well as flags indicating whether RPU, EL, or BL are present.

Here is a breakdown of the structure and its fields:

* `type`: This field specifies the type of box. In this case, it is set to `GF_ISOM_BOX_TYPE_DVCC`.
* `size`: This field stores the size of the box in bytes.
* `ES_ID`: This field stores the ID of the elementary stream that contains the Dolby Vision configuration information.
* `decoder_config_record`: This field stores an instance of a `GF_DOVIDecoderConfigurationRecord` structure, which defines the version number, profile, and level of the Dolby Vision configuration. The record also has flags indicating whether RPU, EL, or BL are present.
* `dv_version_major`: This field stores the major version number of the Dolby Vision configuration.
* `dv_version_minor`: This field stores the minor version number of the Dolby Vision configuration.
* `dv_profile`: This field stores the profile of the Dolby Vision configuration.
* `dv_level`: This field stores the level of the Dolby Vision configuration.
* `rpu_present_flag`: This field indicates whether an RPU is present in the stream.
* `el_present_flag`: This field indicates whether an EL is present in the stream.
* `bl_present_flag`: This field indicates whether a BL is present in the stream.

The functions `dvcC_new`, `dvcC_del`, and `dvcC_Read` are used to create, delete, and read an instance of this structure. The function `dvcC_Write` is used to write an instance of this structure to a bitstream. Finally, the function `dvcC_Size` calculates the size of an instance of this structure in bytes.