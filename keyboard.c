/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: obsidiam
 *
 * Created on September 30, 2017, 11:42 AM
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


Display *display;
unsigned char wasPressed = 0;

Window GetWindowUnderCursor(Window focused_wnd, Window parent, Window *children, int nums, int bar, XWindowAttributes *xwa, Window root){
    XQueryPointer(display, root, &focused_wnd, &parent, &bar, &bar, &bar, &bar, &bar);
    
    XQueryTree(display, parent, &focused_wnd, &focused_wnd, &children, &nums);
    
    while( --nums >= 0 ){
        XGetWindowAttributes(display, children[nums], xwa);
        
        if( (xwa->width * xwa->height) > bar) {
            focused_wnd = children[nums];
            bar = xwa->width * xwa->height;
            break;
        }
        nums--;
    }
    return focused_wnd;
}

unsigned char IsFocusedUnderCursor(Window *focused_wnd,Window *potentially_under){
    return (unsigned char)(*focused_wnd == *potentially_under);   
}

Status KeyPressSynth(const char keycode, int state){
    XKeyEvent event;                     
    Window current_focus_window;   
    char key_str[] = "";
    key_str[0] = keycode;
    KeySym key = XStringToKeysym(key_str);
    KeySym key2 = XkbKeycodeToKeysym(display, XKeysymToKeycode(display,key), 0, 1<<state & ShiftMask ? 1 : 0);

    int return_focus_state;
    XGetInputFocus(display, &current_focus_window, &return_focus_state);
    memset(&event,0, sizeof(event));
    event.type = KeyPress;
    event.display = display;
    event.window = current_focus_window;
    event.root = DefaultRootWindow( display);
    event.subwindow = None;
    event.time = 1000;
    event.x = 0;
    event.y = 0;
    event.x_root = 0;
    event.y_root = 0;
    event.state = 1<<state;   
    event.keycode = XKeysymToKeycode(display,  key2);
    event.same_screen = True;
    XSendEvent(display, InputFocus,True,KeyPressMask,(XEvent *)(&event));
       
    memset(&event,0, sizeof(event));
    event.type = KeyRelease;   
    event.time = 1000;
       
    return XSendEvent(display, InputFocus,True,KeyReleaseMask,(XEvent *)(&event));
}

unsigned char doKeyPress(const char* keycode,int modifier_name){
    display = XOpenDisplay(NULL);
    KeyPressSynth((char)(*keycode),modifier_name);
    XFlush(display);
    XCloseDisplay(display);
    return 1;
}

unsigned char typeSequence(const char *sequence, int modifier_name){
    display = XOpenDisplay(NULL);
    
    for(int i = 0; sequence[i] != '\0'; i++) {
        //printf("%c",sequence[i]);
        if(KeyPressSynth(sequence[i],modifier_name)){
            XFlush(display);
        }else{
            return 0;
        }
    }

    XFlush(display);
    XCloseDisplay(display);
    return 1;
}

const char* convertFromJavaStringToString(JNIEnv *env,jstring javaString){
    return (*env)->GetStringUTFChars(env, javaString, 0);
}

char* GetKeyboardLayout(){
    display = XOpenDisplay(NULL);

    XkbDescRec* _kbdDescPtr = XkbAllocKeyboard();
    XkbGetNames(display, XkbSymbolsNameMask, _kbdDescPtr);
    Atom symName = _kbdDescPtr -> names -> symbols;
    char* layoutString = XGetAtomName(display, symName);
    return (layoutString);
}

JNIEXPORT char* JNICALL Java_ameliaclient_nativesupport_NativeKeyboardController_getKeyboardLayout(JNIEnv *env, jobject jobj){
    return GetKeyboardLayout();
}

JNIEXPORT unsigned char JNICALL Java_ameliaclient_nativesupport_NativeKeyboardController_nativeKeyPress(JNIEnv *env, jobject jobj, jstring keycode,jint modifier){
    const char *seq = convertFromJavaStringToString(env,keycode);
    int modifier_i = (int)modifier;
    unsigned char result = doKeyPress(seq,modifier_i);
    (*env)->ReleaseStringUTFChars(env, keycode, seq);
    return result;
}

JNIEXPORT unsigned char JNICALL Java_ameliaclient_nativesupport_NativeKeyboardController_nativeTypeSequence(JNIEnv *env, jobject jobj, jstring keycode,jint modifier){
    const char *seq = convertFromJavaStringToString(env,keycode);
    int modifier_i = (int)modifier;
    unsigned char result = typeSequence(seq,modifier_i);
    (*env)->ReleaseStringUTFChars(env, keycode, seq);
    return result;
}
JNIEXPORT jboolean JNICALL Java_ameliaclient_nativesupport_NativeKeyboardController_nativeAnyKeyPressed(JNIEnv *env, jobject jobj){
    if(display == NULL){
        display = XOpenDisplay(NULL);
        //Window root = RootWindow(display, DefaultScreen(display));
        int ret = XGrabKey(display, AnyKey, AnyModifier, PointerWindow, 0, GrabModeAsync, GrabModeAsync);
        printf("Was pressed %i",ret);
        return (unsigned char)ret;
    }
}






