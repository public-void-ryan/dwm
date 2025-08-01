/* Constants */
#define TERMINAL "alacritty"
#define TERMCLASS "Alacritty"

/* appearance */
static unsigned int borderpx = 0; /* border pixel of windows */
static unsigned int snap = 32;	  /* snap pixel */
static unsigned int gappih = 2;	  /* horiz inner gap between windows */
static unsigned int gappiv = 2;	  /* vert inner gap between windows */
static unsigned int gappoh = 0;	  /* horiz outer gap between windows and screen edge */
static unsigned int gappov = 0;	  /* vert outer gap between windows and screen edge */
static int swallowfloating = 0;	  /* 1 means swallow floating windows by default */
static int smartgaps = 1;		  /* 1 means no outer gap when there is only one window */
static int showbar = 1;			  /* 0 means no bar */
static int topbar = 1;			  /* 0 means bottom bar */
static const int vertpad = 0;	  /* vertical padding of bar */
static const int sidepad = 0;	  /* horizontal padding of bar */
static char *fonts[] = {"HackNerdFont:size=12:antialias=true"};
static char normbgcolor[] = "#222222";
static char normbordercolor[] = "#ffffff";
static char normfgcolor[] = "#bbbbbb";
static char selfgcolor[] = "#eeeeee";
static char selbordercolor[] = "#ffffff";
static char selbgcolor[] = "#222222";
// static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
	/*               fg           bg           border   */
	[SchemeNorm] = {normfgcolor, normbgcolor, normbordercolor},
	[SchemeSel] = {selfgcolor, selbgcolor, selbordercolor},
};

typedef struct
{
	const char *name;
	const void *cmd;
} Sp;

typedef struct {
	const char **cmd;
	unsigned int tag;
} SpawnViewArg;

const char *spcmd1[] = {TERMINAL, "--class", "spterm", "-o", "window.dimensions.columns=120", "-o", "window.dimensions.lines=24", NULL};
const char *spcmd2[] = {
    "alacritty",
    "--class", "spcalc",
    "--config-file", "/home/ryan/.config/alacritty/spcalc.toml",
    "-e", "bc", "-lq",
    NULL
};
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm", spcmd1},
	{"spcalc", spcmd2},
};

/* tagging */
static const char *tags[] = {"", "󰖟", "󰎞", "󰇰", "󰗃", "󰝚", "󰦔"};

/* Define tag constants */
#define TAG1 (1 << 0)
#define TAG2 (1 << 1)
#define TAG3 (1 << 2)
#define TAG4 (1 << 3)
#define TAG5 (1 << 4)
#define TAG6 (1 << 5)
#define TAG7 (1 << 6)
#define TAG8 (1 << 7)

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   isterminal noswallow monitor    float x,y,w,h         floatborderpx 
	{ "Gimp",     NULL,       NULL,       0,            1,           0,         0,       -1,        50,50,500,500,        5 }, */
	{ TERMCLASS,  NULL,       NULL,       0,            0,           1,         0,       -1,        80, 50, 1280, 720,    0 },
	{ "librewolf", NULL,      NULL,       TAG2,         0,           0,         0,       -1,        80, 50, 1280, 720,    0 },
	{ "vesktop",  NULL,       NULL,       TAG1,         0,           0,         0,        1,        80, 50, 1280, 720,    0 },
	{ "Spotify",  "spotify",  NULL,       TAG6,         0,           0,         0,       -1,        80, 50, 1280, 720,    0 },
	{ "pocket-casts-linux", NULL, NULL,   TAG7,         0,           0,         0,       -1,        80, 50, 1280, 720,    0 },
	{ "thunderbird", NULL,    NULL,       TAG4,         0,           0,         0,       -1,        80, 50, 1280, 720,    0 },
	{ "FreeTube", "freetube", NULL,       TAG5,         0,           0,         0,       -1,        80, 50, 1280, 720,    0 },
	{ "obsidian", "obsidian", NULL,       TAG3,         0,           0,         0,       -1,        80, 50, 1280, 720,    0 },
	{ NULL,       "bg",       NULL,       TAG8,         0,           0,         0,       -1,        -1, -1, -1, -1,       0 },
	{ NULL,       "spterm",   NULL,       SPTAG(0),     1,           1,         0,       -1,        50, 50, 1280, 720,    0 },
	{ NULL, "spcalc", NULL, SPTAG(1), 1, 1, 0, -1, -1, -1, -1, -1, 0 },

	{ NULL,       NULL,       "Event Tester", 0,        0,           0,         1,       -1,        50, 50, 1280, 720,    0 },
	{ "WowUpCf",  NULL,       NULL,       0,            1,           0,         0,       -1,        50, 50, 1280, 720,    0 },
	{ "battle.net.exe", NULL, NULL,       0,            1,           0,         0,       -1,        50, 50, 1280, 720,    0 },
	{ "Qalculate-gtk", NULL,  NULL,       0,            1,           0,         0,       -1,        50, 50, 1280, 720,    0 },
	{ "steam_app_", NULL,     NULL,       0,            1,           0,         0,       -1,        50, 50, 1280, 720,    0 },
	{ "steam",    NULL,       NULL,       0,            1,           0,         0,       -1,        50, 50, 1280, 720,    0 },
	{ "ut2004-bin-linux-amd64", NULL, NULL, 0,          1,           0,         0,       -1,        50, 50, 1280, 720,    0 },
	{ NULL,       NULL,       "Picture in picture", 0,  1,           0,         0,       -1,        50, 50, 1280, 720,    0 },
	{ "librewolf", "Toolkit", "Picture-in-Picture", 0,  1,           0,         0,       -1,        50, 50, 1280, 720,    0 },
	{ "mpv",       NULL,       "webcam",    0,          1,           0	,       0,     	 -1,        50, 50, 1280, 720,    0 },
};

/* layout(s) */
static float mfact = 0.50;	/* factor of master area size [0.05..0.95] */
static int nmaster = 1;		/* number of clients in master area */
static int resizehints = 0; /* 1 means respect size hints in tiled resizals */
#define FORCE_VSPLIT 1		/* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const int lpm[] = {
	/* Index of preferred layout], if LENGTH(lpm)<#monitors -> default layout */
	0, 1};
static const Layout layouts[] = {
	/* symbol     arrange function */
	{"", tile},	 /* Default: Master on left, slaves on right */
	{"", bstack}, /* Master on top, slaMaster in middle, slaves on sides */
	{"[@]", spiral},   /* Fibonacci spiral */
	{"[\\]", dwindle}, /* Decreasing in size right and leftward */
	{"[D]", deck},	  /* Master on left, slaves in monocle-like mode on right */
	{"|M|", centeredmaster},		 /* Master in middle, slaves on sides */
	{">M>", centeredfloatingmaster}, /* Same but master floats */
	{"><>", NULL}, /* no layout function means floating behavior */
	{NULL, NULL},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                          \
	{MODKEY, KEY, view, {.ui = 1 << TAG}},                         \
		{MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}}, \
		{MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},          \
		{MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},
#define STACKKEYS(MOD, ACTION)                      \
	{MOD, XK_j, ACTION##stack, {.i = INC(+1)}},     \
		{MOD, XK_k, ACTION##stack, {.i = INC(-1)}}, \
		{MOD, XK_v, ACTION##stack, {.i = 0}}, /* { MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \ */
											  /* { MOD, XK_a,     ACTION##stack, {.i = 1 } }, \ */
											  /* { MOD, XK_z,     ACTION##stack, {.i = 2 } }, \ */
											  /* { MOD, XK_x,     ACTION##stack, {.i = -1 } }, */

/* helper for spawning shell commands in pre dwm-5.0 fashion */
#define SHCMD(cmd)                                           \
	{                                                        \
		.v = (const char *[]) { "/bin/sh", "-c", cmd, NULL } \
	}

static void spawn_and_view(const Arg *arg) {
	const SpawnViewArg *sva = arg->v;
	spawn(&(const Arg){.v = sva->cmd});
	view(&(const Arg){.ui = sva->tag});
}



static void spawn_and_view(const Arg *arg);

/* commands */
static const char *termcmd[] = {TERMINAL, NULL};
static const char *ocr_cmd[] = {"/home/ryan/.local/bin/ocr", NULL};
static const char *prtscrcmd[] = {"flameshot", "gui", NULL};
static const char *launcherduncmd[] = {"/home/ryan/.local/bin/launcher", NULL};
static const char *launcherruncmd[] = {"/home/ryan/.local/bin/launchercmd", NULL};
static const char *freetube_cmd[] = { "freetube", NULL };
static const SpawnViewArg freetube_combined = { freetube_cmd, TAG5 };
static const char *spotify_cmd[] = { "spotify_wrapper", NULL };
static const SpawnViewArg spotify_combined = { spotify_cmd, TAG6 };
// launch browser with a tag
static const char *browser_cmd[] = { "sh", "-c", "$BROWSER", NULL };
static const SpawnViewArg browser_combined = { browser_cmd, TAG2 };
// launch thunderbird with a tag
static const char *thunderbird_cmd[] = { "thunderbird", NULL };
static const SpawnViewArg thunderbird_combined = { thunderbird_cmd, TAG4 };
// launch obsidian with a tag
static const char *obsidian_cmd[] = { "obsidian", NULL };
static const SpawnViewArg obsidian_combined = { obsidian_cmd, TAG3 };


/*
 * Xresources preferences to load at startup
 */

ResourcePref resources[] = {
	{"color0", STRING, &normbordercolor},
	{"color8", STRING, &selbordercolor},
	{"color0", STRING, &normbgcolor},
	{"color4", STRING, &normfgcolor},
	{"color0", STRING, &selfgcolor},
	{"color4", STRING, &selbgcolor},
	{"borderpx", INTEGER, &borderpx},
	{"snap", INTEGER, &snap},
	{"showbar", INTEGER, &showbar},
	{"topbar", INTEGER, &topbar},
	{"nmaster", INTEGER, &nmaster},
	{"resizehints", INTEGER, &resizehints},
	{"mfact", FLOAT, &mfact},
	{"gappih", INTEGER, &gappih},
	{"gappiv", INTEGER, &gappiv},
	{"gappoh", INTEGER, &gappoh},
	{"gappov", INTEGER, &gappov},
	{"swallowfloating", INTEGER, &swallowfloating},
	{"smartgaps", INTEGER, &smartgaps},
};

#include <X11/XF86keysym.h>
#include "shiftview.c"

static Key keys[] = {
	/* modifier                     key        function        argument */
	STACKKEYS(MODKEY, focus)
	STACKKEYS(MODKEY | ShiftMask, push)

	TAGKEYS(XK_1, 0)
	TAGKEYS(XK_2, 1)
	TAGKEYS(XK_3, 2)
	TAGKEYS(XK_4, 3)
	TAGKEYS(XK_5, 4)
	TAGKEYS(XK_6, 5)
	TAGKEYS(XK_7, 6)

	{MODKEY,                       XK_0,        view,           {.ui = ~0}},
	{MODKEY | ShiftMask,           XK_0,        tag,            {.ui = ~0}},
	{MODKEY,                       XK_minus,    spawn,          SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-; kill -44 $(pidof dwmblocks)")},
	{MODKEY | ShiftMask,           XK_minus,    spawn,          SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 15%-; kill -44 $(pidof dwmblocks)")},
	{MODKEY,                       XK_equal,    spawn,          SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+; kill -44 $(pidof dwmblocks)")},
	{MODKEY | ShiftMask,           XK_equal,    spawn,          SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 15%+; kill -44 $(pidof dwmblocks)")},
	{MODKEY,                       XK_BackSpace,spawn,          SHCMD("powermenu")},
	{MODKEY | ShiftMask,           XK_BackSpace,spawn,          SHCMD("powermenu")},
	{MODKEY,                       XK_Escape,		spawn,      SHCMD("powermenu")},
	{MODKEY,                       XK_Tab,      view,           {0}},
	{MODKEY,                       XK_q,        killclient,     {0}},
	{MODKEY | ShiftMask,           XK_q,        spawn,          SHCMD("powermenu")},
	{MODKEY,                       XK_w,        spawn_and_view, {.v = &browser_combined} },
	{MODKEY | ShiftMask,           XK_w,        spawn,          SHCMD("define_word")},
	{MODKEY,                       XK_e,        spawn_and_view, {.v = &thunderbird_combined} },
	{MODKEY,                       XK_v,        spawn,          SHCMD("clipmenu")},
	{MODKEY | ShiftMask, 		   XK_v, 		spawn, 			SHCMD("setsid vesktop >/dev/null 2>&1")},
	{MODKEY | ShiftMask,           XK_r,        spawn,          SHCMD("setsid thunar")},
	{ControlMask | ShiftMask,      XK_r,        spawn,          SHCMD("rssget")},
	{MODKEY,                       XK_r,        spawn,          SHCMD(TERMINAL " -e lfub")},
	{MODKEY,                       XK_t,        setlayout,      {.v = &layouts[0]}}, /* tile */
	{MODKEY | ShiftMask,           XK_t,        setlayout,      {.v = &layouts[1]}}, /* bstack */
	{MODKEY,                       XK_y,        spawn_and_view, {.v = &freetube_combined} },
	{MODKEY | ShiftMask,           XK_y,        spawn,          SHCMD("alacritty -e /home/ryan/.local/bin/statusbar/sb-popupgrade")},
	{MODKEY,                       XK_p,        spawn,          SHCMD("pocket-casts-linux")},
	{MODKEY | ShiftMask,           XK_p,        spawn,          SHCMD("colorpicker")},
	{MODKEY | ShiftMask,           XK_p,        spawn,          SHCMD("mpc pause ; pauseallmpv")},
	{MODKEY,                       XK_bracketleft, spawn,       SHCMD("mpc seek -10")},
	{MODKEY | ShiftMask,           XK_bracketleft, spawn,       SHCMD("mpc seek -60")},
	{MODKEY,                       XK_bracketright, spawn,      SHCMD("mpc seek +10")},
	{MODKEY | ShiftMask,           XK_bracketright, spawn,      SHCMD("mpc seek +60")},
	{MODKEY,                       XK_backslash, view,          {0}},
	{MODKEY,                       XK_a,        togglegaps,     {0}},
	{MODKEY | ShiftMask,           XK_a,        defaultgaps,    {0}},
	{MODKEY, 					   XK_s, 		spawn_and_view, {.v = &spotify_combined} },
	{MODKEY | ShiftMask,           XK_s,        togglesticky,   {0}},
	{MODKEY,                       XK_d,        spawn,          {.v = launcherduncmd}},
	{MODKEY | ShiftMask,           XK_d,        spawn,          {.v = launcherruncmd}},
	{MODKEY,                       XK_f,        togglefullscr,  {0}},
	{MODKEY | ShiftMask,           XK_f,        setlayout,      {.v = &layouts[7]}}, /* float */
	{MODKEY,                       XK_g,        spawn,     		SHCMD("qutebrowser --basedir /home/ryan/.local/share/qutebrowser-chatgpt --target=window --set tabs.show never --set statusbar.show never https://chat.openai.com")},
	{MODKEY | ShiftMask,           XK_g,        shifttag,       {.i = -1}},
	{MODKEY,                       XK_h,        setmfact,       {.f = -0.05}},
	{MODKEY | ShiftMask,           XK_h,        spawn,          SHCMD("hyphenate")},
	{MODKEY | ShiftMask,           XK_k,        spawn,          SHCMD("xkill")},
	{MODKEY,                       XK_l,        setmfact,       {.f = +0.05}},
	{MODKEY | ShiftMask,           XK_l,        spawn,          SHCMD("lutris")},
	{MODKEY,                       XK_semicolon,shiftview,      {.i = 1}},
	{MODKEY | ShiftMask,           XK_semicolon,shifttag,       {.i = 1}},
	{MODKEY,                       XK_apostrophe, togglescratch,{.ui = 1}},
	{MODKEY | ShiftMask,           XK_apostrophe, togglesmartgaps, {0}},
	{MODKEY,                       XK_Return,   spawn,          {.v = termcmd}},
	{MODKEY,                       XK_KP_Enter, spawn,          {.v = termcmd}},
	{MODKEY | ShiftMask,           XK_Return,   togglescratch,  {.ui = 0}},
	{MODKEY,                       XK_z,        incrgaps,       {.i = +3}},
	{MODKEY,                       XK_x,        incrgaps,       {.i = -3}},
	{MODKEY,                       XK_c,        spawn,          SHCMD("code")},
	{MODKEY,                       XK_b,        togglebar,      {0}},
	{MODKEY, 					   XK_grave, 	spawn, 			SHCMD("toggle-trayer")},
	{MODKEY,                       XK_n,        spawn_and_view, {.v = &obsidian_combined} },
	{MODKEY | ShiftMask,           XK_n,        spawn,          SHCMD("alacritty -e newsboat")},
	{MODKEY,                       XK_m,        spawn,          SHCMD("alacritty -e mpv --force-window --idle")},
	{MODKEY | ShiftMask,           XK_m,        spawn,          {.v = (const char *[]){TERMINAL, "-e", "ncmpcpp", NULL}}},
	{MODKEY,                       XK_comma,    spawn,          SHCMD("playerctl previous")},
	{MODKEY | ShiftMask,           XK_comma,    spawn,          SHCMD("mpc seek 0%")},
	{MODKEY,                       XK_period,   spawn,          SHCMD("playerctl next")},
	{MODKEY | ShiftMask,           XK_period,   spawn,          SHCMD("mpc repeat")},

	{MODKEY,                       XK_Left,     focusmon,       {.i = -1}},
	{MODKEY | ShiftMask,           XK_Left,     tagmon,         {.i = -1}},
	{MODKEY,                       XK_Right,    focusmon,       {.i = +1}},
	{MODKEY | ShiftMask,           XK_Right,    tagmon,         {.i = +1}},

	{MODKEY,                       XK_Page_Up,  shiftview,      {.i = -1}},
	{MODKEY | ShiftMask,           XK_Page_Up,  shifttag,       {.i = -1}},
	{MODKEY,                       XK_Page_Down,shiftview,      {.i = +1}},
	{MODKEY | ShiftMask,           XK_Page_Down,shifttag,       {.i = +1}},
	{MODKEY,                       XK_F1,       spawn,          SHCMD("dmenuhandler")},
	{MODKEY,                       XK_F3,       spawn,          SHCMD("displayselect")},
	{MODKEY,                       XK_F4,       spawn,          SHCMD(TERMINAL " -e pulsemixer; kill -44 $(pidof dwmblocks)")},
	{MODKEY,                       XK_F5,       xrdb,           {.v = NULL}},
	{MODKEY,                       XK_F8,       spawn,          SHCMD("rofibluetooth")},
	{MODKEY,                       XK_F9,       spawn,          SHCMD("mounter")},
	{MODKEY,                       XK_F10,      spawn,          SHCMD("unmounter")},
	{MODKEY,                       XK_F11,      spawn,          SHCMD("mpv --untimed --no-cache --no-osc --no-input-default-bindings --profile=low-latency --input-conf=/dev/null --geometry=+50%+50% --title=webcam $(ls /dev/video[0,2,4,6,8] | tail -n 1)")},
	{MODKEY,                       XK_space,    zoom,           {0}},
	{MODKEY | ShiftMask,           XK_space,    togglefloating, {0}},
	{ShiftMask,                    XK_Print,    spawn,          {.v = ocr_cmd}},
	{0,                            XK_Print,    spawn,          {.v = prtscrcmd}},
	{MODKEY,                       XK_Print,    spawn,          SHCMD("dmenurecord")},
	{MODKEY | ShiftMask,           XK_Print,    spawn,          SHCMD("dmenurecord kill")},
	{MODKEY,                       XK_Delete,   spawn,          SHCMD("dmenurecord kill")},
	{0,                            XF86XK_AudioMute, spawn,     SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)")},
	{0,                            XF86XK_AudioRaiseVolume, spawn, SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 0%- && wpctl set-volume @DEFAULT_AUDIO_SINK@ 3%+; kill -44 $(pidof dwmblocks)")},
	{0,                            XF86XK_AudioLowerVolume, spawn, SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 0%+ && wpctl set-volume @DEFAULT_AUDIO_SINK@ 3%-; kill -44 $(pidof dwmblocks)")},
	{0,                            XF86XK_AudioPrev, spawn,     SHCMD("mpc prev")},
	{0,                            XF86XK_AudioNext, spawn,     SHCMD("mpc next")},
	{0,                            XF86XK_AudioPause, spawn,    SHCMD("mpc pause")},
	{0,                            XF86XK_AudioPlay, spawn,     SHCMD("mpc play")},
	{0,                            XF86XK_AudioStop, spawn,     SHCMD("mpc stop")},
	{0,                            XF86XK_AudioRewind, spawn,   SHCMD("mpc seek -10")},
	{0,                            XF86XK_AudioForward, spawn,  SHCMD("mpc seek +10")},
	{0,                            XF86XK_AudioMedia, spawn,    SHCMD(TERMINAL " -e ncmpcpp")},
	{0,                            XF86XK_AudioMicMute, spawn,  SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle")},
	{0,                            XF86XK_PowerOff, spawn,      SHCMD("sysact")},
	{0,                            XF86XK_Bluetooth, spawn,     SHCMD("dmenubluetooth")},
	{0,                            XF86XK_Calculator, spawn,    SHCMD(TERMINAL " -e bc -l")},
	{0,                            XF86XK_Sleep, spawn,         SHCMD("sudo -A zzz")},
	{0,                            XF86XK_WWW, spawn,          SHCMD("$BROWSER")},
	{0,                            XF86XK_DOS, spawn,          SHCMD(TERMINAL)},
	{0,                            XF86XK_ScreenSaver, spawn,  SHCMD("slock & xset dpms force off; mpc pause; pauseallmpv")},
	{0,                            XF86XK_TaskPane, spawn,     SHCMD(TERMINAL " -e htop")},
	{0,                            XF86XK_Mail, spawn,         SHCMD(TERMINAL " -e neomutt ; pkill -RTMIN+12 dwmblocks")},
	{0,                            XF86XK_MyComputer, spawn,   SHCMD(TERMINAL " -e lfub /")},
	{0,                            XF86XK_Launch1, spawn,      SHCMD("xset dpms force off")},
	{0,                            XF86XK_TouchpadToggle, spawn, SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1")},
	{0,                            XF86XK_TouchpadOff, spawn,  SHCMD("synclient TouchpadOff=1")},
	{0,                            XF86XK_TouchpadOn, spawn,   SHCMD("synclient TouchpadOff=0")},
	{0,                            XF86XK_MonBrightnessUp, spawn, SHCMD("xbacklight -inc 15")},
	{0,                            XF86XK_MonBrightnessDown, spawn, SHCMD("xbacklight -dec 15")},
	{ShiftMask,                    XF86XK_MonBrightnessDown, spawn, SHCMD("xbacklight -set 1")},
	{ShiftMask,                    XF86XK_MonBrightnessUp, spawn, SHCMD("xbacklight -set 100")},
};

#ifndef Button9
#define Button9 9
#endif

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
#ifndef __OpenBSD__
	{ClkWinTitle,           0,              Button2,        zoom,           {0}},
	{ClkStatusText,         0,              Button1,        sigdwmblocks,   {.i = 1}},
	{ClkStatusText,         0,              Button2,        sigdwmblocks,   {.i = 2}},
	{ClkStatusText,         0,              Button3,        sigdwmblocks,   {.i = 3}},
	{ClkStatusText,         0,              Button4,        sigdwmblocks,   {.i = 4}},
	{ClkStatusText,         0,              Button5,        sigdwmblocks,   {.i = 5}},
	{ClkStatusText,         ShiftMask,      Button1,        sigdwmblocks,   {.i = 6}},
	{ClkStatusText,         ShiftMask,      Button2,        sigdwmblocks,   {.i = 7}},
#endif
	{ClkStatusText,         ShiftMask,      Button3,        spawn,          SHCMD("code ~/.local/src/dwmblocks/config.h")},
	{ClkClientWin,          MODKEY,         Button1,        movemouse,      {0}},
	{ClkClientWin,          MODKEY,         Button2,        defaultgaps,    {0}},
	{ClkClientWin,          MODKEY,         Button3,        resizemouse,    {0}},
	{ClkClientWin,          MODKEY,         Button4,        incrgaps,       {.i = +1}},
	{ClkClientWin,          MODKEY,         Button5,        incrgaps,       {.i = -1}},
	{ClkTagBar,             0,              Button1,        view,           {0}},
	{ClkTagBar,             0,              Button3,        toggleview,     {0}},
	{ClkTagBar,             MODKEY,         Button1,        tag,            {0}},
	{ClkTagBar,             MODKEY,         Button3,        toggletag,      {0}},
	{ClkTagBar,             0,              Button4,        shiftview,      {.i = -1}},
	{ClkTagBar,             0,              Button5,        shiftview,      {.i = 1}},
	{ClkRootWin,            0,              Button2,        togglebar,      {0}},
};
