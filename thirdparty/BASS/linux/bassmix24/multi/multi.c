/*
	BASS multiple output example
	Copyright (c) 2001-2024 Un4seen Developments Ltd.
*/

#define GDK_VERSION_MIN_REQUIRED GDK_VERSION_3_0
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <math.h>
#include "bass.h"
#include "bassmix.h"

#define UIFILE "multi.ui"
GtkBuilder *builder;

GtkWidget *win;
GtkWidget *filesel;

DWORD outdev[2] = { 1, 0 };	// output devices
DWORD source;		// source channel
HSTREAM split[2];	// output splitter streams

// display error messages
void Error(const char *es)
{
	GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(win), GTK_DIALOG_DESTROY_WITH_PARENT,
		GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "%s\n(error code: %d)", es, BASS_ErrorGetCode());
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}

#define GetWidget(id) GTK_WIDGET(gtk_builder_get_object(builder,id))

void WindowDestroy(GtkWidget *obj, gpointer data)
{
	gtk_main_quit();
}

BOOL CreateClone()
{
	// set the device to create 2nd splitter stream on, and then create it
	BASS_SetDevice(outdev[1]);
	if (!(split[1] = BASS_Split_StreamCreate(source, 0, NULL))) {
		Error("Can't create splitter");
		return FALSE;
	}
	BASS_ChannelSetLink(split[0], split[1]); // link the splitters to play together
	return TRUE;
}

void DeviceChanged(GtkComboBox *obj, gpointer data)
{
	const gchar *objname = gtk_buildable_get_name(GTK_BUILDABLE(obj));
	int devn = atoi(objname + 6) - 1; // get device number from button name ("deviceX")
	int sel = gtk_combo_box_get_active(obj); // get the selection
	if (outdev[devn] == sel) return;
	if (!BASS_Init(sel, 44100, 0, NULL, NULL)) { // initialize new device
		Error("Can't initialize device");
		gtk_combo_box_set_active(obj, outdev[devn]);
	} else {
		if (split[devn]) BASS_ChannelSetDevice(split[devn], sel); // move channel to new device
		BASS_SetDevice(outdev[devn]); // set context to old device
		BASS_Free(); // free it
		outdev[devn] = sel;
	}
}

gboolean FileExtensionFilter(const GtkFileFilterInfo *info, gpointer data)
{
	return !regexec((regex_t*)data, info->filename, 0, NULL, 0);
}

void OpenClicked(GtkButton *obj, gpointer data)
{
	int resp = gtk_dialog_run(GTK_DIALOG(filesel));
	gtk_widget_hide(filesel);
	if (resp == GTK_RESPONSE_ACCEPT) {
		char *file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(filesel));
		BASS_ChannelFree(source); // free old channel (splitters automatically freed too)
		if (!(source = BASS_StreamCreateFile(0, file, 0, 0, BASS_STREAM_DECODE | BASS_SAMPLE_LOOP | BASS_SAMPLE_FLOAT))
			&& !(source = BASS_MusicLoad(0, file, 0, 0, BASS_MUSIC_DECODE | BASS_MUSIC_PRESCAN | BASS_MUSIC_POSRESET | BASS_MUSIC_RAMPS | BASS_SAMPLE_LOOP | BASS_SAMPLE_FLOAT, 1))) {
			gtk_button_set_label(obj, "Open file...");
			Error("Can't play the file");
		} else {
			// disassociate source from any device so it isn't freed when changing device
			BASS_ChannelSetDevice(source, BASS_NODEVICE);
			// set the device to create 1st splitter stream on, and then create it
			BASS_SetDevice(outdev[0]);
			if (!(split[0] = BASS_Split_StreamCreate(source, 0, NULL))) {
				BASS_ChannelFree(source);
				source = 0;
				gtk_button_set_label(obj, "Open file...");
				Error("Can't create splitter");
			}
			if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(GetWidget("clone"))))
				CreateClone(); // create a clone
			else
				split[1] = 0; // no clone
			gtk_button_set_label(obj, strrchr(file, '/') + 1);
			{ // update scroller range
				QWORD len = BASS_ChannelGetLength(source, BASS_POS_BYTE);
				if (len == -1) len = 0; // unknown length
				gtk_range_set_range(GTK_RANGE(GetWidget("position")), 0, BASS_ChannelBytes2Seconds(source, len));
			}
			BASS_ChannelPlay(split[0], FALSE); // start playback
		}
		g_free(file);
	}
}

void CloneToggled(GtkToggleButton *obj, gpointer data)
{
	if (!split[0]) return;
	if (gtk_toggle_button_get_active(obj)) { // create clone on device #2
		if (!split[1] && CreateClone()) {
			int offset;
			BASS_INFO info;
			BASS_GetInfo(&info);
			offset = BASS_Split_StreamGetAvailable(split[0]) // get the amount of data the 1st splitter has buffered
				+ BASS_ChannelGetData(split[0], NULL, BASS_DATA_AVAILABLE) // add the amount in its playback buffer
				- BASS_ChannelSeconds2Bytes(split[0], info.latency / 1000.0); // subtract the device's playback delay
			if (offset < 0) offset = 0; // just in case
			BASS_Split_StreamResetEx(split[1], offset); // set the new splitter that far back in the source buffer
			BASS_ChannelPlay(split[1], FALSE); // start the clone
		}
	} else { // remove clone on device #2
		BASS_ChannelFree(split[1]);
		split[1] = 0;
	}
}

gboolean PositionChange(GtkRange *range, GtkScrollType scroll, gdouble value, gpointer data)
{
	BASS_ChannelPause(split[0]); // pause splitter streams (so that resumption following seek can be synchronized)
	BASS_ChannelSetPosition(source, BASS_ChannelSeconds2Bytes(source, value), BASS_POS_BYTE); // set source position
	BASS_Split_StreamReset(source); // reset buffers of all (both) the source's splitters
	BASS_ChannelPlay(split[0], FALSE); // resume playback
	return FALSE;
}

gboolean TimerProc(gpointer data)
{
	if (source)
		gtk_range_set_value(GTK_RANGE(GetWidget("position")), BASS_ChannelBytes2Seconds(split[0], BASS_ChannelGetPosition(split[0], BASS_POS_BYTE))); // update position (using 1st splitter)
	return TRUE;
}

int main(int argc, char* argv[])
{
	regex_t fregex;

	gtk_init(&argc, &argv);

	// check the correct BASS was loaded
	if (HIWORD(BASS_GetVersion()) != BASSVERSION) {
		Error("An incorrect version of BASS was loaded");
		return 0;
	}

	// initialize GUI
	builder = gtk_builder_new();
	if (!gtk_builder_add_from_file(builder, UIFILE, NULL)) {
		char path[PATH_MAX];
		readlink("/proc/self/exe", path, sizeof(path));
		strcpy(strrchr(path, '/') + 1, UIFILE);
		if (!gtk_builder_add_from_file(builder, path, NULL)) {
			Error("Can't load UI");
			return 0;
		}
	}
	win = GetWidget("window1");
	gtk_builder_connect_signals(builder, NULL);

	{ // get list of output devices
		int c;
		BASS_DEVICEINFO di;
		for (c = 0; BASS_GetDeviceInfo(c, &di); c++) {
			gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(GetWidget("device1")), di.name);
			if (c == outdev[0]) gtk_combo_box_set_active(GTK_COMBO_BOX(GetWidget("device1")), c);
			gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(GetWidget("device2")), di.name);
			if (c == outdev[1]) gtk_combo_box_set_active(GTK_COMBO_BOX(GetWidget("device2")), c);
		}
	}
	// initialize the output devices
	if (!BASS_Init(outdev[0], 44100, 0, NULL, NULL) || !BASS_Init(outdev[1], 44100, 0, NULL, NULL)) {
		Error("Can't initialize device");
		return 0;
	}

	{ // initialize file selector
		GtkFileFilter *filter;
		filesel = gtk_file_chooser_dialog_new("Open File", GTK_WINDOW(win), GTK_FILE_CHOOSER_ACTION_OPEN,
			GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);
		filter = gtk_file_filter_new();
		gtk_file_filter_set_name(filter, "Playable files");
		regcomp(&fregex, "\\.(mo3|xm|mod|s3m|it|umx|mp[1-3]|ogg|wav|aif)$", REG_ICASE | REG_NOSUB | REG_EXTENDED);
		gtk_file_filter_add_custom(filter, GTK_FILE_FILTER_FILENAME, FileExtensionFilter, &fregex, NULL);
		gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(filesel), filter);
		filter = gtk_file_filter_new();
		gtk_file_filter_set_name(filter, "All files");
		gtk_file_filter_add_pattern(filter, "*");
		gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(filesel), filter);
	}

	g_timeout_add(100, TimerProc, NULL); // timer to update the position display

	gtk_widget_show(win);
	gtk_main();

	gtk_widget_destroy(filesel);
	regfree(&fregex);

	// release both devices
	BASS_SetDevice(outdev[0]);
	BASS_Free();
	BASS_SetDevice(outdev[1]);
	BASS_Free();
	// free source separately because it isn't associated with a device
	BASS_ChannelFree(source);

	return 0;
}
