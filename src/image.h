#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <iostream>

#include "CImg.h"

class Image {

  public:
    Image(std::string file_path);
    ~Image();

    unsigned char* GetData();
    int GetSize();
    int GetHeight();
    int GetWidth();

  private:
    void Repack();

    cimg_library::CImg<unsigned char>* image_;
    unsigned char* data_;
    int height_;
    int width_;
};

inline unsigned char* Image::GetData() {
 return data_;
}

inline int Image::GetSize() {
  return height_ * width_ * 3;
}

inline int Image::GetHeight() {
  return height_;
}

inline int Image::GetWidth() {
  return width_;
}

#endif /* IMAGE_H */
