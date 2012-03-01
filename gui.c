#include "gui.h"
#include <stdlib.h>

static void destroy(GtkWidget *widget, gpointer data);

GuiDescriptor* gui_init(int argc, char *argv[]) {
    GuiDescriptor* gui;
    
    g_type_init();
    gtk_init(&argc, &argv);
    gui = malloc(sizeof(GuiDescriptor));
    gui->gtk_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    g_signal_connect (gui->gtk_window, "destroy", G_CALLBACK (destroy), NULL);
    
    return gui;
}

void gui_run(GuiDescriptor* gui) {
    gtk_widget_show (gui->gtk_window);
    gtk_main ();
}


void gui_destroy(GuiDescriptor* gui) {
    free(gui);
}


static void destroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}
