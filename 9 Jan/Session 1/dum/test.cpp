#include <iostream>
#include <gtk/gtk.h>

// Make them global
GtkWidget *window;
GtkWidget *fixed1;
GtkWidget *button1;
GtkWidget *label1;
GtkBuilder *builder;

int main(int argc, char *argv[]) {

    gtk_init(&argc, &argv); // init Gtk

    //---------------------------------------------------------------------
    // establish contact with xml code used to adjust widget settings
    //---------------------------------------------------------------------

    builder = gtk_builder_new_from_file("Unsaved 2.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_builder_connect_signals(builder, NULL);

    fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
    button1 = GTK_WIDGET(gtk_builder_get_object(builder, "button1"));
    label1 = GTK_WIDGET(gtk_builder_get_object(builder, "label1"));

    gtk_widget_show(window);

    gtk_main();

    return EXIT_SUCCESS;
}

extern "C" void on_button1_clicked(GtkButton *b) {
    gtk_label_set_text(GTK_LABEL(label1), "Hello World");
}
