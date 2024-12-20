# Step 1: Start with an appropriate base image (e.g., Ubuntu)
FROM ubuntu:20.04

# Step 2: Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    cmake \
    curl \
    libpthread-stubs0-dev \
    && rm -rf /var/lib/apt/lists/*

# Step 3: Install Iceoryx (we will clone from GitHub)
RUN git clone --single-branch https://github.com/eclipse-iceoryx/iceoryx.git /iceoryx && \
    cd /iceoryx && \
    git checkout master && \
    mkdir -p build && \
    cd build && \
    cmake .. && \
    make -j && \
    make install

# Step 4: Copy your C++ publisher code into the container
COPY docker_pub.cpp /app/iceoryx_publisher.cpp

# Step 5: Set the working directory
WORKDIR /app

# Step 6: Compile the C++ program (Iceoryx publisher)
RUN g++ -o docker_pub docker_pub.cpp -lstdc++ -pthread

# Step 7: Expose any necessary ports (not needed for publisher, but for clarity)
EXPOSE 8080

# Step 8: Set the default command to run your Iceoryx publisher
CMD ["./docker_pub"]
