/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[] = {"CaskaydiaCoveMonoNerdFont-Bold:size=10:style:Bold"};
static const char dmenufont[] = "CaskaydiaMonoNerdFont-Bold:size=10.6";
static const char normbgcolor[]           = "#222222";
static const char normbordercolor[]       = "#444444";
static const char normfgcolor[]           = "#bbbbbb";
static const char selfgcolor[]            = "#eeeeee";
static const char selbordercolor[]        = "#005577";
static const char selbgcolor[]            = "#005577";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { "#888888", "#1a1a1a", "#333333" }, // Darker gray tones
    [SchemeSel]  = { "#cccccc", "#000000", "#888888" }, // Black background, soft selection border
};
static const unsigned int alphas[][3]      = {
    /*               fg      bg        border*/
    [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class         instance    title       tags mask     isfloating   monitor */
	{ "Gimp",        NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",     NULL,       NULL,       1 << 8,       0,           -1 },
	{ "pavucontrol", NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int attachbelow = 1;    /* 1 means attach after the currently active window */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ 0, MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ 0, MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ 0, MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ 0, MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
// static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *dmenucmd[] = { "ulauncher-toggle", NULL };
static const char *termcmd[] = { "sh", "-c", "/home/espacio/dwm/scripts/launch_kitty.sh", NULL };
static const char *restartcmd[] = { "sh", "-c", "/home/espacio/dwm/scripts/restart.sh", NULL };
static const char *lockcmd[] = { "betterlockscreen", "-l", NULL };
static const char *switchcmd[] = { "sh", "-c", "/home/espacio/dwm/scripts/wacom_toggle.sh", NULL };
static const char *up_vol[]   = { "amixer", "-D", "default", "set", "Master", "5%+", "unmute", NULL };
static const char *down_vol[] = { "amixer", "-D", "default", "set", "Master", "5%-", "unmute", NULL };
static const char *mute_vol[] = { "amixer", "-D", "default", "set", "Master", "toggle", NULL };
static const char *medplaypausecmd[] = { "playerctl", "play-pause", NULL };
static const char *mednextcmd[] = { "playerctl", "next", NULL };
static const char *medprevcmd[] = { "playerctl", "previous", NULL };
static const char *screenshotcmd[] = { "flameshot", "gui", NULL };
static const char *browsercmd[] = { "brave", NULL };

static const char *solver_screenshotcmd[] = { "python3", "/home/espacio/projects/orion/screenshot.py", NULL };
static const char *solver_solvecmd[] = { "python3", "/home/espacio/projects/orion/solver.py", NULL };

static const char *suspendcmd[] = { "systemctl", "suspend", NULL };

#define MULTIKEY_THRESHOLD_MS_PRESS 200
#define MULTIKEY_THRESHOLD_MS_HOLD 700

static Key keys[] = {
	/* npresses,   modifier                     key                      function        argument */

	/* Multikey media controls */
	{ 0,           MODKEY|ShiftMask,             XK_n,                    spawn,          {.v = mednextcmd} },
	{ 0,           MODKEY|ShiftMask,             XK_p,                    spawn,          {.v = medprevcmd} },
	{ 0,           MODKEY|ShiftMask,             XK_space,                spawn,          {.v = medplaypausecmd} },

	{ 0,           0,                            XF86XK_AudioMute,        spawn,          {.v = mute_vol } },
	{ 0,           0,                            XF86XK_AudioLowerVolume, spawn,          {.v = down_vol } },
	{ 0,           0,                            XF86XK_AudioRaiseVolume, spawn,          {.v = up_vol } },
	{ 0,           0,                            XF86XK_AudioPlay,        spawn,          {.v = medplaypausecmd } },
	{ 0,           0,                            XF86XK_AudioNext,        spawn,          {.v = mednextcmd } },
	{ 0,           0,                            XF86XK_AudioPrev,        spawn,          {.v = medprevcmd } },

	{ 0,           MODKEY,                       XK_q,                    spawn,          {.v = mute_vol} },
	{ 0,           MODKEY,                       XK_w,                    spawn,          {.v = down_vol} },
	{ 0,           MODKEY,                       XK_e,                    spawn,          {.v = up_vol} },

    /* Terminal Commands */
	{ 0,           MODKEY,                       XK_p,                    spawn,          {.v = dmenucmd } },
	{ 0,           MODKEY,                       XK_Return,               spawn,          {.v = termcmd } },
	{ 0,           MODKEY|ShiftMask,             XK_l,                    spawn,          {.v = lockcmd } },
	{ 0,           MODKEY|ShiftMask,             XK_r,                    spawn,          {.v = restartcmd } },
	{ 0,           MODKEY,                       XK_s,                    spawn,          {.v = switchcmd } },
	{ 0,           MODKEY|ShiftMask,             XK_s,                    spawn,          {.v = screenshotcmd } },
	{ 0,           MODKEY,                       XK_b,                    spawn,          {.v = browsercmd } },

    /* Misc */
	{ 0,           MODKEY,                       XK_f,                    fullscreen,     {0} },
	{ 0,           MODKEY,                       XK_b,                    togglebar,      {0} },
	{ 0,           MODKEY,                       XK_j,                    focusstack,     {.i = +1 } },
	{ 0,           MODKEY,                       XK_k,                    focusstack,     {.i = -1 } },
	{ 0,           MODKEY,                       XK_i,                    incnmaster,     {.i = +1 } },
	{ 0,           MODKEY,                       XK_d,                    incnmaster,     {.i = -1 } },
	{ 0,           MODKEY,                       XK_h,                    setmfact,       {.f = -0.05} },
	{ 0,           MODKEY,                       XK_l,                    setmfact,       {.f = +0.05} },
	{ 0,           MODKEY,                       XK_Tab,                  view,           {0} },
	{ 0,           MODKEY,                       XK_c,                    killclient,     {0} },
	{ 0,           MODKEY,                       XK_space,                setlayout,      {0} },
	{ 0,           MODKEY|ShiftMask,             XK_space,                togglefloating, {0} },
	{ 0,           MODKEY,                       XK_0,                    view,           {.ui = ~0 } },
	{ 0,           MODKEY|ShiftMask,             XK_0,                    tag,            {.ui = ~0 } },
	{ 0,           MODKEY,                       XK_comma,                focusmon,       {.i = -1 } },
	{ 0,           MODKEY,                       XK_period,               focusmon,       {.i = +1 } },
	{ 0,           MODKEY|ShiftMask,             XK_comma,                tagmon,         {.i = -1 } },
	{ 0,           MODKEY|ShiftMask,             XK_period,               tagmon,         {.i = +1 } },
	{ 0,           MODKEY|ShiftMask,             XK_q,                    quit,           {0} },
    { 0,           0,                            XK_F12,                  spawn,          {.v = suspendcmd} },

	// { 0,           MODKEY,                       XK_x,                    spawn,          {.v = solver_screenshotcmd } },
	// { 0,           MODKEY,                       XK_z,                    spawn,          {.v = solver_solvecmd } },
	
	TAGKEYS(                                     XK_1,                                    0)
	TAGKEYS(                                     XK_2,                                    1)
	TAGKEYS(                                     XK_3,                                    2)
	TAGKEYS(                                     XK_4,                                    3)
	TAGKEYS(                                     XK_5,                                    4)
	TAGKEYS(                                     XK_6,                                    5)
	TAGKEYS(                                     XK_7,                                    6)
	TAGKEYS(                                     XK_8,                                    7)
	TAGKEYS(                                     XK_9,                                    8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

