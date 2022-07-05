#include <stdio.h>
 #include <glib-2.0/gio/gio.h>
 #include "/usr/include/glib-2.0/glib.h"
 #include <gio-unix-2.0/gio/gunixsocketaddress.h>
 #include "/usr/include/gtk-3.0/gtk/gtk.h"
 #include <stdlib.h>
 #include <string.h>

#include "/usr/include/GL/gl.h"
#include "/usr/include/GL/glut.h"

//#include <GL/gl.h>
//#include <GL/glut.h>

/*using glm::mat4;
using glm::vec3;
using glm::lookAt;
using glm::perspective;
using glm::rotate;*/


/* the GtkGLArea widget */
static GtkWidget *gl_area = NULL;

static const GLfloat triangle_vertex_position[] = { 0.0, 0.5, 0.0, 1.0, 0.0, 0.0, 1.0,
                                 										 -0.5, -0.5, 0.0, 0.0, 1.0, 0.0, 1.0,
                                 										 0.5, -0.5, 0.0, 0.0, 0.0, 1.0, 1.0};

																										 
GLuint triangle_vertex_shader;

																										 
GLuint create_vertex_shader(GLchar vertex_source)
{
	GLuint output = 0;
	
	GLunint shader;
	shader = glCreateShader(GL_VERTEX_SHADER);
	
	glShaderSource(shader, 1, &vertex_source, 0);
	
	glCompileShader(shader);
	
	glGetShaderiv (shader, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE)
  {
    int log_len;
    char *buffer;
    glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &log_len);
    buffer = (char*)g_malloc (log_len + 1);
    glGetShaderInfoLog (shader, log_len, NULL, buffer);
    g_warning ("Compile failure in %s shader:\n%s",
               type == GL_VERTEX_SHADER ? "vertex" : "fragment",
               buffer);
    g_free (buffer);
    glDeleteShader (shader);
    return 0;
  }
	
	output = shader;
	
	return output;
}

static void realize (GtkWidget *widget)
{
/*  GdkGLContext *context;
  gtk_gl_area_make_current (GTK_GL_AREA (widget));
  if (gtk_gl_area_get_error (GTK_GL_AREA (widget)) != NULL)
    return;
  context = gtk_gl_area_get_context (GTK_GL_AREA (widget));
  init_buffers (&position_buffer, NULL);
  init_shaders (&program);
*/
  glEnable(GL_CULL_FACE);
  glFrontFace(GL_CCW);  
  glCullFace(GL_BACK);
  glEnable(GL_DEPTH_TEST);
	
	triangle_vertex_shader = create_vertex_shader(GLchar vertex_source);
	
}

static void unrealize (GtkWidget *widget)
{
  /*gtk_gl_area_make_current (GTK_GL_AREA (widget));

  if (gtk_gl_area_get_error (GTK_GL_AREA (widget)) != NULL)
    return;

  glDeleteBuffers (1, &position_buffer);
  glDeleteProgram (program);*/
}


static gboolean render (GtkGLArea *area, GdkGLContext *context)
{
  glClearColor (255, 0, 0, 0);
  glClear (GL_COLOR_BUFFER_BIT);
  return TRUE;
}



static void activate (GtkApplication* app, gpointer user_data)
{
  GtkWidget * window;

  //window = gtk_application_window_new (app);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size (GTK_WINDOW(window),1024,728);
  gtk_window_set_title(GTK_WINDOW(window), "GL Area");
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);
  
	GtkWidget * box;
	box = gtk_box_new (GTK_ORIENTATION_VERTICAL, FALSE);
  g_object_set (box, "margin", 12, NULL);
  gtk_box_set_spacing (GTK_BOX (box), 6);
  gtk_container_add (GTK_CONTAINER (window), box);
  gl_area = gtk_gl_area_new ();
  gtk_box_pack_start (GTK_BOX(box), gl_area,1,1, 0);
  
	/**release initializes gl resources and unintiializes gl resources(similar to the exit signal when a window is closed)*/
	g_signal_connect (gl_area, "realize", G_CALLBACK (realize), NULL);
  g_signal_connect (gl_area, "unrealize", G_CALLBACK (unrealize), NULL);
	
	//gl is ready for next render
	g_signal_connect (gl_area, "render", G_CALLBACK (render), NULL);
  
	//
	
	g_signal_connect(G_OBJECT(window), "delete-event",
                 G_CALLBACK(gtk_main_quit), NULL);
  gtk_widget_show_all(GTK_WIDGET(window));
  gtk_main();

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
