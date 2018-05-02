#include <math.h>

#include <boost/thread.hpp>
#include <boost/algorithm/string.hpp>

#include <gazebo/gazebo_client.hh>
#include <gazebo/common/Plugin.hh>
#include <gazebo/msgs/msgs.hh>
#include <gazebo/transport/transport.hh>

#include <ros/ros.h>
#include <ros/subscribe_options.h>
#include <std_srvs/Empty.h>


bool next_step(std_srvs::Empty::Request  &req,
               std_srvs::Empty::Response &res,
               gazebo::transport::PublisherPtr &pub)
{
  for (int i = 0; i < 2; ++i)
  {
    gazebo::msgs::WorldControl msg;
    msg.set_step(1);
    pub->Publish(msg);
    gazebo::common::Time::MSleep(10);
  }

  return true;
}

int main(int argc, char** argv)
{
  gazebo::client::setup(argc,argv);
  ros::init(argc, argv, "get_world_time_test");

  // Gazebo WorldControl Topic
  gazebo::transport::NodePtr node(new gazebo::transport::Node());
  node->Init();
  gazebo::transport::PublisherPtr pub = node->Advertise<gazebo::msgs::WorldControl>("~/world_control");

  // Initialize the ROSNode
  ros::NodeHandle n;
  // ros::ServiceServer service = n.advertiseService("/gazebo_next_step", &Listener::next_step, &listener); 
  ros::ServiceServer service = n.advertiseService<std_srvs::Empty::Request, std_srvs::Empty::Response>
                                                  ("/gazebo/next_step", boost::bind(next_step, _1, _2, pub)); 
  
  ros::spin();

  gazebo::client::shutdown();

  return 0;
}
