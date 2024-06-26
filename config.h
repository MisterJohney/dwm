/* See LICENSE file for copyright and license details. */

#define TERMINAL "st"
#define BROWSER "librewolf"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 5;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 5;       /* vert inner gap between windows */
static const unsigned int gappoh    = 5;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 5;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 5;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#4C392D";	/* Background color */
static const char col_gray2[]       = "#4E4D4C";	/* Inactive window border color */
static const char col_gray3[]       = "#AA9C66";	/* Font color */
static const char col_gray4[]       = "#F4DF92";	/* Current tag and current window font color */
static const char col_cyan[]        = "#D06824";	/* Top bar second color and active window border color */
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
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
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"


static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define SPAWN(...) { .v = (const char*[]){ __VA_ARGS__, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

#include "movestack.c"
#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                     key        function        argument */

	{ 0, XF86XK_AudioMute,			spawn,		SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,		spawn,		SHCMD("pamixer --allow-boost -i 3; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume,		spawn,		SHCMD("pamixer --allow-boost -d 3; kill -44 $(pidof dwmblocks)") },

	{ 0, XF86XK_MonBrightnessUp,		spawn,		{.v = (const char*[]){ "xbacklight", "-inc", "5", NULL } } },
	{ 0, XF86XK_MonBrightnessDown,		spawn,		{.v = (const char*[]){ "xbacklight", "-dec", "5", NULL } } },

		//Legacy code
	//{ 0,                            XK_F5,     spawn,          SHCMD("pamixer --allow-boost -d 3") },
	//{ 0,                            XK_F6,     spawn,          SHCMD("pamixer --allow-boost -i 3") },
	//{ 0,                            XK_F7,     spawn,          SHCMD("xbacklight -dec 5") },
	//{ 0,                            XK_F8,     spawn,          SHCMD("xbacklight -inc 5") },

	{ MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	//{ MODKEY|ShiftMask,             XK_q,      spawn,          {0} },
	{ MODKEY,			XK_w,	   spawn,	   SPAWN( BROWSER ) },
	//{ MODKEY|ShiftMask,             XK_w,      spawn,          {0} },
	{ MODKEY,		        XK_e,	   spawn,	   SHCMD( "emacsclient -c -a 'emacs'" ) },
	{ MODKEY|ShiftMask,		XK_e,	   spawn,	   SPAWN( TERMINAL, "-e", "gotop" ) },
	{ MODKEY,			XK_r,	   spawn,	   SPAWN( TERMINAL, "-e", "ranger" ) },
	{ MODKEY|ShiftMask,		XK_r,	   spawn,	   SHCMD("killall redshift || redshift &") },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[2]} },
	//{ MODKEY,                       XK_y,      spawn,          {0} },
	//{ MODKEY|ShiftMask,             XK_y,      spawn,          {0} },
	//{ MODKEY,                       XK_u,      spawn,          {0} },
	//{ MODKEY|ShiftMask,             XK_u,      spawn,          {0} },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = -1 } },
	//{ MODKEY|ShiftMask,             XK_i,      spawn,          {0} },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = +1 } },
	//{ MODKEY|ShiftMask,             XK_o,      spawn,          {0} },
	{ MODKEY,			XK_p,	   spawn,	   SHCMD( "thunar" ) },
	{ MODKEY|ShiftMask,		XK_p,	   spawn,	   SHCMD("killall picom || picom &") },

	//{ MODKEY,                       XK_a,      spawn,          {0} },
	//{ MODKEY|ShiftMask,             XK_a,      spawn,          {0} },
	//{ MODKEY,                       XK_s,      spawn,          {0} },
	//{ MODKEY|ShiftMask,             XK_s,      spawn,          {0} },
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,		XK_d,	   spawn,	   SPAWN( TERMINAL, "-e", "nvim", "-c", "VimwikiIndex" ) },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	//{ MODKEY,                       XK_g,      spawn,          {0} },
	//{ MODKEY|ShiftMask,             XK_g,      spawn,          {0} },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	//{ MODKEY|ShiftMask,             XK_h,      spawn,          {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	//{ MODKEY|ShiftMask,             XK_l,      spawn,          {0} },
	//{ MODKEY,                       XK_Semicol, spawn,          {0} },
	//{ MODKEY|ShiftMask,             XK_Semicol, spawn,          {0} },
	//{ MODKEY,                       XK_Backslash, spawn,          {0} },
	//{ MODKEY|ShiftMask,             XK_Backslash, spawn,          {0} },

	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },

	//{ MODKEY,                       XK_z,      spawn,          {0} },
	//{ MODKEY|ShiftMask,             XK_z,      spawn,          {0} },
	//{ MODKEY,                       XK_x,      spawn,          {0} },
	//{ MODKEY|ShiftMask,             XK_x,      spawn,          {0} },
	//{ MODKEY,                       XK_c,      spawn,          {0} },
	{ MODKEY|ShiftMask,             XK_c,      quit,           {0} },
	//{ MODKEY,                       XK_v,      spawn,          {0} },
	//{ MODKEY|ShiftMask,             XK_v,      spawn,          {0} },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
    	{ MODKEY|ShiftMask,             XK_b,      spawn,          SHCMD( "python3 ~/Downloads/ran/programming/python_projects/minecraft_miner/crafter.py" ) },   // Opens crafing script
	//{ MODKEY,                       XK_n,      spawn,          {0} },
	//{ MODKEY|ShiftMask,             XK_n,      spawn,          {0} },
	{ MODKEY,			XK_m,	   spawn,	   SPAWN( TERMINAL, "-e", "pulsemixer" ) },
	{ MODKEY|ShiftMask,		XK_m,	   spawn,	   SPAWN( TERMINAL, "-e", "cmus" ) },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },

	{ MODKEY|Mod1Mask,              XK_u,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_i,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_o,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_6,      incrihgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_7,      incrivgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_8,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_9,      incrovgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
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

