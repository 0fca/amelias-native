/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mouse.c
 * Author: obsidiam
 *
 * Created on December 31, 2017, 1:52 PM
 */

#include <string.h>
#include <unistd.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>
#include <sys/select.h>
#include <stdio.h>
#include <string.h>
#include <X11/keysymdef.h>

int coords[2] = {0,0};
unsigned char hasMoved = 0;
/*
 * 
 */

Display *display;

unsigned char doMouseClick(int button, int x, int y){       
    display = XOpenDisplay(NULL);
    XEvent event;
    Window root = RootWindow(display, DefaultScreen(display));

    if(display == NULL)
    {
            fprintf(stderr, "Default display is not accessible!!!\n");
            return 0;
    }
    memset(&event, 0x00, sizeof(event));
    event.type = ButtonPress;
    event.xbutton.button = button;
    event.xbutton.same_screen = True;

    XWarpPointer(display, None, root,0, 0, 0, 0, x, y);
    XQueryPointer(display, root, &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);

    event.xbutton.subwindow = event.xbutton.window;

    while(event.xbutton.subwindow)
    {
            event.xbutton.window = event.xbutton.subwindow;

            XQueryPointer(display, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
    }

    if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) {
        printf("Error occurred while trying to send an event!!!\n"); return 0;
    }

    XFlush(display);

    event.type = ButtonRelease;
    event.xbutton.state = 0x100;

    if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) {
        printf("Error occurred while trying to send an event!!!\n"); return 0;
    }
    XFlush(display);
    XCloseDisplay(display);
    return 1;
}


JNIEXPORT jboolean JNICALL Java_ameliaclient_nativesupport_NativeMouseController_hasMouseMoved(JNIEnv *env, jobject jobj){
    return hasMoved;
}

JNIEXPORT void JNICALL Java_ameliaclient_nativesupport_NativeMouseController_sendCoords(JNIEnv *env, jobject jobj, jint x, jint y){
    hasMoved = (unsigned char)(coords[0] != x || coords[1] != y);
    coords[0] = (int)x;
    coords[1] = (int)y;
}

JNIEXPORT jboolean JNICALL Java_ameliaclient_nativesupport_NativeMouseController_nativeMouseClick(JNIEnv *env, jobject jobj, jint button) {

    unsigned char result = 0;
    
    if(button > 0 && button < 4){
        result = doMouseClick(button, coords[0], coords[1]);
    }else{
        fprintf(stderr, "No button like %i",button);
    }
    return result;
}



