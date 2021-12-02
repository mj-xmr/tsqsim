#ifndef FRAMEITER_H
#define FRAMEITER_H

class MyMainWindow;
class FrameIter
{
    public:
        FrameIter();
        virtual ~FrameIter();

        void OnFrame(MyMainWindow * win) const;
        void OnFrameReact(MyMainWindow * win, int i) const;

    protected:

    private:
};

#endif // FRAMEITER_H
