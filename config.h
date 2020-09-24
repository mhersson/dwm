/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 20;       /* vert inner gap between windows */
static const unsigned int gappoh    = 15;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 15;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int attachmode         = 3;        /* 0 master (default), 1 = above, 2 = aside, 3 = below, 4 = bottom */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, 0: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#cc241d";
static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
    [SchemeSel]  = { col_gray4, col_gray1, col_cyan },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* class                            instance    title       tags mask     isfloating   monitor */
    { "feh",                            NULL,       NULL,       0,            1,           -1 },
    { "mpv",                            NULL,       NULL,       0,            1,           -1 },
    { "Blueberry.py",                   NULL,       NULL,       0,            1,           -1 },
    { "Zathura",                        NULL,       NULL,       0,            1,           -1 },
    { "Virt-manager",                   NULL,       NULL,       0,            1,           -1 },
    { "Spotify",                        NULL,       NULL,       1 << 8,       0,           -1 },
    { "Pavucontrol",                    NULL,       NULL,       0,            1,           -1 },
    { "Nm-connection-editor",           NULL,       NULL,       0,            1,           -1 },
    { "Microsoft Teams - Preview",      NULL,       NULL,       1 << 1,       0,           -1 },
    { "privateinternetaccess",          NULL,       NULL,       0,            1,            1 },
    { "firefox",                        NULL,       NULL,       0,            1,            1 },
    { "Brave-browser",                  NULL,       NULL,       0,            1,            1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "vanitygaps.h"

static const int layoutaxis[] = {
    SPLIT_VERTICAL,   /* layout axis: 1 = x, 2 = y; negative values mirror the layout, setting the master area to the right / bottom instead of left / top */
    TOP_TO_BOTTOM,    /* master axis: 1 = x (from left to right), 2 = y (from top to bottom), 3 = z (monocle) */
    TOP_TO_BOTTOM,    /* stack axis:  1 = x (from left to right), 2 = y (from top to bottom), 3 = z (monocle) */
};

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      flextile }, /* first entry is default */
    { "><>",      NULL },     /* no layout function means floating behavior */
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

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_gray2, "-sf", col_gray4, NULL };
static const char *roficmd[]  = { "rofi", "-show", "run", NULL };
static const char *copyclipboard[]  = { "/home/morten/Scripts/copyclipboard", NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "xterm", "-T", scratchpadname, "-g", "120x34", NULL };
static const char *xlockcmd[] = {"xlock", "-nolock", "-delay", "40000", "-mode", "fzort", NULL };

static const char *spotify_play[] = {"dbus-send", "--print-reply", "--dest=org.mpris.MediaPlayer2.spotify", "/org/mpris/MediaPlayer2", "org.mpris.MediaPlayer2.Player.PlayPause", NULL};
static const char *spotify_next[] = {"dbus-send", "--print-reply", "--dest=org.mpris.MediaPlayer2.spotify", "/org/mpris/MediaPlayer2", "org.mpris.MediaPlayer2.Player.Next", NULL};
static const char *spotify_prev[] = {"dbus-send", "--print-reply", "--dest=org.mpris.MediaPlayer2.spotify", "/org/mpris/MediaPlayer2", "org.mpris.MediaPlayer2.Player.Previous", NULL};

static const char *focus_left[] = {"focusnextwindow", "left", NULL};
static const char *focus_down[] = {"focusnextwindow", "down", NULL};
static const char *focus_up[] = {"focusnextwindow", "up", NULL};
static const char *focus_right[] = {"focusnextwindow", "right", NULL};

static const char *screenshot[] = {"/home/morten/Scripts/screenshot", NULL};

#include "movestack.c"
static Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY,                       XK_p,      spawn,          {.v = roficmd } },
    { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
    { MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
    { MODKEY,                       XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
    { MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
    { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.02} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.02} },
    { MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
    { MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
    { MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
    { MODKEY,                       XK_Return, zoom,           {0} },
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
    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY,                       XK_q,      killclient,     {0} },
    { MODKEY,                       XK_t,      setflexlayout,  {.i = 261 } }, // default tile
    { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_m,      setflexlayout,  {.i =   6 } }, // monocle
    { MODKEY|ControlMask,           XK_w,      setflexlayout,  {.i = 262 } }, // deck layout
    { MODKEY|ControlMask,           XK_e,      setflexlayout,  {.i = 272 } }, // bstack layout
    { MODKEY|ControlMask,           XK_r,      setflexlayout,  {.i = 273 } }, // bstackhoriz layout
    { MODKEY|ControlMask,           XK_f,      setflexlayout,  {.i =   7 } }, // grid
    { MODKEY|ControlMask,           XK_g,      setflexlayout,  {.i = 293 } }, // centered master
    { MODKEY,                       XK_space,  setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)
    { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
    { MODKEY|ControlMask,           XK_t,      rotatelayoutaxis, {.i = 0} },    /* flextile, 0 = layout axis */
    { MODKEY|ControlMask,           XK_Tab,    rotatelayoutaxis, {.i = 1} },    /* flextile, 1 = master axis */
    { MODKEY|ControlMask|ShiftMask, XK_Tab,    rotatelayoutaxis, {.i = 2} },    /* flextile, 2 = stack axis */
    { MODKEY|ControlMask,           XK_Return, mirrorlayout,     {0} },         /* flextile, flip master and stack areas */
    { Mod1Mask|ControlMask,         XK_Delete, spawn,          {.v = xlockcmd } },   /* start screensaver */
    /*
    { 0, 0x1008ff14, spawn, {.v = spotify_play} },
    { 0, 0x1008ff17, spawn, {.v = spotify_next} },
    { 0, 0x1008ff16, spawn, {.v = spotify_prev} },
    */
    { ControlMask,                  XK_F7,     spawn, {.v = spotify_play} },
    { ControlMask,                  XK_F8,     spawn, {.v = spotify_next} },
    { ControlMask,                  XK_F6,     spawn, {.v = spotify_prev} },

    { MODKEY,                       XK_Left,   spawn, {.v = focus_left} },
    { MODKEY,                       XK_Down,   spawn, {.v = focus_down} },
    { MODKEY,                       XK_Up,     spawn, {.v = focus_up} },
    { MODKEY,                       XK_Right,  spawn, {.v = focus_right} },

    { 0,                            XK_F12,    spawn, {.v = copyclipboard} },
    { MODKEY|ShiftMask,             XK_F11,    spawn, {.v = screenshot} },
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

