/* postmarketos_welcome-window.c
 *
 * Copyright 2020 Martijn Braam
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

#include "postmarketos_welcome-config.h"
#include "postmarketos_welcome-window.h"

#define WELCOME_MESSAGE_LOCATION "/etc/welcome-message"

struct _PostmarketosWelcomeWindow
{
  GtkApplicationWindow  parent_instance;

  /* Template widgets */
  GtkHeaderBar        *header_bar;
  GtkButton           *close_button;
  GtkLabel            *custom_text;
};

G_DEFINE_TYPE (PostmarketosWelcomeWindow, postmarketos_welcome_window, GTK_TYPE_APPLICATION_WINDOW)

static void
postmarketos_welcome_window_class_init (PostmarketosWelcomeWindowClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/postmarketos/Welcome/postmarketos_welcome-window.ui");
  gtk_widget_class_bind_template_child (widget_class, PostmarketosWelcomeWindow, header_bar);
  gtk_widget_class_bind_template_child (widget_class, PostmarketosWelcomeWindow, close_button);
  gtk_widget_class_bind_template_child (widget_class, PostmarketosWelcomeWindow, custom_text);


}

static void
postmarketos_welcome_window_init (PostmarketosWelcomeWindow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
  FILE *f;
  f = fopen(WELCOME_MESSAGE_LOCATION, "r");
  if (f == NULL) {
      fprintf(stderr, "could not open %s\n", WELCOME_MESSAGE_LOCATION);
      return;
  }
  fseek(f, 0, SEEK_END);
  long fsize = ftell(f);
  fseek(f, 0, SEEK_SET);

  char *buff = malloc(fsize+1);
  fread(buff, 1, fsize, f);
  fclose(f);

  buff[fsize] = 0;

  gtk_label_set_markup(self->custom_text, buff);

  /* Remove from autostart (-f: ignore nonexistent) */
  system("rm -vf ~/.config/autostart/org.postmarketos.Welcome.desktop");
}
