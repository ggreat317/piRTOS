#include <unistd.h>

#include <chrono>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class Heartbeat : public rclcpp::Node {
  public: Heartbeat() : Node("heartbeat_cpp") {
    publisher_ = create_publisher<std_msgs::msg::String>("/hello_cpp", 10);

    char name[256] = {};
    gethostname(name, sizeof(name) - 1);
    hostname_ = name;

    slowTimer_ = create_wall_timer(1s, [this]() {slowTick();});
    fastTimer_ = create_wall_timer(100ms, [this]() {fastTick();});
  }

  private: void slowTick() {
    ++count_;
    std_msgs::msg::String msg;
    msg.data = "hello from " + hostname_ + " #" + std::to_string(count_);
    publisher_->publish(msg);
    RCLCPP_INFO(get_logger(), "%s", msg.data.c_str());
  }


  private: void fastTick() {
    fastCount_ = (fastCount_ + 1) % 10;
    std_msgs::msg::String msg;
    msg.data = "hello from " + hostname_ + " #" + std::to_string(fastCount_) + std::to_string(count_);
    publisher_->publish(msg);
    RCLCPP_INFO(get_logger(), "%s", msg.data.c_str());
  }

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr fastTimer_;
  rclcpp::TimerBase::SharedPtr slowTimer_;
  std::string hostname_;
  int count_ = 0;
  int fastCount_ = 0;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Heartbeat>());
  rclcpp::shutdown();
  return 0;
}
