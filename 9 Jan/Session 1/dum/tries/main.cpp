#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkBuilder *builder;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "/home/pratyushs/Desktop/Sessions/9 Jan/Session 1/Assignment/Unsaved 1.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
