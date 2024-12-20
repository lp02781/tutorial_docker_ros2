# Use the ROS 2 Foxy base image
FROM ros:foxy

# Install depedencies
RUN sudo apt-get update && apt-get install -y \
    software-properties-common \
    && add-apt-repository universe \
    && apt-get update \
    && apt-get install -y \
    python3-colcon-common-extensions \
    build-essential \
    python3-pip \
    git \
    && rm -rf /var/lib/apt/lists/*
    
# Install ROS2 Foxy
RUN locale  # check for UTF-8

RUN sudo apt-get update && sudo apt-get install locales
RUN sudo locale-gen en_US en_US.UTF-8
RUN sudo update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
RUN export LANG=en_US.UTF-8

RUN locale  # verify settings

RUN sudo apt install -y software-properties-common
RUN sudo add-apt-repository universe

RUN sudo apt update && sudo apt install curl -y
RUN sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg

RUN echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null

RUN sudo apt -y update
RUN sudo apt -y upgrade

RUN sudo apt install ros-foxy-ros-base python3-argcomplete

# Install ROS2 packages 
RUN sudo apt install -y ros-foxy-joy

# Setup
RUN mkdir -p /workspace/src
WORKDIR /workspace
COPY ../foxy_ws/src/cpp_pubsub /workspace/src/cpp_pubsub
RUN /bin/bash -c "source /opt/ros/foxy/setup.bash && rosdep update && rosdep install --from-paths src --ignore-src -r -y"
RUN /bin/bash -c "source /opt/ros/foxy/setup.bash && colcon build"
RUN echo 'source /opt/ros/foxy/setup.bash' >> ~/.bashrc
RUN echo 'source /workspace/install/setup.bash' >> ~/.bashrc

# Set entrypoint to interactive bash shell
CMD ["/bin/bash", "-c", "source /opt/ros/foxy/setup.bash && \
    source install/setup.bash && \
    ros2 run cpp_pubsub talker && \
    ros2 run cpp_pubsub listener"]


