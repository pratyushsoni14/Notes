#ifndef FINAL_H
#define FINAL_H

#include <gtk/gtk.h>

extern GtkBuilder *builder;
extern GtkListStore *list_store;

gchar *on_department_combo_changed(GtkComboBox *combo_box);
void on_submit_button_clicked(GtkWidget *button, gpointer user_data);

#endif /* FINAL_H */
