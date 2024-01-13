#include <gtk/gtk.h>

GtkBuilder *builder;
GtkListStore *list_store;

// Function to get the selected department from the combo box
gchar *on_department_combo_changed(GtkComboBox *combo_box) {
    gchar *department = nullptr;
    GtkTreeIter iter;

    // Get the selected department from the combo box
    if (gtk_combo_box_get_active_iter(combo_box, &iter)) {
        GtkTreeModel *model = gtk_combo_box_get_model(combo_box);

        // Assuming the first column of the list store is of type G_TYPE_STRING
        gtk_tree_model_get(model, &iter, 0, &department, -1);
    }

    return department;
}

void on_submit_button_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget *entry = GTK_WIDGET(user_data);
    GtkWidget *department_combo = GTK_WIDGET(gtk_builder_get_object(builder, "combobox1"));
    GtkWidget *male_radio = GTK_WIDGET(gtk_builder_get_object(builder, "male"));
    GtkWidget *female_radio = GTK_WIDGET(gtk_builder_get_object(builder, "female"));
    GtkWidget *treeview = GTK_WIDGET(gtk_builder_get_object(builder, "treeview1"));

    // Get the selected department from the combo box
    gchar *department = on_department_combo_changed(GTK_COMBO_BOX(department_combo));

    // Get the text from the entry widget
    const gchar *text = gtk_entry_get_text(GTK_ENTRY(entry));

    // Get the selected gender from the radio buttons
    const gchar *gender = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(male_radio)) ? "Male" : "Female";

    // Add the data to the list store
    GtkTreeIter iter;
    gtk_list_store_append(list_store, &iter);
    gtk_list_store_set(list_store, &iter, 0, text, 1, department ? department : "Not selected", 2, gender, -1);

    // Print the information to the terminal
    g_print("Submitted:\n");
    g_print("Name: %s\n", text);
    g_print("Department: %s\n", department ? department : "Not selected");
    g_print("Gender: %s\n", gender);

    // Clear the entry widget
    gtk_entry_set_text(GTK_ENTRY(entry), "");

    // Clear the combo box selection
    gtk_combo_box_set_active(GTK_COMBO_BOX(department_combo), -1);

    // Clear the radio button selection
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(male_radio), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(female_radio), FALSE);

    // Free the memory allocated for the department string
    g_free(department);
}

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
