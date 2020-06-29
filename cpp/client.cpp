#include <iostream>
#include <functional> // bind
#include <array>
#include <vector>
#include <algorithm>//merge

#define ASIO_STANDALONE
#include <asio.hpp>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using asio::ip::udp;

template<typename T, int N>
void print_array(std::array<T,N> in){
  for(auto e: in)
    std::cout<<e<<" ";
  std::cout<<"\n";
}

template<typename T, int N, int M>
auto concat(const std::array<T, N>& ar1, const std::array<T, M>& ar2)
{
    std::array<T, N+M> result;
    std::copy (ar1.cbegin(), ar1.cend(), result.begin());
    std::copy (ar2.cbegin(), ar2.cend(), result.begin() + N);
    return result;
}

int main(){

  int frame_idx=0;

  //constexpr int buf_size = 2^16;
  constexpr int MAX_DGRAM= 2<<16;

  try
  {
    asio::io_context io_context;

    udp::socket socket(io_context, udp::endpoint(udp::v4(), 12345));


    std::vector<char> recv_output;

    for (;;)
    {
      //std::array<char, MAX_DGRAM> recv_buf;
      std::vector<char> recv_buf(MAX_DGRAM);
      udp::endpoint remote_endpoint;
      size_t ret = socket.receive_from(asio::buffer(recv_buf), remote_endpoint);

      int idx = (int)recv_buf.at(0);
      size_t size=0;
       
      //std::cout<<(int)recv_buf.at(0)<<std::endl;
      std::cout<<"==="<<frame_idx++<< "==="<<ret<<"==="<<std::endl;

      // concat
      if(idx > 1){
      recv_output.insert( recv_output.end(),recv_buf.begin()+1, recv_buf.begin() + ret );

      // concat + display
      }else{
      recv_output.insert( recv_output.end(),recv_buf.begin()+1, recv_buf.begin() + ret );
      std::cout<<"Concat : "<<recv_output.size()<<std::endl;

      /*  Convert to Opencv Mat */

      /*
      CV_LOAD_IMAGE_ANYDEPTH - If set, return 16-bit/32-bit image when the input has the corresponding depth, otherwise convert it to 8-bit.
      CV_LOAD_IMAGE_COLOR - If set, always convert image to the color one
      CV_LOAD_IMAGE_GRAYSCALE - If set, always convert image to the grayscale one
      >0 Return a 3-channel color image.
      Note In the current implementation the alpha channel, if any, is stripped from the output image. Use negative value if you need the alpha channel.
      =0 Return a grayscale image.
    <0 Return the loaded image as is (with alpha channel).
       */
      cv::Mat image = cv::imdecode(recv_output,-1 );
      std::cout<<image.size()<<std::endl;

      /* Display */
      if(!image.empty())
        cv::imshow( "display", image );
      else
        std::cout<<"image empty"<<std::endl;

      int k = cv::waitKey(5);
      if(k == 27)
      {
        cv::destroyAllWindows();
        break;
      }

      //reset output array
      recv_output.clear();
      //std::cout<<"Clear : "<<recv_output.size()<<std::endl;
      }

      


      //asio::error_code ignored_error;
      //socket.send_to(asio::buffer(message),
      //    remote_endpoint, 0, ignored_error);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}


