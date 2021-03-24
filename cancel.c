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
	GtkWidget *dialog;

	dialog = gtk_message_dialog_new(NULL, 0, GTK_MESSAGE_INFO,
		GTK_BUTTONS_OK, "Successfully cancelled!");

	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);

	g_application_quit(G_APPLICATION(data));
}

static void activate(GtkApplication *app, gpointer data)
{
	GtkWidget *window, *box, *label, *entry, *button;

	window = gtk_application_window_new(app);
	box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

	label = gtk_label_new("Who should we cancel today?");
	gtk_container_add(GTK_CONTAINER(box), label);

	entry = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(entry), "FSF");
	gtk_container_add(GTK_CONTAINER(box), entry);

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
