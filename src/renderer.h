
typedef struct {
    int i;
} RendererDescriptor;

RendererDescriptor* renderer_init();

void renderer_run(RendererDescriptor* gui);

void renderer_destroy(RendererDescriptor* gui);

