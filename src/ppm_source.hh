#include <string>

#include "viewer-types.hh"

class PpmSource : public ImageSource
{
private:
    class PpmFrame : public Frame {
        PpmFrame(int width, int height) : len(width*height*3) { data = new uint8_t(len); }
        ~PpmFrame{ /*empty, the source deletes the image*/};
    Frame f_;
    std::string name_;
public:
    PpmSource(std::string filename) : name_{filename} {

        std::ifstream inputStream(filename.c_str(), std::ios::binary);
        
        if (false == inputStream.good()) {
            throw std::runtime_error("Failed to open \"" + filename + "\"\n");
        }

        std::string header;
        inputStream >> header;

        if (header == P6)
        {
            int width, height, scale;
            inputStream >> width >> height >> scale;
            f_ = new PpmFrame(width, height);
            f_->fmt = format::rgb8;

            for (int x=0; x<width; ++x)
            {
                for (int y=0; y<height; ++y)
                {
                    inputStream >> f_->data[y*width + x + 0];
                    inputStream >> f_->data[y*width + x + 1];
                    inputStream >> f_->data[y*width + x + 2];
                }
            }
        }
        else
        {
            std::cerr << "Unsupported header \"" << header << "\"\n";
        }

        glGenTextures(1,&f_->tex);
        glBindTexture(f_->tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, f_->width, f_->height, 0, GL_RGB, GL_UNSIGNED_BYTE, f_->data);
        glBindTexture(0);
    }

    ~PpmSource {
        delete[] f_->data;
    };

    std::unique_ptr<Frame> next() {
        return std::unique_ptr 
    };
};
