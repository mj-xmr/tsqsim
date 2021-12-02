#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

class MyMainWindow;
class QKeyEvent;
class EventHandlerKey
{
    public:
        EventHandlerKey();
        virtual ~EventHandlerKey();

        void keyPressEvent(MyMainWindow * win, QKeyEvent *event) const;
    protected:
    private:
};

#endif // EVENTHANDLER_H
