#include "final.h"

gchar *on_department_combo_changed(GtkComboBox *combo_box) {
    gchar *department = nullptr;
    GtkTreeIter iter;

    if (gtk_combo_box_get_active_iter(combo_box, &iter)) {
        GtkTreeModel *model = gtk_combo_box_get_model(combo_box);
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


// g++ -c final_main.cpp final_callbacks.cpp final_globals.cpp `pkg-config --cflags gtk+-3.0`
// g++ -o final final_main.o final_callbacks.o final_globals.o `pkg-config --libs gtk+-3.0`
