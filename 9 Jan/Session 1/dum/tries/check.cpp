#include <gtk/gtk.h>

enum {
    COLUMN_NAME,
    COLUMN_POSITION,
    COLUMN_DEPARTMENT,
    COLUMN_PHONE,
    NUM_COLUMNS
};

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkBuilder *builder;
    GtkListStore *store;
    GtkWidget *tree_view;
    GtkTreeViewColumn *column;
    GtkCellRenderer *renderer;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "/home/pratyushs/Desktop/Sessions/9 Jan/Session 1/Assignment/Unsaved 1.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Get the GtkTreeView and create a GtkListStore
    tree_view = GTK_WIDGET(gtk_builder_get_object(builder, "treeview1"));
    store = gtk_list_store_new(NUM_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

    // Add a record to the GtkListStore
    GtkTreeIter iter;
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter,
                       COLUMN_NAME, "Pratyush",
                       COLUMN_POSITION, "Intern",
                       COLUMN_DEPARTMENT, "IT department",
                       COLUMN_PHONE, "9041673733",
                       -1);

    // Create columns for the tree view
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Name", renderer, "text", COLUMN_NAME, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Position", renderer, "text", COLUMN_POSITION, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Department", renderer, "text", COLUMN_DEPARTMENT, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);

    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Phone", renderer, "text", COLUMN_PHONE, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), column);

    gtk_tree_view_set_model(GTK_TREE_VIEW(tree_view), GTK_TREE_MODEL(store));
    g_object_unref(store); // Unreference the store when done

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
