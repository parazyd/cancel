/* 
 * gcc -o cancel $(pkg-config --cflags --libs gtk+-2.0) cancel.c
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

static void cancel(GtkWidget *window, gpointer data)
{
	GtkWidget *dialog, *content_area, *label, *karen;

	dialog = gtk_dialog_new_with_buttons("Cancelled", NULL,
		GTK_DIALOG_MODAL, "OK", GTK_RESPONSE_ACCEPT, NULL);

	content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
	label = gtk_label_new("\nSuccessfully cancelled!\n");
	gtk_container_add(GTK_CONTAINER(content_area), label);

	karen = gtk_image_new_from_file("karen.png");
	gtk_container_add(GTK_CONTAINER(content_area), karen);

	gtk_widget_show_all(dialog);

	g_signal_connect_swapped(dialog, "response",
		G_CALLBACK(gtk_main_quit), window);
}

int main(int argc, char **argv)
{
	GtkWidget *window, *align, *box, *label, *entry, *lynch_mob, *button;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(window), 320, 240);

	align = gtk_alignment_new(0, 0, 1, 0);
	gtk_alignment_set_padding(GTK_ALIGNMENT(align), 15, 15, 50, 50);
	gtk_container_add(GTK_CONTAINER(window), align);

	box = gtk_vbox_new(TRUE, 10);
	gtk_container_add(GTK_CONTAINER(align), box);

	label = gtk_label_new("Who should we cancel today?");
	gtk_container_add(GTK_CONTAINER(box), label);

	entry = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(entry), "Freedom of speech");
	gtk_container_add(GTK_CONTAINER(box), entry);

	lynch_mob = gtk_check_button_new_with_label(
		"There is a lynch mob outside my house");
	gtk_container_add(GTK_CONTAINER(box), lynch_mob);

	button = gtk_button_new_with_label("CANCEL");
	gtk_container_add(GTK_CONTAINER(box), button);
	g_signal_connect(button, "clicked", G_CALLBACK(cancel), window);

	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}
