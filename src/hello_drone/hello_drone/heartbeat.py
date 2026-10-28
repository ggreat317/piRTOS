"""Publish "hello from <hostname> #<count>" on /hello once per second."""

import socket

import rclpy
from rclpy.executors import ExternalShutdownException
from rclpy.node import Node
from std_msgs.msg import String


class Heartbeat(Node):

    def __init__(self):
        super().__init__('heartbeat')
        self.publisher = self.create_publisher(String, '/hello', 10)
        self.hostname = socket.gethostname()
        self.count = 0
        self.create_timer(1.0, self.tick)

    def tick(self):
        self.count += 1
        msg = String()
        msg.data = f'hello from {self.hostname} #{self.count}'
        self.publisher.publish(msg)
        self.get_logger().info(msg.data)


def main():
    rclpy.init()
    node = Heartbeat()
    try:
        rclpy.spin(node)
    except (KeyboardInterrupt, ExternalShutdownException):
        pass
    finally:
        node.destroy_node()
        rclpy.try_shutdown()


if __name__ == '__main__':
    main()
