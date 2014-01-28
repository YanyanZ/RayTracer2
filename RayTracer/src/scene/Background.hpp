#ifndef BACKGROUND_HPP
# define BACKGROUND_HPP

# include <iostream>
# include <vector>

namespace Engine
{
  class Background
  {
  private:
    std::vector<double> color;

  public:
    Background (std::vector<double> c);
    ~Background(void);

  public:
    void getBackground(std::vector<double> c);
  };
}

#endif
