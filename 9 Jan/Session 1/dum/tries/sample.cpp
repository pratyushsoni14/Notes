#include <gtk/gtk.h>

enum {
    COLUMN_NAME,
    COLUMN_DEPARTMENT,
    COLUMN_GENDER,
    NUM_COLUMNS
};

GtkListStore *store;

void on_submit_clicked(GtkButton *button, gpointer user_data) {
    GtkBuilder *builder = GTK_BUILDER(user_data);

    GtkWidget *entry_name = GTK_WIDGET(gtk_builder_get_object(builder, "entry1"));
    GtkWidget *combobox_department = GTK_WIDGET(gtk_builder_get_object(builder, "combobox1"));
    GtkWidget *radiobutton_male = GTK_WIDGET(gtk_builder_get_object(builder, "radiobutton1"));
    GtkWidget *radiobutton_female = GTK_WIDGET(gtk_builder_get_object(builder, "radiobutton2"));
    GtkTreeView *treeview = GTK_TREE_VIEW(gtk_builder_get_object(builder, "treeview1"));

    const gchar *name = gtk_entry_get_text(GTK_ENTRY(entry_name));
    const gchar *department = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combobox_department));
    const gchar *gender = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton_male)) ? "Male" : "Female";

    GtkTreeIter iter;
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter,
        COLUMN_NAME, name,
        COLUMN_DEPARTMENT, department,
        COLUMN_GENDER, gender,
        -1);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "/home/pratyushs/Desktop/Sessions/9 Jan/Session 1/Assignment/Unsaved 1.glade", NULL);

    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
    if (!window) {
        g_error("Failed to retrieve the window from the UI file.");
        return 1;  // Exit with an error status
    }

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    store = gtk_list_store_new(NUM_COLUMNS,
        G_TYPE_STRING,   // Name column
        G_TYPE_STRING,   // Department column
        G_TYPE_STRING    // Gender column
    );

    GtkWidget *submit = GTK_WIDGET(gtk_builder_get_object(builder, "submit"));
    g_signal_connect(submit, "clicked", G_CALLBACK(on_submit_clicked), builder);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
