#ifndef __VIEWER_TYPES_HH__
#define __VIEWER_TYPES_HH__

#include <memory>

enum class format {rgba8, rgb8};

struct Frame
{
    int tex;
    int width;
    int height;
    void *data;
    int len;
    format fmt;
    virtual ~Frame=0;
};


class ImageSource
{
private:
    unique_ptr<void> *data_{nullptr};
    int tex_{-1}; // texture representation
    size_t size_{0};
public:
    ImageSource(void *data, size_t size, Encoding enc) : data_(data), size_(size){};
    unique_ptr<Frame> next()=0;
    std::string name()=0;
};

#endif
