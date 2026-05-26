#pragma once

// ── Window / Frame ──────────────────────────────────────────────
#define IDC_SIDEBAR_WIDTH       220
#define IDC_NAVBAR_HEIGHT        48
#define IDC_PANEL_PAD            12

// ── Sidebar menu items ───────────────────────────────────────────
#define IDC_MENU_DASHBOARD      2001
#define IDC_MENU_UIELEMENTS     2002
#define IDC_MENU_FORMS          2003
#define IDC_MENU_TABLES         2004
#define IDC_MENU_CHARTS         2005

// ── Navbar controls ──────────────────────────────────────────────
#define IDC_NAVBAR_SEARCH       2010
#define IDC_NAVBAR_NOTIF        2011
#define IDC_NAVBAR_USER         2012
#define IDC_MENU_TOGGLE         2013

// ── Refresh / Timer ──────────────────────────────────────────────
#define IDC_REFRESH_BTN         2020
#define IDT_REFRESH_TIMER       2021

// ── Observer event types (passed in OnUpdate) ────────────────────
#define EVT_STATS_CHANGED       3001   // stat cards updated
#define EVT_CHART_CHANGED       3002   // chart data updated
#define EVT_CHAT_CHANGED        3003   // new message
#define EVT_TABLE_CHANGED       3004   // table rows updated
