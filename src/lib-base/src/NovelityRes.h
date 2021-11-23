#ifndef NOVELITYRES_H
#define NOVELITYRES_H

namespace boost
{
    namespace serialization
    {
        class access;
    }
}

struct NovelityRes
{
    bool status = false;
    bool isNovel = false;
    float distToDecFun = 0;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & status;
        ar & isNovel;
        ar & distToDecFun;
    }
};

#endif // NOVELITYRES_H
