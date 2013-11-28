#ifndef IMAGE_HPP
# define IMAGE_HPP

# include <iostream>
# include <opencv2/core/core.hpp>
# include <opencv2/highgui/highgui.hpp>

# include <tools/Color.hpp>

namespace Display
{
  class Image
  {
  private:
    cv::Mat* image;

  public:
    ~Image();

  public:
    Image(cv::Mat* img);
    Image(std::vector<std::vector<Tools::RGBColor<float> > > img);

  public:
    void show(const std::string wname);
    //void update();
  };
}

#endif
