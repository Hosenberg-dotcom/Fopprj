#include "headers.h"

MessageWindow* init_message_window(int width,int height, int y) {
    MessageWindow* msg_win = malloc(sizeof(MessageWindow));
    msg_win->screen_height = height;
    msg_win->width = width;
    msg_win->type = y;
    if(y == 0)
        msg_win->win = newwin(3, width, 0, 0);  // ارتفاع ۳، عرض `width`، مکان `(0,0)`
    else
        msg_win->win = newwin(3, width, height - 3, 0);
    wattron(msg_win->win, COLOR_PAIR(1));
    box(msg_win->win, 0, 0);
    wattroff(msg_win->win, COLOR_PAIR(1));
    wrefresh(msg_win->win);
    return msg_win;
}

void print_message(MessageWindow* msg_win, const char* msg) {
    werase(msg_win->win);  // پاک کردن پنجره
    wattron(msg_win->win, COLOR_PAIR(1));
    box(msg_win->win, 0, 0);  // کشیدن کادر دور `window`
    wattroff(msg_win->win, COLOR_PAIR(1));
    if (msg && strlen(msg) > 0) {  
        mvwprintw(msg_win->win, 1, msg_win->width / 2, "%s", msg);  // نمایش پیام در `window`
    }

    wrefresh(msg_win->win);  // به‌روزرسانی `window`
}

void destroy_message_window(MessageWindow* msg_win) {
    delwin(msg_win->win);
    free(msg_win);
}