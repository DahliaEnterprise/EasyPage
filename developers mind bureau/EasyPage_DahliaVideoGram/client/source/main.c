
#include <stdio.h>
 #include <glib-2.0/gio/gio.h>
 #include "/usr/include/glib-2.0/glib.h"
 #include <gio-unix-2.0/gio/gunixsocketaddress.h>
 #include "/usr/include/gtk-3.0/gtk/gtk.h"
 #include <stdlib.h>
 #include <string.h>

static void
activate (GtkApplication* app,
          gpointer        user_data)
{
  GtkWidget *window;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
  gtk_widget_show_all (window);
}

 int  main()
 {
 
      GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), 0, 0);
  g_object_unref (app);

   return 0;
 }
