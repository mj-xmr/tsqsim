#ifndef EVENTHANDLERMOUSE_H
#define EVENTHANDLERMOUSE_H

class MyMainWindow;
class QMouseEvent;
class EventHandlerMouse
{
    public:
        EventHandlerMouse();
        virtual ~EventHandlerMouse();

        void mouseMove(MyMainWindow * win, QMouseEvent *event) const;
        void mousePress(MyMainWindow * win, QMouseEvent *event) const;
        void mouseRelease(MyMainWindow * win, QMouseEvent *event) const;
    protected:
    private:
};

#endif // EVENTHANDLERMOUSE_H
