
#ifndef __MPLAYER_MAIN
#define __MPLAYER_MAIN

extern int use_gui;
extern char* current_module;
extern int fullscreen;
extern int vcd_track;

extern int    video_family;
extern char * video_driver;
extern char * audio_driver;
extern int    has_audio;
extern float  audio_delay;

extern int osd_level;
extern int osd_visible;

extern char * font_name;
extern float  font_factor;

extern char * sub_name;
extern float  sub_delay;
extern float  sub_fps;
extern int    sub_auto;

extern char * filename;

extern void exit_player(char* how);

#endif
