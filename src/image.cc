#include "image.h"

Image::Image(std::string file_path) : height_(0),  width_(0) {
  image_ = new cimg_library::CImg<unsigned char>(file_path.c_str());
  image_->mirror('y');
  height_ =  image_->height();
  width_ =  image_->width();

  data_ = new unsigned char[height_ * width_ * 3];
  Repack();
}

Image::~Image() {
  delete data_;
}

void Image::Repack() {
  int k = 0;
  unsigned char* temp_data = new unsigned char[height_*width_*3];

  for (int i = 0; i < height_*width_*3; i += 3) {
    data_[i] = image_->operator()(k,0,0,0);
    data_[i+1] = image_->operator()(k,0,0,1);
    data_[i+2] = image_->operator()(k,0,0,2);
    ++k;
  }

  delete temp_data;
}
