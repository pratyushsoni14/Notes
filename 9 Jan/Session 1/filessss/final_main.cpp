#include "final.h"

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "output.glade", nullptr);

    list_store = GTK_LIST_STORE(gtk_builder_get_object(builder, "liststore1"));

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
    GtkWidget *entry = GTK_WIDGET(gtk_builder_get_object(builder, "entry1"));
    GtkWidget *submit_button = GTK_WIDGET(gtk_builder_get_object(builder, "button1"));
    GtkWidget *department_combo = GTK_WIDGET(gtk_builder_get_object(builder, "combobox1"));

    // Connect the button click event to the callback function
    g_signal_connect(submit_button, "clicked", G_CALLBACK(on_submit_button_clicked), entry);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
