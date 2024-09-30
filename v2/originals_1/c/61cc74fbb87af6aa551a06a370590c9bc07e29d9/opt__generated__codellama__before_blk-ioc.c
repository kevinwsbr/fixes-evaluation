#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>

#define MAX_RESOURCES 100 /* maximum number of resources */

struct resource {
    void *data;
};

static struct resource *pool = NULL;

void init_resource_pool(void)
{
    pool = kzalloc(sizeof(*pool) * MAX_RESOURCES, GFP_KERNEL);
}

struct resource *get_resource(void)
{
    int i;

    for (i = 0; i < MAX_RESOURCES; i++) {
        if (!pool[i].data) {
            pool[i].data = kzalloc(sizeof(void *), GFP_KERNEL);
            return &pool[i];
        }
    }

    return NULL;
}

void free_resource(struct resource *res)
{
    kfree(res->data);
    res->data = NULL;
}
