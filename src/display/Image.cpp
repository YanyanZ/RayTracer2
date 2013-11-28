# include <display/Image.hpp>

Display::Image::~Image()
{
  if (image)
  {
    delete image;
  }
}

Display::Image::Image(cv::Mat* img) : image (img)
{
}

Display::Image::Image(std::vector<std::vector<Tools::RGBColor<float> > > img)
{
  image = new cv::Mat(img.size(), img[0].size() , CV_8UC3, cv::Scalar(0,0,0));

  for (unsigned int i = 0; i < img.size(); i++)
    for (unsigned int j = 0; j < img[i].size();j++)
    {
      image->at<cv::Vec3b>(j, i)[0] = static_cast<int>(img[i][j].r);
      image->at<cv::Vec3b>(j, i)[1] = static_cast<int>(img[i][j].b);
      image->at<cv::Vec3b>(j, i)[2] = static_cast<int>(img[i][j].g);
    }
}

void Display::Image::show(const std::string wname)
{
  cv::namedWindow(wname.c_str(), CV_WINDOW_AUTOSIZE);
  cv::imshow(wname.c_str(), *image);

  cv::waitKey(0);
}
