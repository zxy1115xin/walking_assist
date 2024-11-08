//
// Created by lyy on 22/8/3.
//

#include <iostream>
#include <sstream>
#include <time.h>

#include "ros/ros.h"
#include "ros/time.h"
#include <std_msgs/Float64.h>

#include <boost/program_options.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/random.hpp>
#include <boost/asio.hpp>
#pragma warning( push )
#pragma warning( pop )
#pragma warning( disable : 4242 )

int main( int argc, char *argv[] )
{
  // 初始化节点
  ros::init(argc, argv, "remote_start_stop");
  ros::NodeHandle n;
  ros::Publisher trigger_pub = n.advertise<std_msgs::Float64>("trigger", 1000);

  
  std::string CaptureName;
  std::string CaptureNotes;
  std::string CaptureDescription;
  std::string CaptureDatabasePath;
  std::string Timecode;
  unsigned int CaptureDelayInMilliseconds = 0;
  unsigned short Port = 30;

  // 利用roslaunch传递参数
  n.getParam("name", CaptureName);
  n.getParam("path", CaptureDatabasePath);

  // ************** //
  // Start capture. //
  // ************** //
  bool flag = true;
  // Seed the random number with the time.
  boost::rand48 Random( 100000 );
  Random.seed( static_cast< boost::rand48::result_type >( time(0) ) );
  // The packet ID is selected randomly.
  // Packets with duplicate ID's are ignored by Nexus.
  const unsigned int CaptureID_start = Random();
  //.Set up ASIO for UDP broadcast.
  boost::asio::io_service Service_start;
  // Create and open socket.
  boost::asio::ip::udp::socket Socket_start( Service_start );
  boost::system::error_code Error_start;
  Socket_start.open( boost::asio::ip::udp::v4(), Error_start );
  if( !Error_start )
  {
    // Successfully opened the socket.
    // Set to broadcast.
    Socket_start.set_option( boost::asio::ip::udp::socket::reuse_address(true) );
    Socket_start.set_option( boost::asio::socket_base::broadcast(true) );
    boost::asio::ip::address ip_address = boost::asio::ip::address::from_string("192.168.10.1",Error_start); // printf("%s:%d\n",__FILE__,__LINE__);
    boost::asio::ip::udp::endpoint SenderEndpoint_start( ip_address, Port );
    // Build up XML contents of the broadcast message.
    std::ostringstream Stream;
    if( flag )
    {
      Stream << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << std::endl;
      Stream << "<CaptureStart>" << std::endl;
      Stream << "<Name VALUE=\"" << CaptureName << "\"/>" << std::endl;
      if( !CaptureNotes.empty() )
        Stream << "  <Notes VALUE=\"" << CaptureNotes << "\"/>" << std::endl;
      if( !CaptureDescription.empty() )
        Stream << "  <Description VALUE=\"" << CaptureDescription << "\"/>" << std::endl;
      if( !Timecode.empty() )
        Stream << "  <TimeCode VALUE=\"" << Timecode << "\"/>" << std::endl;
      Stream << "  <DatabasePath VALUE=\"" << CaptureDatabasePath << "\"/>" << std::endl;
      Stream << "  <Delay VALUE=\"" << CaptureDelayInMilliseconds << "\"/>" << std::endl;
      Stream << "  <PacketID VALUE=\"" << CaptureID_start << "\"/>" << std::endl;
      Stream << "</CaptureStart>" << std::endl;
    }
    std::string String_start( Stream.str() );
    // Send message.
    // Buffer must contain terminating 0.
    Socket_start.send_to( boost::asio::buffer( String_start.c_str(), String_start.size() + 1 ), SenderEndpoint_start );
    Socket_start.close( Error_start );

    // Print 数据包xml
    std::cout << String_start << std::endl;
  }

  // 打印当前时间戳，由bag中/clock获取，为仿真时间
  ros::Time time_now = ros::Time::now();

  std::cout << "trigger start xml message has been sent successfully!" << ", " << time_now << std::endl;

  ros::Rate loop_rate(100);
  std_msgs::Float64 time_now_;
  time_now_.data=time_now.toSec();
  int count = 0;
  while (ros::ok())
  {
      if(count <1){
          trigger_pub.publish(time_now_);
      }
      time_now = ros::Time::now();
      time_now_.data=time_now.toSec();
      trigger_pub.publish(time_now_);

    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }



  // 等待Ctrl+C跳出循环
  // ************* //
  // Stop capture. //
  // ************* //
  flag = false;
  // Seed the random number with the time.
  Random.seed( static_cast< boost::rand48::result_type >( time(0) ) );
  // The packet ID is selected randomly.
  // Packets with duplicate ID's are ignored by Nexus.
  const unsigned int CaptureID_stop = Random();
  //.Set up ASIO for UDP broadcast.
  boost::asio::io_service Service_stop;
  // Create and open socket.
  boost::asio::ip::udp::socket Socket_stop( Service_stop );
  boost::system::error_code Error_stop;
  Socket_stop.open( boost::asio::ip::udp::v4(), Error_stop );
  if( !Error_stop )
  {
    // Successfully opened the socket.
    // Set to broadcast.
    Socket_stop.set_option( boost::asio::ip::udp::socket::reuse_address(true) );
    Socket_stop.set_option( boost::asio::socket_base::broadcast(true) );
    boost::asio::ip::address ip_address = boost::asio::ip::address::from_string("192.168.10.1",Error_stop); // printf("%s:%d\n",__FILE__,__LINE__);
    boost::asio::ip::udp::endpoint SenderEndpoint_stop( ip_address, Port );
    // Build up XML contents of the broadcast message.
    std::ostringstream Stream;
    if( !flag )
    {
      Stream << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << std::endl;
      Stream << "<CaptureStop>" << std::endl;
      Stream << "  <Name VALUE=\"" << CaptureName << "\"/>" << std::endl;
      Stream << "  <DatabasePath VALUE=\"" << CaptureDatabasePath << "\"/>" << std::endl;
      if( !Timecode.empty() )
        Stream << "  <TimeCode VALUE=\"" << Timecode << "\"/>" << std::endl;
      Stream << "  <PacketID VALUE=\"" << CaptureID_stop << "\"/>" << std::endl;
      Stream << "</CaptureStop>" << std::endl;
    }
    std::string String_stop( Stream.str() );
    // Send message.
    // Buffer must contain terminating 0.
    Socket_stop.send_to( boost::asio::buffer( String_stop.c_str(), String_stop.size() + 1 ), SenderEndpoint_stop );
    Socket_stop.close( Error_stop );
    // Print 数据包xml
    std::cout << String_stop << std::endl;
  }

  // 打印当前时间戳，由bag中/clock获取，为仿真时间
  ros::Time finish_time = ros::Time::now();
  std::cout << "trigger stop xml message has been sent successfully!" << ", " << finish_time << std::endl;

  return 0;
  
}
