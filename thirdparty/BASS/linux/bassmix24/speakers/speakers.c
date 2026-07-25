/*
	BASSmix multi-speaker example
	Copyright (c) 2009-2024 Un4seen Developments Ltd.
*/

#define GDK_VERSION_MIN_REQUIRED GDK_VERSION_3_0
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "bass.h"
#include "bassmix.h"

#define UIFILE "speakers.ui"
GtkBuilder *builder;

GtkWidget *win;
GtkWidget *filesel;

HSTREAM mixer, source; // mixer and source channels

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

void SetMatrix(BOOL ramp)
{
	float *matrix;
	BASS_CHANNELINFO mi, si;
	BASS_ChannelGetInfo(mixer, &mi); // get mixer info for channel count
	BASS_ChannelGetInfo(source, &si); // get source info for channel count
	matrix = (float*)malloc(mi.chans * si.chans * sizeof(float)); // allocate matrix (mixer channel count * source channel count)
	memset(matrix, 0, mi.chans * si.chans * sizeof(float)); // initialize it to empty/silence
/*
	set the mixing matrix depending on the speaker switches
	mono & stereo sources are duplicated on each enabled pair of speakers
*/
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(GetWidget("speaker1")))) { // 1st pair of speakers enabled
		matrix[0 * si.chans + 0] = 1;
		if (si.chans == 1) // mono source
			matrix[1 * si.chans + 0] = 1;
		else
			matrix[1 * si.chans + 1] = 1;
	}
	if (mi.chans >= 4 && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(GetWidget("speaker2")))) { // 2nd pair of speakers enabled
		if (si.chans > 2) { // multi-channel source
			matrix[2 * si.chans + 2] = 1;
			if (si.chans > 3) matrix[3 * si.chans + 3] = 1;
		} else {
			matrix[2 * si.chans + 0] = 1;
			if (si.chans == 1) // mono source
				matrix[3 * si.chans + 0] = 1;
			else // stereo source
				matrix[3 * si.chans + 1] = 1;
		}
	}
	if (mi.chans >= 6 && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(GetWidget("speaker3")))) { // 3rd pair of speakers enabled
		if (si.chans > 2) { // multi-channel source
			if (si.chans > 4) matrix[4 * si.chans + 4] = 1;
			if (si.chans > 5) matrix[5 * si.chans + 5] = 1;
		} else {
			matrix[4 * si.chans + 0] = 1;
			if (si.chans == 1) // mono source
				matrix[5 * si.chans + 0] = 1;
			else // stereo source
				matrix[5 * si.chans + 1] = 1;
		}
	}
	if (mi.chans >= 8 && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(GetWidget("speaker4")))) { // 4th pair of speakers enabled
		if (si.chans > 2) { // multi-channel source
			if (si.chans > 6) matrix[6 * si.chans + 6] = 1;
			if (si.chans > 7) matrix[7 * si.chans + 7] = 1;
		} else {
			matrix[6 * si.chans + 0] = 1;
			if (si.chans == 1) // mono source
				matrix[7 * si.chans + 0] = 1;
			else // stereo source
				matrix[7 * si.chans + 1] = 1;
		}
	}
	BASS_Mixer_ChannelSetMatrixEx(source, matrix, ramp ? 0.1 : 0); // apply the matrix
	free(matrix);
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
		BASS_CHANNELINFO ci;
		BASS_INFO di;
		BASS_StreamFree(mixer); // free old mixer (and source due to AUTOFREE)
		if (!(source = BASS_StreamCreateFile(0, file, 0, 0, BASS_STREAM_DECODE | BASS_SAMPLE_LOOP | BASS_SAMPLE_FLOAT))
			&& !(source = BASS_MusicLoad(0, file, 0, 0, BASS_MUSIC_DECODE | BASS_MUSIC_RAMPS | BASS_SAMPLE_LOOP | BASS_SAMPLE_FLOAT, 1))) {
			gtk_button_set_label(obj, "Open file...");
			Error("Can't play the file");
		} else {
			BASS_ChannelGetInfo(source, &ci); // get source info for sample rate
			BASS_GetInfo(&di); // get device info for speaker count
			mixer = BASS_Mixer_StreamCreate(ci.freq, di.speakers < 8 ? di.speakers : 8, BASS_SAMPLE_FLOAT); // create mixer with source sample rate and device speaker count
			if (!mixer) { // failed
				BASS_ChannelFree(source);
				gtk_button_set_label(obj, "Open file...");
				Error("Can't create mixer");
			} else {
				BASS_ChannelSetAttribute(mixer, BASS_ATTRIB_BUFFER, 0); // disable playback buffering to minimize latency
				BASS_Mixer_StreamAddChannel(mixer, source, BASS_MIXER_CHAN_MATRIX | BASS_STREAM_AUTOFREE); // add the source to the mix with matrix-mixing enabled
				SetMatrix(FALSE); // set the matrix
				BASS_ChannelPlay(mixer, FALSE); // start playing
				gtk_button_set_label(obj, strrchr(file, '/') + 1);
				// enable the speaker switches according to the speaker count
				gtk_widget_set_sensitive(GetWidget("speaker2"), di.speakers >= 4);
				gtk_widget_set_sensitive(GetWidget("speaker3"), di.speakers >= 6);
				gtk_widget_set_sensitive(GetWidget("speaker4"), di.speakers >= 8);
			}
		}
		g_free(file);
	}
}

void SpeakerToggled(GtkButton *obj, gpointer data)
{
	SetMatrix(TRUE); // update the matrix
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

	// initialize default device
	if (!BASS_Init(-1, 44100, BASS_DEVICE_SPEAKERS, NULL, NULL)) {
		Error("Can't initialize device");
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

	gtk_widget_show(win);
	gtk_main();

	gtk_widget_destroy(filesel);
	regfree(&fregex);

	BASS_Free();

	return 0;
}
