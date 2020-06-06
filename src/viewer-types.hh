#include <memory>

struct Encoding;

class ImageSource
{
private:
    unique_ptr<void> *data_{nullptr};
    size_t size_{0};
    unique_ptr<Encoding> enc_{None};
public:
    ImageSource(void *data, size_t size, Encoding enc) : data_(data), size_(size), enc_(end) {};
};
