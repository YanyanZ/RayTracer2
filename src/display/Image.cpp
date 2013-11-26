# include <display/Image.hpp>

Display::Image::~Image()
{
  if (image)
  {
    delete image;
    BOOST_LOG_TRIVIAL(info) << "[Display] Image destroy";
  }
  BOOST_LOG_TRIVIAL(info) << "[Display] Image not destroy";
}

Display::Image::Image(cv::Mat* img) : image (img)
{
  BOOST_LOG_TRIVIAL(info) << "[Display] Init class";
}

Display::Image::Image(std::vector<std::vector<Tools::RGBColor<int> > > img)
{
  if (img.size() == 0)
    BOOST_LOG_TRIVIAL(fatal) << "[Display] Bad argument in constructor";

  image = new cv::Mat M(img.size() ,img[0].size() , CV_8UC3, Scalar(0,0,0));

  for (int i = 0; i < img.size(); i++)
    for (int j = 0; j < img[i].size(); i++)
    {
      image.at<Vec3b>(j, i)[0] = image[i][j].r;
      image.at<Vec3b>(j, i)[1] = image[i][j].b;
      image.at<Vec3b>(j, i)[2] = image[i][j].g;
    }

  BOOST_LOG_TRIVIAL(info) << "[Display] Image construction done";
}

void Diplay::Image::show(const std::string wname)
{
  BOOST_LOG_TRIVIAL(info) << "[Display] Show image";

  cv::namedWindow(wname.c_str(), CV_WINDOW_AUTOSIZE);
  cv::imshow(wname.c_str(), image);

  cv::waitKey(0);
}
