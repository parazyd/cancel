/* 
 * gcc -o cancel $(pkg-config --cflags --libs gtk+-2.0) cancel.c
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>

#include <gtk/gtk.h>

#define nelem(x) (sizeof (x) / sizeof *(x))

static const char *karens[] = {
	"karens/karen0.jpg",
	"karens/karen1.jpg",
	"karens/karen2.jpg",
	"karens/karen3.jpg",
};

static void lynch(int unused, GtkWidget *entry)
{
	int fd;
	char req[64];
	struct hostent *he;
	struct sockaddr_in addr;

	if ((he = gethostbyname("bitreich.org")) == NULL)
		return;

	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(70);
	addr.sin_addr = *((struct in_addr *)he->h_addr);
	memset(&(addr.sin_zero), 0, 8);

	snprintf(req, sizeof(req), "/cancel\t%s\r\n",
		gtk_entry_get_text(GTK_ENTRY(entry)));

	if (connect(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr)) < 0)
		goto out;

	send(fd, req, strlen(req), 0);

out:
	close(fd);
	(void)unused;
}

static void cancel()
{
	GtkWidget *dialog, *content_area, *label;

	dialog = gtk_dialog_new_with_buttons("Cancelled", NULL,
		GTK_DIALOG_MODAL, "OK", GTK_RESPONSE_ACCEPT, NULL);

	content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
	label = gtk_label_new("\nSuccessfully cancelled!\n");
	gtk_container_add(GTK_CONTAINER(content_area), label);

	gtk_container_add(GTK_CONTAINER(content_area), gtk_image_new_from_file(
		karens[g_rand_int_range(g_rand_new(), 0, nelem(karens))]));

	g_signal_connect(dialog, "response", G_CALLBACK(gtk_main_quit), NULL);

	gtk_widget_show_all(dialog);
}

int main(int argc, char **argv)
{
	GtkWidget *window, *align, *box, *label, *entry, *lynch_mob, *button;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(window), 320, 240);
	gtk_window_set_title(GTK_WINDOW(window), "Cancel Tool");

	g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

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
	g_signal_connect(button, "clicked", G_CALLBACK(lynch), entry);

	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}
