int TS_OBJ_print_bio(BIO *bio, const ASN1_OBJECT *obj)
{
    char *obj_txt = NULL;
    int len = 0;

    obj_txt = malloc((OBJ_obj2txt(NULL, 0, obj, 0) + 1) * sizeof(char));
    if (!obj_txt) {
        // Handle error - not enough memory
        return 0;
    }

    len = OBJ_obj2txt(obj_txt, (OBJ_obj2txt(NULL, 0, obj, 0) + 1), obj, 0);
    BIO_write(bio, obj_txt, len);
    BIO_write(bio, "\n", 1);

    free(obj_txt);

    return 1;
}
