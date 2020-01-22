#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

int main (void)
{
  Display *dpy;
  Window root, self;
  Colormap cmap;
  Visual *vis;
  XVisualInfo vi;
  XSetWindowAttributes xattrs;
  int screen, depth;
  unsigned long attribmask = 0;

  printf("Starting...\n");

  dpy = XOpenDisplay(NULL); // A connection to the X Window System server
  if (dpy == NULL) {
    fprintf(stderr, "error: Cannot connect to X Window System server\n");
    exit(1);
  }

  screen = DefaultScreen(dpy);

  depth = 24;
  if (XMatchVisualInfo(dpy, screen, depth, DirectColor, &vi)) {
    vis = vi.visual;
  } else {
    fprintf(stderr, "DirectColor Visual is not available\n");
    exit(1);
  }

  root   = DefaultRootWindow(dpy);
  cmap   = XCreateColormap(dpy, root, vis, AllocNone);

  xattrs.colormap = cmap;
  xattrs.event_mask = ExposureMask;
  xattrs.background_pixel = WhitePixel(dpy, screen);
  xattrs.override_redirect = True;

  attribmask = CWEventMask|CWColormap|CWBackPixel|CWOverrideRedirect;

  self = XCreateWindow(
      dpy, root,
      100, 100,
      256, 256,
      1,
      24,
      InputOutput,
      vis,
      attribmask,
      &xattrs);

  XMapWindow(dpy, self);
  XFlush(dpy);
  while(1);
  return 0;
}
