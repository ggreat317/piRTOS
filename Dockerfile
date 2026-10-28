FROM ros:jazzy-ros-base

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        ros-jazzy-demo-nodes-cpp \
        ros-jazzy-demo-nodes-py \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /ws

RUN echo 'source /opt/ros/jazzy/setup.bash' >> /root/.bashrc \
    && echo '[ -f /ws/install/setup.bash ] && source /ws/install/setup.bash' >> /root/.bashrc
