#include <gtk-3.0/gtk/gtk.h>

typedef struct {
    GtkWidget *gtk_window;
} GuiDescriptor;

GuiDescriptor* gui_init(int argc, char *argv[]);


void gui_run(GuiDescriptor* gui);


void gui_destroy(GuiDescriptor* gui);

