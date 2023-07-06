#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>

class TranslationKinematics {
public:
  TranslationKinematics() {
    turtle1_pose_subscriber = nh.subscribe("turtle1/pose", 1000, &TranslationKinematics::turtle1PoseCallback, this);
    turtle2_pose_subscriber = nh.subscribe("turtle2/pose", 1000, &TranslationKinematics::turtle2PoseCallback, this);

    translation_vector = geometry_msgs::Vector3();
  }

  void subscribe() {
    // Subscribe to the turtle pose topics.
    turtle1_pose_subscriber = nh.subscribe("turtle1/pose", 1000, &TranslationKinematics::turtle1PoseCallback, this);
    turtle2_pose_subscriber = nh.subscribe("turtle2/pose", 1000, &TranslationKinematics::turtle2PoseCallback, this);
  }

  void calculateTranslationVector() {
    // Get the latest turtle poses.
    turtle1_pose = turtle1_pose_subscriber.getLatestMsg();
    turtle2_pose = turtle2_pose_subscriber.getLatestMsg();

    // Calculate the translation vector.
    translation_vector.x = turtle2_pose.pose.position.x - turtle1_pose.pose.position.x;
    translation_vector.y = turtle2_pose.pose.position.y - turtle1_pose.pose.position.y;
    translation_vector.z = turtle2_pose.pose.position.z - turtle1_pose.pose.position.z;
  }

  void publishTranslationVector() {
    // Publish the translation vector.
    translation_vector_publisher.publish(translation_vector);
  }

private:
  ros::NodeHandle nh;
  ros::Subscriber turtle1_pose_subscriber;
  ros::Subscriber turtle2_pose_subscriber;
  ros::Publisher translation_vector_publisher;
  geometry_msgs::PoseStamped turtle1_pose;
  geometry_msgs::PoseStamped turtle2_pose;
  geometry_msgs::Vector3 translation_vector;

  void turtle1PoseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg) {
    turtle1_pose = *msg;
  }

  void turtle2PoseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg) {
    turtle2_pose = *msg;
  }
};