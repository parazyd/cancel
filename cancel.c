/* 
 * gcc -o cancel $(pkg-config --cflags --libs gtk+-3.0) cancel.c
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gtk/gtk.h>

static void cancel(GtkButton *btn, gpointer data)
{
	GtkWidget *dialog, *karen, *content_area, *label;

	dialog = gtk_dialog_new_with_buttons("Cancelled", NULL,
		GTK_DIALOG_MODAL, "OK", GTK_RESPONSE_ACCEPT,  NULL);

	content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
	label = gtk_label_new("\nSuccessfully cancelled!\n");
	gtk_container_add(GTK_CONTAINER(content_area), label);

	karen = gtk_image_new_from_file("karen.png");
	gtk_container_add(GTK_CONTAINER(content_area), karen);

	gtk_widget_show_all(dialog);

	g_signal_connect_swapped(dialog, "response",
		G_CALLBACK (g_application_quit), data);
}

static void activate(GtkApplication *app, gpointer data)
{
	GtkWidget *window, *box, *label, *entry, *button;
	GtkWidget *lynch_mob;

	window = gtk_application_window_new(app);
	gtk_window_set_default_size(GTK_WINDOW(window), 320, 240);
	gtk_window_set_gravity(GTK_WINDOW(window), GDK_GRAVITY_CENTER);

	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
	gtk_widget_set_valign(box, GTK_ALIGN_CENTER);

	label = gtk_label_new("Who should we cancel today?");
	gtk_container_add(GTK_CONTAINER(box), label);

	entry = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(entry), "FSF");
	gtk_container_add(GTK_CONTAINER(box), entry);

	lynch_mob = gtk_check_button_new_with_label(
		"There is a lynch mob outside my house");
	gtk_container_add(GTK_CONTAINER(box), lynch_mob);

	button = gtk_button_new_with_label("CANCEL");
	gtk_container_add(GTK_CONTAINER(box), button);
	g_signal_connect(button, "clicked", G_CALLBACK(cancel), app);

	gtk_window_set_title(GTK_WINDOW(window), "Cancel");
	gtk_container_add(GTK_CONTAINER(window), box);

	gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
	GtkApplication *app;
	int status;

	app = gtk_application_new(NULL, G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);

	return status;
}
