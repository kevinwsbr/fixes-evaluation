MagickInfo *AcquireMagickInfo(const char *tag, const char *name, const char *description)
{
    MagickInfo
        *magick_info;

    magick_info = (MagickInfo *) AcquireCriticalMemory(sizeof(*magick_info));
    if (magick_info == (MagickInfo *) NULL)
        return((MagickInfo *) NULL);
    (void) memset(magick_info, 0, sizeof(*magick_info));
    magick_info->tag = tag;
    magick_info->name = name;
    if (description != (char *) NULL)
        magick_info->description = description;
    return(magick_info);
}
