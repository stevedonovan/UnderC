#ifdef _LINK_GTK 
#include <gtk/gtkmain.h>

int s_on;

void special_init(int *argc, char ***argv, bool on_off)
{
  s_on = on_off;
  if(s_on) gtk_init(argc,argv);
}

void special_idle()
{
 if(s_on) 
   while (gtk_events_pending()) 
     gtk_main_iteration();
}
#else
void special_init(int *argc, char ***argv, bool on_off) { }
void special_idle() { }
#endif
  
  
