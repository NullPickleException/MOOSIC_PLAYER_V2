/*
	BASSCD test player
	Copyright (c) 2003-2024 Un4seen Developments Ltd.
*/

#define GDK_VERSION_MIN_REQUIRED GDK_VERSION_3_0
#include <gtk/gtk.h>
#include <glib/gthread.h>
#include <string.h>
#include "bass.h"
#include "basscd.h"

#define UIFILE "cdtest.ui"
GtkBuilder *builder;

GtkWidget *win;

#define MAXDRIVES 10
int curdrive;
HSTREAM stream[MAXDRIVES];
BOOL advance;
BOOL updating;

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

void PlayTrack(DWORD drive, DWORD track);

// End sync
void CALLBACK EndSync(HSYNC handle, DWORD channel, DWORD data, void *user)
{
	if (advance) { // advance onto next track
		DWORD track = BASS_CD_StreamGetTrack(channel);
		DWORD drive = HIWORD(track);
		DWORD tracks = BASS_CD_GetTracks(drive);
		if (tracks == -1) return; // error, eg. CD removed?
		track = LOWORD(track) + 1; // next track
		if (track >= tracks) return; // no more tracks
		if (drive == curdrive) {
			GtkTreePath *tp = gtk_tree_path_new_from_indices(track, -1);
			gtk_tree_selection_select_path(gtk_tree_view_get_selection(GTK_TREE_VIEW(GetWidget("tracks"))), tp);
			gtk_tree_path_free(tp);
		}
		PlayTrack(drive, track);
	}
}

void PlayTrack(DWORD drive, DWORD track)
{
	if (stream[drive]) { // already have a stream, so just set the track
		if (!BASS_CD_StreamSetTrack(stream[drive], track))
			return; // failed, data track?
	} else {
		stream[drive] = BASS_CD_StreamCreate(drive, track, 0); // create stream
		BASS_ChannelSetSync(stream[drive], BASS_SYNC_END | BASS_SYNC_MIXTIME, 0, EndSync, 0); // set end sync ("mixtime" for gapless advancing)
	}
	if (drive == curdrive)
		gtk_range_set_range(GTK_RANGE(GetWidget("position")), 0, BASS_ChannelGetLength(stream[drive], BASS_POS_BYTE) / 176400); // set pos scroller range
	BASS_ChannelPlay(stream[drive], FALSE); // start playing
}

void UpdateTrackList()
{
	char text[100], tag[10];
	const char *cdtext, *cddb = 0;
	int a, tc;
	GtkTreeView *tree = GTK_TREE_VIEW(GetWidget("tracks"));
	GtkListStore *tm = GTK_LIST_STORE(gtk_tree_view_get_model(tree));
	GtkTreeIter it;
	gtk_list_store_clear(tm);
	tc = BASS_CD_GetTracks(curdrive);
	if (tc == -1) return; // no CD
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(GetWidget("cddb")))) { // get CDDB entry...
		cddb = BASS_CD_GetID(curdrive, BASS_CDID_CDDB_READ_CACHE); // first look for cached entry
		if (!cddb)
			cddb = BASS_CD_GetID(curdrive, BASS_CDID_CDDB_READ); // get CDDB text (simply taking 1st match)
	}
	if (!cddb)
		cdtext = BASS_CD_GetID(curdrive, BASS_CDID_TEXT); // get CD-TEXT
	for (a = 0; a < tc; a++) {
		int len = BASS_CD_GetTrackLength(curdrive, a);
		sprintf(text, "Track %02d", a + 1);
		if (cddb) {
			int taglen = sprintf(tag, "TTITLE%d=", a); // the CDDB tag to look for
			const char *t = strstr(cddb, tag);
			if (t) { // found it
				char *e = strpbrk(t + taglen, "\r\n"); // get end of line
				if (e) sprintf(text, "%.*s", (int)(e - (t + taglen)), t + taglen);
			}
		} else if (cdtext) {
			const char *t = cdtext;
			int taglen = sprintf(tag, "TITLE%d=", a + 1); // the CD-TEXT tag to look for
			while (*t) {
				if (!memcmp(t, tag, taglen)) { // found it
					strcpy(text, t + taglen); // replace "track x" with title
					break;
				}
				t += strlen(t) + 1;
			}
		}
		if (len == -1) // data track
			strcat(text, " (data)");
		else {
			len /= 176400;
			sprintf(text + strlen(text), " (%d:%02d)", len / 60, len % 60);
		}
		gtk_list_store_append(tm, &it);
		gtk_list_store_set(tm, &it, 0, text, 1, a, -1);
	}
	a = BASS_CD_StreamGetTrack(stream[curdrive]);
	if (a != -1) { // this drive has a stream
		GtkTreePath *tp = gtk_tree_path_new_from_indices(LOWORD(a), -1);
		gtk_tree_selection_select_path(gtk_tree_view_get_selection(tree), tp); // select current track
		gtk_tree_path_free(tp);
		gtk_range_set_range(GTK_RANGE(GetWidget("position")), 0, BASS_ChannelGetLength(stream[curdrive], BASS_POS_BYTE) / 176400); // set pos scroller range
	}
}

// Get list of available drives
void SetupDriveList()
{
	GtkComboBoxText *list = GTK_COMBO_BOX_TEXT(GetWidget("drive"));
	int a = 0;
	BASS_CD_INFO cdi;
	updating = 1;
	gtk_combo_box_text_remove_all(list);
	while (a < MAXDRIVES && BASS_CD_GetInfo(a, &cdi)) {
		char text[100];
		sprintf(text, "%s %s v%s", cdi.vendor, cdi.product, cdi.rev);
		gtk_combo_box_text_append_text(list, text);
		a++;
	}
	if (curdrive >= a) curdrive = 0;
	updating = 0;
	gtk_combo_box_set_active(GTK_COMBO_BOX(list), curdrive); // select current drive
	UpdateTrackList();
}

void DriveChanged(GtkComboBox *obj, gpointer data)
{
	if (updating) return;
	curdrive = gtk_combo_box_get_active(obj); // get the selection
	UpdateTrackList();
}

void RescanClicked(GtkButton *obj, gpointer data)
{
	BASS_CD_SetInterface(0); // rescan for drives
	memset(stream, 0, sizeof(stream)); // clear stream handles (freed by rescan)
	SetupDriveList(); // refresh drive list
}

void TracksChanged(GtkTreeView *obj, gpointer data)
{
	GtkTreeModel *tm;
	GtkTreeIter it;
	DWORD track;
	if (!gtk_tree_selection_get_selected(gtk_tree_view_get_selection(obj), &tm, &it)) return;
	gtk_tree_model_get(tm, &it, 1, &track, -1);
	PlayTrack(curdrive, track);
}

void CddbToggled(GtkToggleButton *obj, gpointer data)
{
	UpdateTrackList();
}

void PlayClicked(GtkButton *obj, gpointer data)
{
	if (BASS_ChannelIsActive(stream[curdrive]) == BASS_ACTIVE_PLAYING)
		BASS_ChannelPause(stream[curdrive]);
	else
		BASS_ChannelPlay(stream[curdrive], FALSE);
}

gboolean PositionChange(GtkRange *range, GtkScrollType scroll, gdouble value, gpointer data)
{
	BASS_ChannelSetPosition(stream[curdrive], value * 176400, BASS_POS_BYTE);
	return FALSE;
}

void AdvanceToggled(GtkToggleButton *obj, gpointer data)
{
	advance = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(GetWidget("advance")));
}

void OpenToggled(GtkToggleButton *obj, gpointer data)
{
	if (updating) return;
	BASS_CD_Door(curdrive, BASS_CD_DoorIsOpen(curdrive) ? BASS_CD_DOOR_CLOSE : BASS_CD_DOOR_OPEN); // open/close door
}

void LockToggled(GtkToggleButton *obj, gpointer data)
{
	if (updating) return;
	BASS_CD_Door(curdrive, BASS_CD_DoorIsLocked(curdrive) ? BASS_CD_DOOR_UNLOCK : BASS_CD_DOOR_LOCK); // lock/unlock door
}

gboolean TimerProc(gpointer data)
{
	char time[20] = "-";
	updating = TRUE;
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(GetWidget("open")), BASS_CD_DoorIsOpen(curdrive)); // update "open" status
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(GetWidget("lock")), BASS_CD_DoorIsLocked(curdrive)); // update "lock" status
	updating = FALSE;
	if (BASS_ChannelIsActive(stream[curdrive])) { // playing - update info
		DWORD p = BASS_ChannelBytes2Seconds(stream[curdrive], BASS_ChannelGetPosition(stream[curdrive], BASS_POS_BYTE));
		gtk_range_set_value(GTK_RANGE(GetWidget("position")), p); // update position
		sprintf(time, "%d - %d:%02d", (int)BASS_ChannelGetPosition(stream[curdrive], BASS_POS_CD_TRACK) + 1, p / 60, p % 60);
	} else {
		GtkTreeView *tree = GTK_TREE_VIEW(GetWidget("tracks"));
		if (!gtk_tree_model_iter_n_children(gtk_tree_view_get_model(tree), 0)) { // empty track list - refresh
			if (BASS_CD_IsReady(curdrive)) UpdateTrackList();
		} else if (!BASS_CD_IsReady(curdrive)) { // no CD - free stream & clear list
			BASS_StreamFree(stream[curdrive]);
			stream[curdrive] = 0;
			gtk_list_store_clear(GTK_LIST_STORE(gtk_tree_view_get_model(tree)));
		}
	}
	gtk_label_set_text(GTK_LABEL(GetWidget("time")), time);
	return TRUE;
}

int main(int argc, char* argv[])
{
#if !GLIB_CHECK_VERSION(2,32,0)
	g_thread_init(NULL);
#endif
	gdk_threads_init();
	gtk_init(&argc, &argv);

	// check the correct BASS was loaded
	if (HIWORD(BASS_GetVersion()) != BASSVERSION) {
		Error("An incorrect version of BASS was loaded");
		return 0;
	}

	// initialize default output device
	if (!BASS_Init(-1, 44100, 0, NULL, NULL)) {
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

	{ // setup track list
		GtkTreeView *list = GTK_TREE_VIEW(GetWidget("tracks"));
		GtkTreeViewColumn *col = gtk_tree_view_column_new();
		gtk_tree_view_append_column(list, col);
		GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
		gtk_tree_view_column_pack_start(col, renderer, TRUE);
		gtk_tree_view_column_add_attribute(col, renderer, "text", 0);
		GtkListStore *liststore = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_INT);
		gtk_tree_view_set_model(list, GTK_TREE_MODEL(liststore));
		g_object_unref(liststore);
	}

	SetupDriveList();

	g_timeout_add(500, TimerProc, NULL);

	gdk_threads_enter();
	gtk_main();
	gdk_threads_leave();

	// free the output device
	BASS_Free();

	return 0;
}
