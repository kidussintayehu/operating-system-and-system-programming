#include <gtk/gtk.h>
#include <stdio.h>

static int counter = 0;

void greet(GtkWidget *widget, gpointer data)
{
	g_print("Welcome to GTK\n");
	g_print("%s clicked %d times\n",
			(char *)data, ++counter);
}

void destroy(GtkWidget *widget, gpointer data)
{
	gtk_main_quit();
}


int main(int argc, char *argv[])
{

	GtkWidget *window;
	// condition 1
	GtkWidget *window;/* this is condition 1.1 */GtkWidget *button;
	gtk_init(&argc, &argv);/*this is condition 1.2 */ window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	int i = 0 /* this is condition 1.3 */ int j = 0;
	int k = 0// condition 2  

	g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);
//condition 3
	gtk_container_set_border_width(GTK_CONTAINER(window), 20);/* this condtion 3.1
	according to the assignment */

	/* this is condition 3.2
	according to the
	assignment */
//condition 4

	button = gtk_button_new_with_label("Click Me!");/* this condition 4 
	about nested c-90 comments
	* You /*may play */with the */

//condition 5
	g_signal_connect(GTK_OBJECT(button),
					 "clicked", G_CALLBACK(greet),
					 "button");
	"/* this is condition 5 .1
		* about string literals
				  *difference.
		*/ "

			  /* this is condition 5.2 "string literal inside the c-90 comment" */
			  /* this is condition 5.3 "single qoute  */
		
// condition 6

		'/* this is condition 6.1.
		*about character literal.
		*/ '

		/* this is condition 6.2
		* character 'literal' inside the commment
		*/
	/* this is condition 6.3
		* character 'literal inside the commment
		*/
	//condition 7
	/* this is condition 7.1
		* character 'literal inside the commment
		*/
		gtk_container_add(GTK_CONTAINER(window), button);

	/* this is condition 7.1
		* character 'literal inside the commment
		*/

		gtk_container_add(GTK_CONTAINER(windo
	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}

// condtion 8
/* Lets set the "border" width of the window to 20.
 * You may play with the value and see the
 *difference.
 */


/* hi