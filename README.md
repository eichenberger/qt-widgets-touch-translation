# Introduction
Qt Widgets can't handle Touch events properly. Therefore, we install an event filter which will translate touch events to mouse events. With this it is possible to emulate button clicks, etc. However, because the close button is handled differently close, maximize/minimize still don't work unfortunately.

This is only a proof of concept. Don't use it 1:1.
