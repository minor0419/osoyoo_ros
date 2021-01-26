#include "ros/ros.h"
#include "std_msgs/Int16.h"

#include <stdio.h>

int cmd_fr,cmd_fl,cmd_rr,cmd_rl;


void cmd_fr_buf_Callback(const std_msgs::Int16& msg)
{
  cmd_fr = msg.data;
}
void cmd_fl_buf_Callback(const std_msgs::Int16& msg)
{
  cmd_fl = msg.data;
}
void cmd_rr_buf_Callback(const std_msgs::Int16& msg)
{
  cmd_rr = msg.data;
}
void cmd_rl_buf_Callback(const std_msgs::Int16& msg)
{
  cmd_rl = msg.data;
}

int main(int argc, char **argv)
{
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line. For programmatic
   * remappings you can use a different version of init() which takes remappings
   * directly, but for most command-line programs, passing argc and argv is the easiest
   * way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  ros::init(argc, argv, "publisher2");

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;

  /**
   * The advertise() function is how you tell ROS that you want to
   * publish on a given topic name. This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing. After this advertise() call is made, the master
   * node will notify anyone who is trying to subscribe to this topic name,
   * and they will in turn negotiate a peer-to-peer connection with this
   * node.  advertise() returns a Publisher object which allows you to
   * publish messages on that topic through a call to publish().  Once
   * all copies of the returned Publisher object are destroyed, the topic
   * will be automatically unadvertised.
   *
   * The second parameter to advertise() is the size of the message queue
   * used for publishing messages.  If messages are published more quickly
   * than we can send them, the number here specifies how many messages to
   * buffer up before throwing some away.
   */
  ros::Publisher fr_pub = n.advertise<std_msgs::Int16>("cmd_fr",1000);
  ros::Publisher fl_pub = n.advertise<std_msgs::Int16>("cmd_fl",1000);
  ros::Publisher rr_pub = n.advertise<std_msgs::Int16>("cmd_rr",1000);
  ros::Publisher rl_pub = n.advertise<std_msgs::Int16>("cmd_rl",1000);
  ros::Subscriber fr_sub = n.subscribe("cmd_fr_buf", 10, cmd_fr_buf_Callback);
  ros::Subscriber fl_sub = n.subscribe("cmd_fl_buf", 10, cmd_fl_buf_Callback);
  ros::Subscriber rr_sub = n.subscribe("cmd_rr_buf", 10, cmd_rr_buf_Callback);
  ros::Subscriber rl_sub = n.subscribe("cmd_rl_buf", 10, cmd_rl_buf_Callback);
  
  ros::Rate loop_rate(1);


  /**
   * A count of how many messages we have sent. This is used to create
   * a unique string for each message.
   */
  int count = 0;

  cmd_fr = 0;
  cmd_fl = 0;
  cmd_rr = 0;
  cmd_rl = 0;

  while (ros::ok())
  {
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
    //int cmd;
    //printf("Input command data : ");
    //scanf("%d",&cmd);
    std_msgs::Int16 msg;

    //msg.data = cmd;

    /**
     * The publish() function is how you send messages. The parameter
     * is the message object. The type of this object must agree with the type
     * given as a template parameter to the advertise<>() call, as was done
     * in the constructor above.
     */
    msg.data = cmd_fr;
    fr_pub.publish(msg);

    msg.data = cmd_fl;
    fl_pub.publish(msg);

    msg.data = cmd_rr;
    rr_pub.publish(msg);

    msg.data = cmd_rl;
    rl_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
  }


  return 0;
}
